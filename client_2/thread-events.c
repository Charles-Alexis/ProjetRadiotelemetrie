// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Generated events.
#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "hal/hal.h"


void stateEventHandler(void);
extern EmberEventControl stateEventControl;



const EmberEventData emAppEvents[] = {
  {&stateEventControl, stateEventHandler},
  {NULL, NULL}
};