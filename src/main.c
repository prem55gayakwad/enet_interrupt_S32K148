#include "board_config.h"

#include "app_config.h"

#include <board_access.h>

int main(void) {

  // configure hardware/BSP
  config_hw();

  config_fast_cb(app_fast_handler);
  config_slow_cb(app_slow_handler);

  // configure trigger-in callback
  config_trigger_in_cb(app_trigger_in_handler);
  // clear all trigger pins
  release_trigger_out();

  // endless loop here
  // all activities are in app-callbacks triggered by ISR from timer interrupt
  for (;;) {}
}
