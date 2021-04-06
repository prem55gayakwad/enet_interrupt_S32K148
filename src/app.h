/*
 * app.h
 */

#ifndef APP_H_
#define APP_H_


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "sdk_project_config.h"

#include <interrupt_manager.h>

#include "pin_mux.h"

#include "phy.h"

#include "phy_tja110x.h"

#include "enet_driver.h"

typedef struct{
	uint8_t error_count;
	bool PhyLinkUp;
	mac_frame_t frame;
	mac_frame_t * RxFrame; // buffer data comes from ENET driver
	enet_buffer_t buff, rxBuff;
	enet_tx_enh_info_t txInfo;
	enet_rx_enh_info_t rxInfo;
	int32_t last_tx_time_sent;
	int32_t last_rx_time_received;
	int32_t header_send;
 }app_enet_t;


#define EVB

#ifdef EVB
#define GPIO_PORT PTE
#define PCC_CLOCK PCC_PORTE_CLOCK
#define LED1 21U
#define LED2 22U
#else
#define GPIO_PORT PTC
#define PCC_CLOCK PCC_PORTC_CLOCK
#define LED1 0 U
#define LED2 1 U
#endif


void app_fast_handler(void);
void app_slow_handler(void);
void app_trigger_in_handler(void);

#endif /* APP_H_ */
