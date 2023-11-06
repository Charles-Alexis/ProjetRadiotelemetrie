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
#ifdef CORTEXM3_EFM32_MICRO
  #include "tempdrv.h"
#endif

#define ALIAS(x) x##Alias
#include "app/thread/plugin/udp-debug/udp-debug.c"

// US DELAY
#include "em_timer.h"
#include "ustimer.h"
#include <sys/time.h>
#include "hal-config.h"
#include "ember-hal-config.h"

#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_adc.h"
#include "em_gpio.h"
#include "em_letimer.h"

// ADC
#include "em_adc.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_letimer.h"
#define adcFreq 16000000
// Desired letimer interrupt frequency (in Hz)
#define letimerDesired 1000
uint32_t OUT_FREQ = 24000;// Min: 145 Hz, Max: 9.5 MHz with default settings
#define TIMER1_PRESCALE timerPrescale1
void initADC (ADC_PosSel_TypeDef channel);
void ADC0_IRQHandler(void);
uint32_t TempIndex = 0;
uint32_t initTimer(void);
void TIMER1_IRQHandler(void);
bool AdcValueInit = false;
//UDP
const EmberCoapRequestInfo * UdpInfo;
//uint8_t addr[16]={0xfd,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
uint8_t addr[16]={0xfd,0x6a,0x7b,0x67,0x41,0x92,0x0,0x0,0x32,0xf6,0x81,0xd1,0x11,0xe0,0xed,0x7f};
uint16_t FailedCounter = 0;
uint32_t temp = 0;
uint8_t IndexPacket = 0;

EmberUdpOptions test = {1};

//
uint32_t ADC_LENGTH = 124;
uint32_t PAYLOAD_LENGTH = 156;
uint8_t packIndex = 0;
uint8_t sentIndex = 0;
int32_t dataLength = 156;
uint8_t PayloadData[1500];
uint8_t PayloadDataShrink[1500];

// DELTA ENCODING
bool Encoding = true;
const uint16_t DeltaLength7 = 80;
const uint16_t DeltaLength6 = 141;
uint8_t DeltaPackets[300];
uint8_t freqindex = 0;

#include "delta-encoding.h"

#define ADC_DIFFERENT_PAQUETS 5
uint16_t ADCData[1500];
uint8_t adc2Send = 0;
uint8_t sentadcpacket = 0;

uint32_t adcIndex=0;
bool adcBuffFull = false;
void buildPayload(uint8_t ind);

// WARNING: Random join keys MUST be used for real devices, with the keys
// typically programmed during product manufacturing and printed on the devices
// themselves for access by the user.  This application will read the join key
// from a manufacturing token.  For ease of use, this application will generate
// a random join key at runtime if the manufacturing token was not set
// previously.  This will then be saved in a manufacturing token.  Join keys
// SHOULD NOT be generated at runtime.  They should be produced at
// manufacturing time.

// The client/server sample applications use a fixed network id to simplify
// the join process.
static const uint8_t networkId[EMBER_NETWORK_ID_SIZE] = "client/server";

#define JOIN_BUTTON BUTTON1
#define JOIN_KEY_SIZE 8

static void resumeNetwork(void);
static void joinNetwork(void);
static void getJoinKey(uint8_t *joinKey, uint8_t *joinKeyLength);
static void createRandomJoinKey(uint8_t *joinKey, uint8_t *joinKeyLength);
static void waitForServerAdvertisement(void);
static void attachToServer(const EmberIpv6Address *newServer);
static void reportDataToServer(void);
static void detachFromServer(void);
static void resetNetworkState(void);

static EmberIpv6Address server;
static uint8_t failedReports;
#define REPORT_FAILURE_LIMIT 3
#define WAIT_PERIOD_MS   (30 * MILLISECOND_TICKS_PER_SECOND)
#define REPORT_PERIOD_MS (10 * MILLISECOND_TICKS_PER_SECOND)
#define REPORT_PERIOD_US (500)

uint8_t tableIndex = 0;
uint8_t A0Table[12] = {1,1,1,1,1,1,1,1,0,0,0,0}; //4/2/4/2/4/2/4/2/1/1/3/3
uint8_t A1Table[12] = {1,0,1,0,1,0,1,0,0,0,1,1};
/*ADC_PosSel_TypeDef ChannelTable[16] = {adcPosSelAPORT1XCH6,adcPosSelAPORT1XCH6,adcPosSelAPORT2XCH7,adcPosSelAPORT2XCH7,
										adcPosSelAPORT4XCH29,adcPosSelAPORT4XCH29,adcPosSelAPORT3XCH2,adcPosSelAPORT3XCH2,
										adcPosSelAPORT2XCH7,adcPosSelAPORT2XCH7,adcPosSelAPORT1XCH6,adcPosSelAPORT1XCH6,
										adcPosSelAPORT3XCH2,adcPosSelAPORT3XCH2,adcPosSelAPORT4XCH29,adcPosSelAPORT4XCH29};*/

uint8_t channelIndex = 0;
ADC_PosSel_TypeDef ChannelTable[12] = {adcPosSelAPORT1XCH6,adcPosSelAPORT1XCH6,adcPosSelAPORT2XCH7,adcPosSelAPORT2XCH7,
										adcPosSelAPORT4XCH29,adcPosSelAPORT4XCH29,adcPosSelAPORT3XCH2,adcPosSelAPORT3XCH2,
										adcPosSelAPORT2XCH7,adcPosSelAPORT1XCH6,adcPosSelAPORT1XCH6,adcPosSelAPORT2XCH7};

// EMG1  EMG2  EMG3  EMG4  EMG5  EMG6  EMG7  EMG8  EOG  ECG  EEG1  EEG2
extern uint8_t packetsOrder[];
uint8_t index_EOG = 0; // Each 10 samples #9 -> #8 pos
uint8_t index_ECG = 0; // Each 5 samples #10 -> #9 pos
uint8_t index_EEG = 0; // Each 10 samples #11/#12 -> #10/#11 pos

//adcPosSelAPORT4XCH29 //PB13
//adcPosSelAPORT3XCH2 //PD10
//adcPosSelAPORT1XCH6 //PC6
//adcPosSelAPORT2XCH7 //PC7

static const uint8_t clientReportUri[] = "cr";

enum {
  INITIAL                       = 0,
  RESUME_NETWORK                = 1,
  JOIN_NETWORK                  = 2,
  WAIT_FOR_SERVER_ADVERTISEMENT = 4,
  REPORT_DATA_TO_SERVER         = 5,
  WAIT_FOR_DATA_CONFIRMATION    = 6,
  RESET_NETWORK_STATE           = 7,
};
static uint8_t state = INITIAL;
EmberEventControl stateEventControl;
static void setNextStateWithDelay(uint8_t nextState, uint32_t delayMs);
#define setNextState(nextState)       setNextStateWithDelay((nextState), 0)
#define repeatState()                 setNextStateWithDelay(state, 0)
#define repeatStateWithDelay(delayMs) setNextStateWithDelay(state, (delayMs))
#define repeatStateWithDelayUS(delayUs) setNextStateWithUsDelay(state, (delayUs))

static const uint8_t *printableNetworkId(void);

void emberAfNetworkStatusCallback(EmberNetworkStatus newNetworkStatus,
                                  EmberNetworkStatus oldNetworkStatus,
                                  EmberJoinFailureReason reason)
{
  // This callback is called whenever the network status changes, like when
  // we finish joining to a network or when we lose connectivity.  If we have
  // no network, we try joining to one.  If we have a saved network, we try to
  // resume operations on that network.  When we are joined and attached to the
  // network, we wait for an advertisement and then begin reporting.

  emberEventControlSetInactive(stateEventControl);

  switch (newNetworkStatus) {
    case EMBER_NO_NETWORK:
      if (oldNetworkStatus == EMBER_JOINING_NETWORK) {
        emberAfCorePrintln("ERR: Joining failed: 0x%x", reason);
      }
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
                          : (state == JOIN_NETWORK
                             ? "Joined"
                             : "Rejoined")),
                         printableNetworkId());
      // TODO: For a brief interruption in connectivity, the client could attempt
      // to continue reporting to its previous server, rather than wait for a new
      // server.
      setNextState(WAIT_FOR_SERVER_ADVERTISEMENT);
      break;
    case EMBER_JOINED_NETWORK_NO_PARENT:
      // We always join as a router, so we should never end up in the "no parent"
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
  assert(state == RESUME_NETWORK);
  if (status != EMBER_SUCCESS){
    emberAfCorePrintln("ERR: Unable to resume: 0x%x", status);
    setNextState(JOIN_NETWORK);}
}

static void joinNetwork(void)
{
  // When joining a network, we look for one specifically with our network id.
  // The commissioner must have our join key for this to succeed.

  EmberNetworkParameters parameters = { { 0 } };
  uint8_t joinKey[EMBER_JOIN_KEY_MAX_SIZE + 1] = { 0 };

  assert(state == JOIN_NETWORK);

  MEMCOPY(parameters.networkId, networkId, sizeof(networkId));
  parameters.nodeType = EMBER_END_DEVICE;
  parameters.radioTxPower = 10;
  getJoinKey(joinKey, &parameters.joinKeyLength);
  MEMCOPY(parameters.joinKey, joinKey, parameters.joinKeyLength);

  emberAfCorePrint("Joining network \"%s\" with EUI64 ", networkId);
  emberAfCoreDebugExec(emberAfPrintBigEndianEui64(emberEui64()));
  emberAfCorePrintln(" and join key \"%s\"", joinKey);

  emberJoinNetwork(&parameters,
                   (EMBER_NETWORK_ID_OPTION
                    | EMBER_NODE_TYPE_OPTION
                    | EMBER_TX_POWER_OPTION
                    | EMBER_JOIN_KEY_OPTION),
                   EMBER_ALL_802_15_4_CHANNELS_MASK);
}

// join
void joinCommand(void)
{
  // If we are not in a join state, we will attempt to join a network.
  // This is functionally the same as pushing the JOIN_BUTTON.

  if (emberNetworkStatus() == EMBER_NO_NETWORK) {
    setNextState(JOIN_NETWORK);
  }
}

static void getJoinKey(uint8_t *joinKey, uint8_t *joinKeyLength)
{
  tokTypeMfgThreadJoinKey token;
  halCommonGetMfgToken(&token, TOKEN_MFG_THREAD_JOIN_KEY);
  if (token.joinKeyLength == 0xFFFF) {
    createRandomJoinKey(joinKey, joinKeyLength);
    emberAfCorePrintln("WARNING: Join key not set");
    token.joinKeyLength = *joinKeyLength;
    MEMCOPY(token.joinKey, joinKey, token.joinKeyLength);
    halCommonSetMfgToken(TOKEN_MFG_THREAD_JOIN_KEY, &token);
  } else {
    *joinKeyLength = token.joinKeyLength;
    MEMCOPY(joinKey, token.joinKey, *joinKeyLength);
    joinKey[*joinKeyLength] = '\0';
  }
}

static void createRandomJoinKey(uint8_t *joinKey, uint8_t *joinKeyLength)
{
  // If the manufacturing token containing the join key was not set, a random
  // join key is generated.  The Thread specification disallows the characters
  // I, O, Q, and Z, for readability.

  const char characters[] = "ABCDEFGHJKLMNPRSTUVWXY1234567890";
  for (*joinKeyLength = 0; *joinKeyLength < JOIN_KEY_SIZE; (*joinKeyLength)++ ) {
    uint16_t key = halCommonGetRandom() % (int) (sizeof(characters) - 1);
    joinKey[*joinKeyLength] = characters[key];
    //joinKey[*joinKeyLength] = 'X';
  }
  joinKey[*joinKeyLength] = '\0';
}

// get-join-key
void getJoinKeyCommand(void)
{
  // This function gets the join key and then prints it.  If the join key has
  // not been created yet, it will be created in the getJoinKey function and
  // then printed.

  uint8_t joinKey[EMBER_JOIN_KEY_MAX_SIZE + 1];
  uint8_t joinKeyLength;

  getJoinKey(joinKey, &joinKeyLength);
  emberAfCorePrintln("Join key: \"%s\"", joinKey);
}

void emberJoinNetworkReturn(EmberStatus status)
{
  // This return indicates whether the stack is going to attempt to join.  If
  // so, the result is reported later as a network status change.  Otherwise,
  // we just try again.

  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("ERR: Unable to join: 0x%x", status);
    repeatState();
  }
}

static void waitForServerAdvertisement(void)
{
  // Once on the network, we wait for a server to advertise itself.  We
  // periodically print a message while waiting to prove we are alive.

  assert(state == WAIT_FOR_SERVER_ADVERTISEMENT);

  emberAfCorePrintln("Waiting for an advertisement from a server");

  repeatStateWithDelay(WAIT_PERIOD_MS);
}

void serverAdvertiseHandler(EmberCoapCode code,
                            uint8_t *uri,
                            EmberCoapReadOptions *options,
                            const uint8_t *payload,
                            uint16_t payloadLength,
                            const EmberCoapRequestInfo *info)
{
  // Advertisements from servers are sent as CoAP POST requests to the
  // "server/advertise" URI.  When we receive an advertisement, we attach to
  // the that sent it and beginning sending reports.

  EmberCoapCode responseCode;

  if (state != WAIT_FOR_SERVER_ADVERTISEMENT) {
    responseCode = EMBER_COAP_CODE_503_SERVICE_UNAVAILABLE;
  } else {
    attachToServer(&info->remoteAddress);
    static bool infoflag =false;
    if(infoflag==false){
    UdpInfo = &info;
    infoflag=true;}
    responseCode = EMBER_COAP_CODE_204_CHANGED;
  }

  if (emberCoapIsSuccessResponse(responseCode)
      || info->localAddress.bytes[0] != 0xFF) { // not multicast
    emberCoapRespondWithCode(info, responseCode);
  }
}

static void attachToServer(const EmberIpv6Address *newServer)
{
  // We attach to a server in response to an advertisement (or a CLI command).
  // Once we have a server, we begin reporting periodically.  We start from a
  // clean state with regard to failed reports.

  assert(state == WAIT_FOR_SERVER_ADVERTISEMENT);

  //USTIMER_Init();
  MEMCOPY(&server, newServer, sizeof(EmberIpv6Address));
  failedReports = 0;

  emberAfCorePrint("Attached to server at ");
  emberAfCoreDebugExec(emberAfPrintIpv6Address(newServer));
  emberAfCorePrintln("");

  setNextState(REPORT_DATA_TO_SERVER);
}

// attach <server>
void attachCommand(void)
{
  // If we are waiting for a server, we can manually attach to one using a CLI
  // command.

  if (state == WAIT_FOR_SERVER_ADVERTISEMENT) {
    EmberIpv6Address newServer = { { 0 } };
    if (emberGetIpv6AddressArgument(0, &newServer)) {
      attachToServer(&newServer);
    } else {
      emberAfCorePrintln("ERR: Invalid ip");
    }
  }
}

static void processServerDataAck(EmberCoapStatus status,
                                 EmberCoapCode code,
                                 EmberCoapReadOptions *options,
                                 uint8_t *payload,
                                 uint16_t payloadLength,
                                 EmberCoapResponseInfo *info)
{
  // We track the success or failure of reports so that we can determine when
  // we have lost the server.  A series of consecutive failures is the trigger
  // to detach from the current server and find a new one.  Any successfully-
  // transmitted report clears past failures.
  if (state == WAIT_FOR_DATA_CONFIRMATION) {
    if (status == EMBER_COAP_MESSAGE_ACKED
        || status == EMBER_COAP_MESSAGE_RESPONSE) {
      failedReports = 0;

    } else {
      failedReports++;
      emberAfCorePrintln("ERR: Report timed out - failure %u of %u",
                         failedReports,
                         REPORT_FAILURE_LIMIT);
    }
    if (failedReports < REPORT_FAILURE_LIMIT) {
    	setNextStateWithDelay(REPORT_DATA_TO_SERVER,0);
    } else {
      detachFromServer();
    }
  }
}

void initGPIO(void)
{
  // Enable GPIO clock
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(gpioPortA, 5, gpioModePushPull, 0); //A0
  GPIO_PinModeSet(gpioPortB, 11, gpioModePushPull, 0); //A1
  GPIO_PinOutClear(gpioPortA, 5);
  GPIO_PinOutClear(gpioPortB, 11); //00

}

void SwitchChannel(uint8_t A0,uint8_t A1, ADC_PosSel_TypeDef channel)
	{
	  /*if(A0 == 0){GPIO_PinOutClear(gpioPortA, 5);}
	  else{GPIO_PinOutSet(gpioPortA, 5);}
	  if(A1 == 0){GPIO_PinOutClear(gpioPortB, 11);}
	  else{GPIO_PinOutSet(gpioPortB, 11);}*/
	  initADC(channel);
	}

void initADC (ADC_PosSel_TypeDef channel)
{
  // Enable clocks required
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_ADC0, true);

  // Declare init structs
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

  // Modify init structs and initialize
  init.prescale   = ADC_PrescaleCalc(adcFreq, 0);
  init.timebase   = ADC_TimebaseCalc(0);
  initSingle.diff       = false;        // single ended
  initSingle.reference  = adcRef5V;    // internal 2.5V reference
  initSingle.resolution = adcRes12Bit;  // 12-bit resolution
  initSingle.acqTime    = adcAcqTime1;  // set acquisition time to meet minimum requirements

  // Select ADC input. See README for corresponding EXP header pin.
  initSingle.posSel = channel;

  ADC_Init(ADC0, &init);
  ADC_InitSingle(ADC0, &initSingle);

  // Enable ADC Single Conversion Complete interrupt
  ADC_IntEnable(ADC0, ADC_IEN_SINGLE);

  // Enable ADC interrupts
  NVIC_ClearPendingIRQ(ADC0_IRQn);
  NVIC_EnableIRQ(ADC0_IRQn);

  if(AdcValueInit == false){
	  if(Encoding==true){ADC_LENGTH = 170;}
	  tableIndex = 0;
	  index_EOG = 0;
	  index_EEG = 0;
	  index_ECG = 0;
	  AdcValueInit=true;
  }
}

uint32_t initTimer(void)
{
  // Enable clock for TIMER0 module
  CMU_ClockEnable(cmuClock_TIMER1, true);

  // Configure TIMER0 Compare/Capture for output compare
   TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
   timerCCInit.mode = timerCCModeCompare;
   timerCCInit.cmoa = timerOutputActionToggle;
   TIMER_InitCC(TIMER1, 0, &timerCCInit);

  // Note each overflow event constitutes 1/2 the signal period
  uint32_t topValue = CMU_ClockFreqGet(cmuClock_HFPER) / (1*OUT_FREQ * (1 << TIMER1_PRESCALE))-1;
  TIMER_TopSet(TIMER1, topValue);

  // Initialize and start timer with defined prescale
  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
  timerInit.prescale = TIMER1_PRESCALE;
  timerInit.oneShot = false;
  timerInit.mode =timerModeUp;

  TIMER_CompareSet(TIMER1, 0, topValue);

  TIMER_Init(TIMER1, &timerInit);

  // Enable TIMER0 interrupts
  TIMER_IntEnable(TIMER1, TIMER_IEN_CC0);
  NVIC_ClearPendingIRQ(TIMER1_IRQn);
  NVIC_EnableIRQ(TIMER1_IRQn);

  // Enable the TIMER
  TIMER_Enable(TIMER1, true);
  return topValue;
}

void TIMER1_IRQHandler(void)
{
  // Acknowledge the interrupt
  uint32_t flags = TIMER_IntGet(TIMER1);
  TIMER_IntClear(TIMER1, flags);

  if(adcBuffFull==false){
  ADC_Start(ADC0, adcStartSingle);}
}

uint16_t * ADCPOS;

void ADC0_IRQHandler(void)
{

	if(packetsOrder[tableIndex]<8){ADCData[adcIndex] = /*1000+tableIndex*/(ADC_DataSingleGet(ADC0) & 0XFFC)>>2;}
	if(packetsOrder[tableIndex]==8){ADCData[adcIndex] = /*2000+tableIndex*/(ADC_DataSingleGet(ADC0) & 0XFFC)>>2;}
	if(packetsOrder[tableIndex]==9){ADCData[adcIndex] = /*3000+tableIndex*/(ADC_DataSingleGet(ADC0) & 0XFFC)>>2;}
	if(packetsOrder[tableIndex]==10 || tableIndex==11){ADCData[adcIndex] = /*4000+tableIndex*/(ADC_DataSingleGet(ADC0) & 0XFFC)>>2;}
	tableIndex++;  //Index Of The Channel
	if(tableIndex>84){tableIndex=0;}
	SwitchChannel(A0Table[packetsOrder[tableIndex]],A1Table[packetsOrder[tableIndex]],ChannelTable[packetsOrder[tableIndex]]);

	adcIndex++;    //Index Of The Adc
	if(adcIndex>=ADC_LENGTH){adcBuffFull=true;}
	ADC_DataSingleGet(ADC0) & 0XFFC;
}

static void reportDataToServer(void)
{
  static bool initTimerFlag = false;
  EmberStatus status;
  assert(state == REPORT_DATA_TO_SERVER);
  adcIndex=0;
  adcBuffFull=false;

  if(initTimerFlag == false){
	  SwitchChannel(A0Table[packetsOrder[tableIndex]],A1Table[packetsOrder[tableIndex]],ChannelTable[packetsOrder[tableIndex]]);
  	  initTimerFlag = true;
  	  initTimer();
  }

  while(adcBuffFull==false){emberAfCorePrint("");}

  if(Encoding == false){
	  buildPayload(0);
	  status = emberSendUdpWithOptions(addr,UdpInfo->localPort,UdpInfo->remotePort,(uint8_t *)&PayloadData,PAYLOAD_LENGTH, &test);}
 else{
	  buildPayloadEncoding6(DeltaPackets,ADCData);
	  status = emberSendUdpWithOptions(addr,UdpInfo->localPort,UdpInfo->remotePort,(uint8_t *)&DeltaPackets,DeltaLength6, &test);
 }

  if(status == EMBER_SUCCESS){
	  TempIndex++;
		if(TempIndex > 100){
			freqindex++;
			//if(freqindex==5){freqindex=0;initTimerFlag=false;OUT_FREQ +=1000;}
			uint32_t Now = halCommonGetInt32uMillisecondTick();
			emberAfCorePrintln("While sending 100 Packets of %d samples (fs = %d), %d failed to send and it tooks %d ms",ADC_LENGTH,OUT_FREQ,FailedCounter,Now-temp);
			FailedCounter=0;
			temp = Now;
			TempIndex=0;
		}repeatStateWithDelay(0);}
  else{repeatStateWithDelay(0); return;}
}



void buildPayload(uint8_t ind){
	uint16_t ADCInd=0;
	for(uint32_t p = 0; p<PAYLOAD_LENGTH; p+=5){
		PayloadData[p] = (uint8_t)((ADCData[ADCInd])>>2);
		PayloadData[p+1] = (uint8_t)((ADCData[ADCInd+1])>>2);
		PayloadData[p+2] = (uint8_t)((ADCData[ADCInd+2])>>2);
		PayloadData[p+3] = (uint8_t)((ADCData[ADCInd+3])>>2);
		PayloadData[p+4] = ((ADCData[ADCInd]>>10)<<6)+((ADCData[ADCInd+1]>>10)<<4)+((ADCData[ADCInd+2]>>10)<<2)+((ADCData[ADCInd+3]>>10));
		ADCInd+=4;
	}
	PayloadData[PAYLOAD_LENGTH-1] = packIndex;
	packIndex+=1;
	if(packIndex==85){packIndex=0;}
}

// report
void reportCommand(void)
{
  // If we have a server and are reporting data, we can manually send a new
  // report using a CLI command.

  if (state == REPORT_DATA_TO_SERVER) {
    reportDataToServer();
  }
}

static void detachFromServer(void)
{
  // We detach from a server in response to failed reports (or a CLI command).
  // Once we detach, we wait for a new server to advertise itself.

  assert(state == REPORT_DATA_TO_SERVER
         || state == WAIT_FOR_DATA_CONFIRMATION);

  emberAfCorePrint("Detached from server at ");
  emberAfCoreDebugExec(emberAfPrintIpv6Address(&server));
  emberAfCorePrintln("");

  setNextState(WAIT_FOR_SERVER_ADVERTISEMENT);
}

// detach
void detachCommand(void)
{
  // If we have a server and are reporting data, we can manually detach and try
  // to find a new server by using a CLI command.

  if (state == REPORT_DATA_TO_SERVER
      || state == WAIT_FOR_DATA_CONFIRMATION) {
    detachFromServer();
  }
}

static void resetNetworkState(void)
{
  emberAfCorePrintln("Resetting network state");
  emberResetNetworkState();
}

void emberResetNetworkStateReturn(EmberStatus status)
{
  // If we ever leave the network, we go right back to joining again.  This
  // could be triggered by an external CLI command.

  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("Reset network state");
  }
}

void emberUdpHandler(const uint8_t *destination,
                     const uint8_t *source,
                     uint16_t localPort,
                     uint16_t remotePort,
                     const uint8_t *payload,
                     uint16_t payloadLength)
{
  /*ALIAS(emberUdpHandler)(destination,
                         source,
                         localPort,
                         remotePort,
                         payload,
                         payloadLength);*/
}

bool emberAfPluginIdleSleepOkToSleepCallback(uint32_t durationMs)
{
  // Once we join to a network, we will automatically stay awake, because we
  // are a router.  Before we join, we would could sleep, but we prevent that
  // by returning false here.

  return false;
}

void halButtonIsr(uint8_t button, uint8_t buttonState)
{
  // When the user pushes JOIN_BUTTON, the client will attempt to join a
  // network.

  if (buttonState == BUTTON_PRESSED && button == JOIN_BUTTON) {
    if (emberNetworkStatus() == EMBER_NO_NETWORK) {
      setNextState(JOIN_NETWORK);
    }
  }
}

void stateEventHandler(void)
{
  emberEventControlSetInactive(stateEventControl);

  switch (state) {
    case RESUME_NETWORK:
      resumeNetwork();
      break;
    case JOIN_NETWORK:
      joinNetwork();
      break;
    case WAIT_FOR_SERVER_ADVERTISEMENT:
      waitForServerAdvertisement();
      break;
    case REPORT_DATA_TO_SERVER:
      reportDataToServer();
      break;
    case WAIT_FOR_DATA_CONFIRMATION:
      break;
    case RESET_NETWORK_STATE:
      resetNetworkState();
      break;
    default:
      assert(false);
      break;
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





























/*
void initADC (void)
{
  // Enable ADC0 clock
  CMU_ClockEnable(cmuClock_ADC0, true);

  // Declare init structs
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

  // Modify init structs and initialize
  init.prescale = ADC_PrescaleCalc(adcFreq, 0); // Init to max ADC clock for Series 1

  initSingle.diff       = false;        // single ended
  initSingle.reference  = adcRef2V5;    // internal 2.5V reference
  initSingle.resolution = adcRes12Bit;  // 12-bit resolution
  initSingle.acqTime    = adcAcqTime4;  // set acquisition time to meet minimum requirementprsEnable
  initSingle.prsEnable    = false;  // set acquisition time to meet minimum requirementprsEnable

  // Select ADC input. See README for corresponding EXP header pin.
  initSingle.posSel = adcPosSelAPORT2XCH9;
  init.timebase = ADC_TimebaseCalc(0);

  ADC_Init(ADC0, &init);
  ADC_InitSingle(ADC0, &initSingle);
}*/


