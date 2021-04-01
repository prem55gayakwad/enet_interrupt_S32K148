/*
 * app.c
 */

#include "app_config.h"

#include <board_access.h>

#include "app.h"


uint8_t ethMacAddrBroadcast[6] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
uint8_t ethMacAddrTgt[6] = {0x11U, 0x22U, 0x33U, 0x77U, 0x88U, 0x99U};
uint8_t ethMacAddrSrc[6] = {0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U};

static app_enet_t AppEnet;

void link_up(uint8_t phy) {
  // this demo only supports 1 external phy (TJA1100 or TJA1101)
  if (phy == 0)
	  AppEnet.PhyLinkUp = true;
}

void link_down(uint8_t phy) {
  // this demo only supports 1 external phy (TJA1100 or TJA1101)
  if (phy == 0)
	  AppEnet.PhyLinkUp = false;
}

void delay(volatile int cycles) {
  /* Delay function - do nothing for a number of cycles */
  while (cycles--);
}

void copyBuff(uint8_t * dest, uint8_t * src, uint32_t len) {
  uint32_t i;

  for (i = 0; i < len; i++) {
    dest[i] = src[i];
  }
}

void rx_callback(uint8_t instance, enet_event_t event, uint8_t ring) {
  (void) instance;

  if (event == ENET_RX_EVENT) {
    enet_buffer_t buff;
    status_t status;

    status = ENET_DRV_ReadFrame(INST_ENET, ring, & buff, NULL);
    if (status == STATUS_SUCCESS) {
      mac_frame_t * frame;

      frame = (mac_frame_t * ) buff.data;

      /* You can process the payload here */
      (void) frame -> payload;

      /* We successfully received a frame -> turn on LED 2 */
      PINS_DRV_ClearPins(GPIO_PORT, (1 << LED1));
      PINS_DRV_SetPins(GPIO_PORT, (1 << LED2));

      ENET_DRV_ProvideRxBuff(INST_ENET, ring, & buff);
    }
  }
}

void app_fast_handler(void) {
  //static uint32_t trigProfile[] = {50, 40, 30, 20, 10, 5, 4, 3, 2, 250};	// trigOut Profile, starts with level=high
  static uint32_t trigProfile[] = {50, 40, 30, 20, 860};	// trigOut Profile, starts with level=high
  static uint32_t period = sizeof(trigProfile) / sizeof(uint32_t);
  static uint32_t cnt, pos;
  static mac_frame_t frame;
  static tx_info txinf;
  static rx_info rxinf;

  uint32_t i;

  if (!cnt)
	  release_trigger_out();

  cnt++;

  // fill-up Eth-Frame
  copyBuff(frame.destAddr, ethMacAddrTgt, 6U);
  copyBuff(frame.srcAddr, ethMacAddrSrc, 6U);

  frame.etherType = 0x0608;

  for (i = 0; i < 64U; i++) {
	  frame.payload[i] = i;
  }
  frame.length = 64;



  if (trigProfile[pos] == cnt)
  {
	// as precise as possible, first create the trigger edge here
	activate_trigger_out();

	cnt = 0;

	pos++;
	if (pos >= period)
	{
		uint8_t status;

		status=enet_send(&frame,&txinf); //<send Enet on every period start
		//app check
		 if (status!=1) {

		  AppEnet.error_count++;
		  }
		 else
		 {
			 AppEnet.last_tx_time_sent=txinf.time_stamp;
			 AppEnet.last_rx_time_received=rxinf.time_stamp_rx;
			 AppEnet.header_send=rxinf.header;
		 }
		pos = 0;

	}
  }
}


// called by ISR-Timer each 100 ms
void app_slow_handler(void)
{
	static uint32_t cnt;

	cnt++;

	if (AppEnet.error_count>0)
	{
	  set_led(MASK_LED_RED);

	}
	if (cnt > 10)	// 1 sec
	{
		cnt = 0;
		toggle_led(MASK_LED_GREEN);		// alive LED
		clear_led(MASK_LED_BLUE);;		// clear trigger
	}

}


void app_trigger_in_handler(void)
{

	set_led(MASK_LED_BLUE);

}

