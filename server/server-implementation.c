/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK
#include EMBER_AF_API_HAL
#include EMBER_AF_API_COMMAND_INTERPRETER2
#ifdef EMBER_AF_API_DEBUG_PRINT
  #include EMBER_AF_API_DEBUG_PRINT
#endif

#define ALIAS(x) x##Alias
#include "app/thread/plugin/udp-debug/udp-debug.c"
#include "stack/ip/ip-address.h"
#ifdef HAL_CONFIG
  #include "hal-config.h"
  #include "ember-hal-config.h"
#endif
#include "em_timer.h"
#include "Channel_Definition.h"

// WARNING: By default, this sample application uses the well-know sensor/sink
// network key as the master key.  This is done for demonstration purposes, so
// that packets will decrypt automatically in Simplicity Studio.  Using
// predefined keys is a significant security risk.  Real devices MUST use
// random keys.  The stack automatically generates random keys if
// emberSetSecurityParameters is not called prior to forming.
//#define USE_RANDOM_MASTER_KEY
#ifdef USE_RANDOM_MASTER_KEY
  #define SET_SECURITY_PARAMETERS_OR_FORM_NETWORK FORM_NETWORK
#else
static EmberKeyData masterKey = {
  { 0x65, 0x6D, 0x62, 0x65, 0x72, 0x20, 0x45, 0x4D,
    0x32, 0x35, 0x30, 0x20, 0x63, 0x68, 0x69, 0x70, }
};
  #define SET_SECURITY_PARAMETERS_OR_FORM_NETWORK SET_SECURITY_PARAMETERS
#endif

// The client/server sample applications use a fixed network id to simplify
// the join process.
static const uint8_t networkId[EMBER_NETWORK_ID_SIZE] = "client/server";

static const uint8_t commissionerId[] = "server";

//SPI + DAC
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_ldma.h"

#define TX_BUFFER_SIZE   33
uint8_t ADDR = 0x10;
uint8_t TxBuffer[TX_BUFFER_SIZE];
uint32_t advertiseIndex=9999;
uint32_t dacBuffIndex = 0;
uint32_t TxBufferIndex = 0;
uint8_t DACIndex=0;
uint16_t tempDacIndex = 0;
uint16_t data[1000];
uint32_t totalDataLength=0;
uint32_t totalPayloadLength=0;
uint32_t indexDataLength=0;
uint32_t TimeStamp=0;
uint8_t indTest=0;
extern uint8_t packetsOrder[];
//UDP
uint8_t FailCounter = 0;
uint8_t OldPackets = 0;
int8_t PacketsFailHandler[17];

static void resumeNetwork(void);
#ifndef USE_RANDOM_MASTER_KEY
static void setSecurityParameters(void);
#endif
static void formNetwork(void);
static void getCommissioner(void);
static void becomeCommissioner(void);
static void printAllThreadNodesAddresses(void);
static void advertise(void);
static void resetNetworkState(void);

#define ADVERTISEMENT_PERIOD_MS (60 * MILLISECOND_TICKS_PER_SECOND)

static const uint8_t serverAdvertiseUri[] = "server/advertise";

enum {
  INITIAL                       = 0,
  RESUME_NETWORK                = 1,
  SET_SECURITY_PARAMETERS       = 2,
  FORM_NETWORK                  = 3,
  GET_COMMISSIONER              = 4,
  BECOME_COMMISSIONER           = 5,
  MAKE_ALL_THREAD_NODES_ADDRESS = 6,
  ADVERTISE                     = 7,
  RESET_NETWORK_STATE           = 8,
};
static uint8_t state = INITIAL;
EmberEventControl stateEventControl;
static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs);
#define setNextState(nextState)       setNextStateWithDelay((nextState), 0)
#define repeatStateWithDelay(delayMs) setNextStateWithDelay(state, (delayMs))

static const uint8_t *printableNetworkId(void);

bool emIsDefaultGlobalPrefix(const uint8_t *prefix);

void emberAfNetworkStatusCallback(EmberNetworkStatus newNetworkStatus,
                                  EmberNetworkStatus oldNetworkStatus,
                                  EmberJoinFailureReason reason)
{
  // This callback is called whenever the network status changes, like when
  // we finish forming a new network or when we lose connectivity.  If we have
  // no network, we form a new one.  If we have a saved network, we try to
  // resume operations on that network.  When we are joined and attached to the
  // network, we establish ourselves as the commissioner and then begin
  // advertising.

  emberEventControlSetInactive(stateEventControl);

  switch (newNetworkStatus) {
    case EMBER_NO_NETWORK:
      if (oldNetworkStatus == EMBER_JOINING_NETWORK) {
        emberAfCorePrintln("ERR: Forming failed: 0x%x", reason);
      }
      setNextState(SET_SECURITY_PARAMETERS_OR_FORM_NETWORK);
      break;
    case EMBER_SAVED_NETWORK:
      setNextState(RESUME_NETWORK);
      break;
    case EMBER_JOINING_NETWORK:
      // Wait for either the "attaching" or "no network" state.
      break;
    case EMBER_JOINED_NETWORK_ATTACHING:
      // Wait for the "attached" state.
      if (oldNetworkStatus == EMBER_JOINED_NETWORK_ATTACHED) {
        emberAfCorePrintln("Trying to re-connect...");
      }
      break;
    case EMBER_JOINED_NETWORK_ATTACHED:
      emberAfCorePrintln("%s network \"%s\"",
                         (state == RESUME_NETWORK
                          ? "Resumed operation on"
                          : (state == FORM_NETWORK
                             ? "Formed"
                             : "Rejoined")),
                         printableNetworkId());
      setNextState(GET_COMMISSIONER);
      break;
    case EMBER_JOINED_NETWORK_NO_PARENT:
      // We always form as a router, so we should never end up in the "no parent"
      // state.
      assert(false);
      break;
    default:
      assert(false);
      break;
  }
}

static void resumeNetwork(void)
{
  assert(state == RESUME_NETWORK);

  emberAfCorePrintln("Resuming operation on network \"%s\"", printableNetworkId());
  emberResumeNetwork();
}

void emberResumeNetworkReturn(EmberStatus status)
{
  // This return indicates whether the stack is going to attempt to resume.  If
  // so, the result is reported later as a network status change.  If we cannot
  // even attempt to resume, we just give up and try forming instead.

  assert(state == RESUME_NETWORK);

  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("ERR: Unable to resume: 0x%x", status);
    setNextState(SET_SECURITY_PARAMETERS_OR_FORM_NETWORK);
  }
}

#ifndef USE_RANDOM_MASTER_KEY
static void setSecurityParameters(void)
{
  // Setting a fixed master key is a security risk, but is useful for
  // demonstration purposes.  See the warning above.

  EmberSecurityParameters parameters = { 0 };

  assert(state == SET_SECURITY_PARAMETERS);

  emberAfCorePrint("Setting master key to ");
  emberAfCoreDebugExec(emberAfPrintZigbeeKey(masterKey.contents));

  parameters.networkKey = &masterKey;
  emberSetSecurityParameters(&parameters, EMBER_NETWORK_KEY_OPTION);
}
#endif

void emberSetSecurityParametersReturn(EmberStatus status)
{
#ifndef USE_RANDOM_MASTER_KEY
  // After setting our security parameters, we can move on to actually forming
  // the network.

  assert(state == SET_SECURITY_PARAMETERS);

  if (status == EMBER_SUCCESS) {
    setNextState(FORM_NETWORK);
  } else {
    emberAfCorePrint("ERR: Setting master key to ");
    emberAfCoreDebugExec(emberAfPrintZigbeeKey(masterKey.contents));
    emberAfCorePrintln(" failed:  0x%x", status);
    setNextState(SET_SECURITY_PARAMETERS);
  }
#endif
}

static void formNetwork(void)
{
  EmberNetworkParameters parameters = { { 0 } };

  assert(state == FORM_NETWORK);

  emberAfCorePrintln("Forming network \"%s\"", networkId);

  MEMCOPY(parameters.networkId, networkId, sizeof(networkId));
  parameters.nodeType = EMBER_END_DEVICE;
  parameters.radioTxPower = 10;

  emberFormNetwork(&parameters,
                   (EMBER_NETWORK_ID_OPTION
                    | EMBER_NODE_TYPE_OPTION
                    | EMBER_TX_POWER_OPTION),
                   EMBER_ALL_802_15_4_CHANNELS_MASK);
}

void emberFormNetworkReturn(EmberStatus status)
{
  // This return indicates whether the stack is going to attempt to form.  If
  // so, the result is reported later as a network status change.  Otherwise,
  // we just try again.

  assert(state == FORM_NETWORK);

  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("ERR: Unable to form: 0x%x", status);
    setNextState(SET_SECURITY_PARAMETERS_OR_FORM_NETWORK);
  }
}

static void getCommissioner(void)
{
  assert(state == GET_COMMISSIONER);

  emberGetCommissioner();
}

void emberCommissionerStatusHandler(uint16_t flags,
                                    const uint8_t *commissionerName,
                                    uint8_t commissionerNameLength)
{
  if (state == GET_COMMISSIONER) {
    if (flags == EMBER_NO_COMMISSIONER) {
      setNextState(BECOME_COMMISSIONER);
    } else {
      if (!READBITS(flags, EMBER_AM_COMMISSIONER)) {
        emberAfCorePrint("ERR: Network already has a commissioner");
        if (commissionerName != NULL) {
          emberAfCorePrint(": ");
          uint8_t i;
          for (i = 0; i < commissionerNameLength; i++) {
            emberAfCorePrint("%c", commissionerName[i]);
          }
        }
        emberAfCorePrintln("");
      }
      setNextState(MAKE_ALL_THREAD_NODES_ADDRESS);
    }
  }
}

static void becomeCommissioner(void)
{
  // We want to establishing ourselves as the commissioner so that we are in
  // charge of bringing new devices into the network.

  assert(state == BECOME_COMMISSIONER);

  emberAfCorePrintln("Becoming commissioner \"%s\"", commissionerId);

  emberBecomeCommissioner(commissionerId, sizeof(commissionerId));
}

void emberBecomeCommissionerReturn(EmberStatus status)
{
  // Once we are established as the commissioner, we move on to periodically
  // advertising our presence to other routers in the mesh.

  assert(state == BECOME_COMMISSIONER);

  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("Became commissioner");
    setNextState(MAKE_ALL_THREAD_NODES_ADDRESS);
  } else {
    emberAfCorePrintln("ERR: Becoming commissioner failed: 0x%x", status);
    setNextState(GET_COMMISSIONER);
  }
}

// expect <join key:1--16> [<eui64:8>]
void expectCommand(void)
{
  uint8_t joinKeyLength;
  uint8_t *joinKey;
  bool hasEui64;
  EmberEui64 eui64;

  joinKey = emberStringCommandArgument(0, &joinKeyLength);
  if (joinKeyLength > EMBER_JOIN_KEY_MAX_SIZE) {
    emberAfAppPrintln("%p: %p", "ERR", "invalid join key");
    return;
  }

  hasEui64 = (emberCommandArgumentCount() > 1);
  if (hasEui64) {
    emberGetEui64Argument(1, &eui64);
    emberSetJoinKey(&eui64, joinKey, joinKeyLength);
    emberSetJoiningMode(EMBER_JOINING_ALLOW_EUI_STEERING, 16);
    emberAddSteeringEui64(&eui64);
  } else {
    emberSetJoinKey(NULL, joinKey, joinKeyLength);
    emberSetJoiningMode(EMBER_JOINING_ALLOW_ALL_STEERING, 1);
  }
  emberSendSteeringData();
}

void emberSendSteeringDataReturn(EmberStatus status)
{
  // The steering data helps bring new devices into our network.

  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("Sent steering data");
  } else {
    emberAfCorePrintln("ERR: Sending steering data failed: 0x%x", status);
  }
}

static void printAllThreadNodesAddresses(void)
{
  assert(state == MAKE_ALL_THREAD_NODES_ADDRESS);

  emberAfCorePrintln("Using the following thread multicast addresses:");
  emberAfCoreDebugExec(emberAfPrintIpv6Address((EmberIpv6Address*)&emFf32AllThreadNodesMulticastAddress));
  emberAfCorePrintln("");
  emberAfCoreDebugExec(emberAfPrintIpv6Address((EmberIpv6Address*)&emFf33AllThreadNodesMulticastAddress));
  emberAfCorePrintln("");
  emberAfCoreDebugExec(emberAfPrintIpv6Address((EmberIpv6Address*)&emFf33AllThreadRoutersMulticastAddress));
  emberAfCorePrintln("");

  setNextState(ADVERTISE);
}

static void advertise(void)
{
  // We periodically send advertisements to all nodes in the mesh.  Unattached
  // clients that hear these advertisements will begin sending data to us.

  EmberCoapSendInfo info = { 0 }; // use defaults
  EmberStatus status;
  assert(state == ADVERTISE);


  emberAfCorePrint("Advertising to ");
  emberAfCoreDebugExec(emberAfPrintIpv6Address((EmberIpv6Address*)&emFf33AllThreadNodesMulticastAddress));
  emberAfCorePrintln("");

  status = emberCoapPost((const EmberIpv6Address*)&emFf33AllThreadNodesMulticastAddress,
						 serverAdvertiseUri,
						 NULL, // payload
						 0,    // payload length
						 NULL, // handler
						 &info);
  if (status != EMBER_SUCCESS) {emberAfCorePrintln("ERR: Advertising failed: 0x%x", status);}
  repeatStateWithDelay(10000);
}

// advertise
void advertiseCommand(void)
{
  // If we are already advertising, we can manually send a new advertisement
  // using a CLI command.

  if (state == ADVERTISE) {
    advertise();
  }
}

void TIMER1_IRQHandler(void)
{
  // Acknowledge the interrupt
  uint32_t flags = TIMER_IntGet(TIMER1);
  TIMER_IntClear(TIMER1, flags);

  //DAC Output
  if(DACIndex > 0)
  	  {
	  	  if(dacBuffIndex==0){tempDacIndex = DACIndex;} 					//Lock to Received Packet
	  	  TxBuffer[0]=0x10; 												//Address to DACn
	  	  uint16_t dataIndex = (160*(tempDacIndex-1))+(16*dacBuffIndex);	//Lock to sample in Received Packet
	  	  for(int i=1; i<TX_BUFFER_SIZE; i=i+2)								//Build Data Buff to Send to DAC
	  	  	  {
	  		  	TxBuffer[i] = (uint8_t)(data[dataIndex]>>8);				//8bits per 8bits
	  		  	TxBuffer[i+1] =(uint8_t)(data[dataIndex]&0x00ff);
	  	  	  }
	  	  /*
	  	  	  ADD SPI SEND FUNCTzION
	  	  */
	  	dacBuffIndex++;														//Switch to next Sample
		if(dacBuffIndex==10){dacBuffIndex=0;if(DACIndex==tempDacIndex){DACIndex=0;}}					//
  	  }

}


void clientReportHandler(EmberCoapCode code,
                         uint8_t *uri,
                         EmberCoapReadOptions *options,
                         const uint8_t *payload,
                         uint16_t payloadLength,
                         const EmberCoapRequestInfo *info)
{
  EmberCoapCode responseCode;
  if (state != ADVERTISE) {
    responseCode = EMBER_COAP_CODE_503_SERVICE_UNAVAILABLE;
  } else if (payloadLength > 1024) {
    responseCode = EMBER_COAP_CODE_400_BAD_REQUEST;
  } else {
	  uint8_t index=0;
	  for(int p =0; p<((payloadLength*12)/12);p+=3){
			data[index] = (((uint16_t)(payload[p]))<<4) | (((uint16_t)payload[p+1]) &0xF0)>>4;
			data[index+1] = ((((uint16_t)(payload[p+1]))<<8) | (((uint16_t)payload[p+2])))&0x0FFF;
			index+=2;
	  }
	  totalDataLength += payloadLength;



	  indexDataLength++;
	 if(indexDataLength==100){
		 uint32_t Now = halCommonGetInt32uMillisecondTick();
		 emberAfCorePrintln("Get %d Data in %d", totalDataLength, Now-TimeStamp);
		 TimeStamp = Now;
		 indexDataLength=0;
		 totalDataLength=0;
	 }
	 responseCode = EMBER_COAP_CODE_204_CHANGED;

  }
  if (emberCoapIsSuccessResponse(responseCode)
      || info->localAddress.bytes[0] != 0xFF) { // not multicast
    emberCoapRespondWithCode(info, responseCode);
  }
}

static void resetNetworkState(void)
{
  emberAfCorePrintln("Resetting network state");
  emberResetNetworkState();
}

void emberResetNetworkStateReturn(EmberStatus status)
{
  // If we ever leave the network, we go right back to forming again.  This
  // could be triggered by an external CLI command.

  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("Reset network state");
  }
}

uint32_t calculateBitRate(uint32_t time, uint32_t numberOfData)
{
	float tempo = numberOfData /  (((float)time)/1000);
	return (uint32_t)tempo;
}

void emberUdpHandler(const uint8_t *destination,
                     const uint8_t *source,
                     uint16_t localPort,
                     uint16_t remotePort,
                     const uint8_t *payload,
                     uint16_t payloadLength)
{
	  uint32_t now = halCommonGetInt32uMillisecondTick(); //Time for arranging data

	  if(payload[payloadLength-1]< 99){
	  dispatchPackets(data,payload,payloadLength);
	  totalDataLength += ((payloadLength-1)*8/10);}
	  else if(payload[payloadLength-1]<149){dispatchPacketsDeltaEncoding(data,payload,payloadLength);
	  totalDataLength += 85;}
	  else{dispatchPacketsDeltaEncoding(data,payload,payloadLength);
	  totalDataLength += 170;}


	  totalPayloadLength += payloadLength;
	  indexDataLength++;
		if(indexDataLength==100){
			 uint32_t Now = halCommonGetInt32uMillisecondTick();
			 emberAfCorePrintln("Get %d Data in %d with a DataRate of %d (%d Bytes from packets)", totalDataLength, Now-TimeStamp, calculateBitRate(Now-TimeStamp,totalDataLength),totalPayloadLength);
			 TimeStamp = Now;
			 indexDataLength=0;
			totalPayloadLength=0;
			 totalDataLength=0;
		}
}

bool emberAfPluginIdleSleepOkToSleepCallback(uint32_t durationMs)
{
  // Once we join to a network, we will automatically stay awake, because we
  // are a router.  Before we join, we would could sleep, but we prevent that
  // by returning false here.

  return false;
}

void stateEventHandler(void)
{
  emberEventControlSetInactive(stateEventControl);

  switch (state) {
    case RESUME_NETWORK:
      resumeNetwork();
      break;
#ifndef USE_RANDOM_MASTER_KEY
    case SET_SECURITY_PARAMETERS:
      setSecurityParameters();
      break;
#endif
    case FORM_NETWORK:
      formNetwork();
      break;
    case GET_COMMISSIONER:
      getCommissioner();
      break;
    case BECOME_COMMISSIONER:
      becomeCommissioner();
      break;
    case MAKE_ALL_THREAD_NODES_ADDRESS:
      printAllThreadNodesAddresses();
      break;
    case ADVERTISE:
      advertise();
      break;
    case RESET_NETWORK_STATE:
      resetNetworkState();
      break;
    default:
      assert(false);
  }
}

static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs)
{
  state = nextState;
  emberEventControlSetDelayMS(stateEventControl, delayMs);
}

static const uint8_t *printableNetworkId(void)
{
  EmberNetworkParameters parameters = { { 0 } };
  static uint8_t networkId[EMBER_NETWORK_ID_SIZE + 1] = { 0 };
  emberGetNetworkParameters(&parameters);
  MEMCOPY(networkId, parameters.networkId, EMBER_NETWORK_ID_SIZE);
  return networkId;
}

// expect <join key:1--16> [<eui64:8>]
void autoExpectCommand(uint8_t *joinKey, uint8_t joinKeyLength)
{
  emberSetJoinKey(NULL, joinKey, joinKeyLength);
  emberSetJoiningMode(EMBER_JOINING_ALLOW_ALL_STEERING, 1);
  emberSendSteeringData();
}





void initUSART1 (void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_USART1, true);

  // Configure GPIO mode
  GPIO_PinModeSet(gpioPortC, 8, gpioModePushPull, 0); // US1_CLK is push pull
  GPIO_PinModeSet(gpioPortC, 9, gpioModePushPull, 1); // US1_CS is push pull
  GPIO_PinModeSet(gpioPortC, 6, gpioModePushPull, 1); // US1_TX (MOSI) is push pull
  GPIO_PinModeSet(gpioPortC, 7, gpioModeInput, 1);    // US1_RX (MISO) is input

  // Start with default config, then modify as necessary
  USART_InitSync_TypeDef config = USART_INITSYNC_DEFAULT;
  config.master       = true;            // master mode
  config.baudrate     = 1000000;         // CLK freq is 1 MHz
  config.autoCsEnable = false;            // CS pin controlled by hardware, not firmware
  config.clockMode    = usartClockMode0; // clock idle low, sample on rising/first edge
  config.msbf         = true;            // send MSB first
  config.enable       = usartDisable;    // Make sure to keep USART disabled until it's all set up
  USART_InitSync(USART1, &config);

  // Set USART pin locations
  USART1->ROUTELOC0 = (USART_ROUTELOC0_CLKLOC_LOC11) | // US1_CLK       on location 11 = PC8 per datasheet section 6.4 = EXP Header pin 8
                      (USART_ROUTELOC0_CSLOC_LOC11)  | // US1_CS        on location 11 = PC9 per datasheet section 6.4 = EXP Header pin 10
                      (USART_ROUTELOC0_TXLOC_LOC11)  | // US1_TX (MOSI) on location 11 = PC6 per datasheet section 6.4 = EXP Header pin 4
                      (USART_ROUTELOC0_RXLOC_LOC11);   // US1_RX (MISO) on location 11 = PC7 per datasheet section 6.4 = EXP Header pin 6

  // Enable USART pins
  USART1->ROUTEPEN = USART_ROUTEPEN_CLKPEN | USART_ROUTEPEN_CSPEN | USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;

  // Enable USART1
  USART_Enable(USART1, usartEnable);
}
