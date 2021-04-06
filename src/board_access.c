/*
 * boardr_access.c
 */

#include "sdk_project_config.h"

#include "interrupt_manager.h"

#include "board_config.h"

#include <board_access.h>


// local function pointers to be configured by application
static cb_fast_t fast_cb;
static cb_slow_t slow_cb;
static cb_trigger_in_t trig_in_cb;
static mac_frame_t * RxFrame; // buffer data comes from ENET driver

void config_fast_cb(cb_fast_t cb_func) {
  fast_cb = cb_func;
}

void config_slow_cb(cb_slow_t cb_func) {
  slow_cb = cb_func;
}

void config_trigger_in_cb(cb_trigger_in_t cb_func) {
  trig_in_cb = cb_func;
}

// registered interrupt-handler for 1 ms
void lpit_isr_1(void) {
  if (LPIT_DRV_GetInterruptFlagTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL_1MS))) {
    /* Clear LPIT channel flag */
    LPIT_DRV_ClearInterruptFlagTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL_1MS));

    fast_cb();
  }

}

// registered interrupt-handler for 100 ms
void lpit_isr_100(void) {
  static uint32_t cnt;

  cnt++;

  if (LPIT_DRV_GetInterruptFlagTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL_100MS))) {
    /* Clear LPIT channel flag */
    LPIT_DRV_ClearInterruptFlagTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL_100MS));

    slow_cb();
  }
}

void isr_port_e(void) {
  trig_in_cb();
  PINS_DRV_ClearPinIntFlagCmd(PORTE, TRIG_IN_PIN);
}

void release_trigger_out(void) {
  PINS_DRV_SetPins(TRIG_OUT_PORT, 1 << TRIG_OUT_PIN);
}

void activate_trigger_out(void) {
  PINS_DRV_ClearPins(TRIG_OUT_PORT, 1 << TRIG_OUT_PIN);
}

void toggle_led(int mask) {
  if (mask & MASK_LED_RED)
    PINS_DRV_TogglePins(LED_RED_PORT, (1 << LED_RED_PIN));
  if (mask & MASK_LED_GREEN)
    PINS_DRV_TogglePins(LED_GREEN_PORT, (1 << LED_GREEN_PIN));
  if (mask & MASK_LED_BLUE)
    PINS_DRV_TogglePins(LED_BLUE_PORT, (1 << LED_BLUE_PIN));

}

void clear_led(int mask) {
  if (mask & MASK_LED_RED)
    PINS_DRV_ClearPins(LED_RED_PORT, (1 << LED_RED_PIN));
  if (mask & MASK_LED_GREEN)
    PINS_DRV_ClearPins(LED_GREEN_PORT, (1 << LED_GREEN_PIN));
  if (mask & MASK_LED_BLUE)
    PINS_DRV_ClearPins(LED_BLUE_PORT, (1 << LED_BLUE_PIN));

}

void set_led(int mask) {
  if (mask & MASK_LED_RED)
    PINS_DRV_SetPins(LED_RED_PORT, (1 << LED_RED_PIN));
  if (mask & MASK_LED_GREEN)
    PINS_DRV_SetPins(LED_GREEN_PORT, (1 << LED_GREEN_PIN));
  if (mask & MASK_LED_BLUE)
    PINS_DRV_SetPins(LED_BLUE_PORT, (1 << LED_BLUE_PIN));

}

int32_t enet_send(mac_frame_t * pframe, tx_info * txinf)
{
  status_t state;
  bool linkStatus;
  enet_tx_enh_info_t txInfo;
  enet_buffer_t buff;

  state = PHY_GetLinkStatus(0, & linkStatus); //board_access (1)

  buff.data = (uint8_t * ) pframe;
  buff.length = pframe -> length + 14; // no VLAN: 6+6+2

  if (linkStatus)
  {

    state = ENET_DRV_SendFrame(INST_ENET, 0U, & buff, NULL);

    if (state == STATUS_SUCCESS)
    {
      int j = 100;
      do {
        state = ENET_DRV_GetTransmitStatus(INST_ENET, 0U, & buff, & txInfo);
        if (state == STATUS_SUCCESS)
          break;
      } while (--j);

      if (j > 0)
      {
        txinf -> err_Mask = txInfo.errMask;
        txinf -> time_stamp = txInfo.timestamp;
        return 1;
      }
      else
      {
        return -2;
      }
    }
    else
    {
    	return -3;
    }
  }
  else
  {
    return -4; // return value for no link state
  }
}

void enet_cb(uint8_t instance, enet_event_t event, uint8_t ring) // for Rx send
{
  status_t state;
  enet_buffer_t rxBuff;
  enet_rx_enh_info_t rxInfo;
  rx_info * rxinf;
  if (event == ENET_RX_EVENT)
  {
    state = ENET_DRV_ReadFrame(INST_ENET, 0U, & rxBuff, & rxInfo);
    if (state == STATUS_SUCCESS)
    {
    	RxFrame = (mac_frame_t * ) rxBuff.data;
    	rxinf->header=rxInfo.headerLen;
    	rxinf->time_stamp_rx=rxInfo.timestamp;
    // pull internal data-buffer back to driver pool
    }
    ENET_DRV_ProvideRxBuff(INST_ENET, 0U, & rxBuff);
  }
}
