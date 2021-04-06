/*
 * board_config.h
 *
 *  Created on: 11 Jan 2021
 *      Author: rainer
 */

#ifndef BOARD_CONFIG_H_
#define BOARD_CONFIG_H_

#include "sdk_project_config.h"
#include "interrupt_manager.h"

#define LPIT_CHANNEL_1MS	0
#define LPIT_CHANNEL_100MS	1

void config_hw();
void app_fast_handler(void);
void app_slow_handler(void);

void app_trigger_in_handler(void);

#endif /* BOARD_CONFIG_H_ */
