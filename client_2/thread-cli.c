// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// This file contains the mapping for the command line configuration

#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_EMBER_TYPES
#ifdef EMBER_AF_API_THREAD_TEST_HARNESS_CLI
#include EMBER_AF_API_THREAD_TEST_HARNESS_CLI
#endif
#include EMBER_AF_API_COMMAND_INTERPRETER2

void attachCommand(void);
void coapDeleteCommand(void);
void coapGetCommand(void);
void coapListenCommand(void);
void coapPostCommand(void);
void coapPutCommand(void);
void coapSetOptionAcceptCommand(void);
void coapSetOptionBlockOptionValueCommand(void);
void coapSetOptionContentFormatCommand(void);
static EmberCommandEntry emberCommandCoapSetOptionTable[] = {
  emberCommandEntryAction("accept", coapSetOptionAcceptCommand, "v", ""),
  emberCommandEntryAction("block-option-value", coapSetOptionBlockOptionValueCommand, "uuw", ""),
  emberCommandEntryAction("content-format", coapSetOptionContentFormatCommand, "v", ""),
  emberCommandEntryTerminator(),
};
static EmberCommandEntry emberCommandCoapTable[] = {
  emberCommandEntryAction("delete", coapDeleteCommand, "bb", ""),
  emberCommandEntryAction("get", coapGetCommand, "bb", ""),
  emberCommandEntryAction("listen", coapListenCommand, "b", ""),
  emberCommandEntryAction("post", coapPostCommand, "bbb*", ""),
  emberCommandEntryAction("put", coapPutCommand, "bbb*", ""),
  emberCommandEntrySubMenu("set-option", emberCommandCoapSetOptionTable, ""),
  emberCommandEntryTerminator(),
};
void coapsDeleteCommand(void);
void coapsGetCommand(void);
void coapsPostCommand(void);
void coapsPutCommand(void);
static EmberCommandEntry emberCommandCoapsTable[] = {
  emberCommandEntryAction("delete", coapsDeleteCommand, "bb", ""),
  emberCommandEntryAction("get", coapsGetCommand, "bb", ""),
  emberCommandEntryAction("post", coapsPostCommand, "bbb*", ""),
  emberCommandEntryAction("put", coapsPutCommand, "bbb*", ""),
  emberCommandEntryTerminator(),
};
void detachCommand(void);
void getJoinKeyCommand(void);
void emberPrintCommandTable(void);
void icmpListenCommand(void);
void icmpPingCommand(void);
static EmberCommandEntry emberCommandIcmpTable[] = {
  emberCommandEntryAction("listen", icmpListenCommand, "b", ""),
  emberCommandEntryAction("ping", icmpPingCommand, "bv*", ""),
  emberCommandEntryTerminator(),
};
void networkManagementInfoCommand(void);
void joinCommand(void);
void emberAttachToNetwork(void);
void networkManagementCommissionCommand(void);
void networkManagementCommissioningStartCommand(void);
void emberStopCommissioning(void);
static EmberCommandEntry emberCommandNetworkManagementCommissioningTable[] = {
  emberCommandEntryAction("start", networkManagementCommissioningStartCommand, "b", ""),
  emberCommandEntryAction("stop", emberStopCommissioning, "", ""),
  emberCommandEntryTerminator(),
};
void networkManagementFormCommand(void);
void networkManagementConfigureGatewayCommand(void);
void networkManagementGetGlobalAddressesCommand(void);
void emberGetGlobalPrefixes(void);
void networkManagementJoinCommand(void);
void networkManagementJoinCommissionedCommand(void);
void networkManagementListenersCommand(void);
void networkManagementMulticastSubscribeCommand(void);
static EmberCommandEntry emberCommandNetworkManagementMulticastTable[] = {
  emberCommandEntryAction("subscribe", networkManagementMulticastSubscribeCommand, "b", ""),
  emberCommandEntryTerminator(),
};
void emberResetNetworkState(void);
void emberResumeNetwork(void);
void networkManagementScanCommand(void);
void networkManagementScanCommand(void);
void emberStopScan(void);
static EmberCommandEntry emberCommandNetworkManagementScanTable[] = {
  emberCommandEntryAction("active", networkManagementScanCommand, "u*", ""),
  emberCommandEntryAction("energy", networkManagementScanCommand, "u*", ""),
  emberCommandEntryAction("stop", emberStopScan, "", ""),
  emberCommandEntryTerminator(),
};
void networkManagementSetJoinKeyCommand(void);
void networkManagementSetJoiningModeCommand(void);
void networkManagementSetMasterKeyCommand(void);
void networkManagementSteeringAddCommand(void);
void emberSendSteeringData(void);
static EmberCommandEntry emberCommandNetworkManagementSteeringTable[] = {
  emberCommandEntryAction("add", networkManagementSteeringAddCommand, "b", ""),
  emberCommandEntryAction("send", emberSendSteeringData, "", ""),
  emberCommandEntryTerminator(),
};
static EmberCommandEntry emberCommandNetworkManagementTable[] = {
  emberCommandEntryAction("attach", emberAttachToNetwork, "", ""),
  emberCommandEntryAction("commission", networkManagementCommissionCommand, "uwbbbbv*", ""),
  emberCommandEntrySubMenu("commissioning", emberCommandNetworkManagementCommissioningTable, ""),
  emberCommandEntryAction("form", networkManagementFormCommand, "usub*", ""),
  emberCommandEntryAction("gateway", networkManagementConfigureGatewayCommand, "vubuww", ""),
  emberCommandEntryAction("global-addresses", networkManagementGetGlobalAddressesCommand, "b*", ""),
  emberCommandEntryAction("global-prefixes", emberGetGlobalPrefixes, "", ""),
  emberCommandEntryAction("join", networkManagementJoinCommand, "usubbvb", ""),
  emberCommandEntryAction("join-commissioned", networkManagementJoinCommissionedCommand, "suu*", ""),
  emberCommandEntryAction("listeners", networkManagementListenersCommand, "", ""),
  emberCommandEntrySubMenu("multicast", emberCommandNetworkManagementMulticastTable, ""),
  emberCommandEntryAction("reset", emberResetNetworkState, "", ""),
  emberCommandEntryAction("resume", emberResumeNetwork, "", ""),
  emberCommandEntrySubMenu("scan", emberCommandNetworkManagementScanTable, ""),
  emberCommandEntryAction("set-join-key", networkManagementSetJoinKeyCommand, "bb*", ""),
  emberCommandEntryAction("set-joining-mode", networkManagementSetJoiningModeCommand, "uu", ""),
  emberCommandEntryAction("set-master-key", networkManagementSetMasterKeyCommand, "b", ""),
  emberCommandEntrySubMenu("steering", emberCommandNetworkManagementSteeringTable, ""),
  emberCommandEntryTerminator(),
};
void reportCommand(void);
void emberResetMicro(void);
void networkManagementStackInfoCommand(void);
void udpListenCommand(void);
void udpSendCommand(void);
static EmberCommandEntry emberCommandUdpTable[] = {
  emberCommandEntryAction("listen", udpListenCommand, "vb", ""),
  emberCommandEntryAction("send", udpSendCommand, "bvvbu*", ""),
  emberCommandEntryTerminator(),
};
void emberGetVersions(void);
EmberCommandEntry emberCommandTable[] = {
  emberCommandEntryAction("attach", attachCommand, "b", ""),
  emberCommandEntrySubMenu("coap", emberCommandCoapTable, ""),
  emberCommandEntrySubMenu("coaps", emberCommandCoapsTable, ""),
  emberCommandEntryAction("detach", detachCommand, "", ""),
  emberCommandEntryAction("get-join-key", getJoinKeyCommand, "", ""),
  emberCommandEntryAction("help", emberPrintCommandTable, "", ""),
  emberCommandEntrySubMenu("icmp", emberCommandIcmpTable, ""),
  emberCommandEntryAction("info", networkManagementInfoCommand, "", ""),
  emberCommandEntryAction("join", joinCommand, "", ""),
  emberCommandEntrySubMenu("network-management", emberCommandNetworkManagementTable, ""),
  emberCommandEntryAction("report", reportCommand, "", ""),
  emberCommandEntryAction("reset", emberResetMicro, "", ""),
  emberCommandEntryAction("stackinfo", networkManagementStackInfoCommand, "", ""),
  emberCommandEntrySubMenu("udp", emberCommandUdpTable, ""),
  emberCommandEntryAction("versions", emberGetVersions, "", ""),
#ifdef EMBER_AF_ENABLE_CUSTOM_COMMANDS
  CUSTOM_COMMANDS
#endif // EMBER_AF_ENABLE_CUSTOM_COMMANDS
  emberCommandEntryTerminator(),
};
