// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

#ifdef CONFIGURATION_HEADER
  #include CONFIGURATION_HEADER
#endif // CONFIGURATION_HEADER
#include EMBER_AF_API_COAP_DISPATCH

EmberAfCoapDispatchHandler clientReportHandler;
EmberAfCoapDispatchHandler diagnosticAnswerHandler;

const EmberAfCoapDispatchEntry emberAfCoapDispatchTable[] = {
  {EMBER_AF_COAP_DISPATCH_METHOD_ANY, "d/da", 4, diagnosticAnswerHandler},
  {EMBER_AF_COAP_DISPATCH_METHOD_POST, "client/report", 13, clientReportHandler},
  {0, NULL, 0, NULL}, // terminator
};
