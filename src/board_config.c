/*
 * board_config.c
 *
 *  Created on: 11 Jan 2021
 *      Author: rainer
 */
#include <board_access.h>
#include "board_config.h"

void config_hw() {
  //Enet
  CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
  CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

  status_t error;
  /* Configure clocks for PORT */
  error = CLOCK_DRV_Init( & clockMan1_InitConfig0);
  DEV_ASSERT(error == STATUS_SUCCESS);
  /* Set pins as GPIO */
  error = PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
  DEV_ASSERT(error == STATUS_SUCCESS);


  // Configure ENET

  ENET_DRV_Init(INST_ENET, & enetState, & enetInitConfig, enet_buffConfigArr, enet_MacAddr);

  ENET_DRV_EnableMDIO(INST_ENET, false);

  // TimeStamping
      ENET_DRV_TimerStart(INST_ENET);
      ENET_DRV_TimerSetCorrection(INST_ENET, 1, 1);

  // Configure PHY
  error = PHY_FrameworkInit(phyConfig, phyDrivers);
  DEV_ASSERT(error == STATUS_SUCCESS);
  error = PHY_Init(0);
  DEV_ASSERT(error == STATUS_SUCCESS);


  /* Install LPIT_ISR as LPIT interrupt handler */
  INT_SYS_InstallHandler(LPIT0_Ch0_IRQn, & lpit_isr_1, NULL);
  INT_SYS_InstallHandler(LPIT0_Ch1_IRQn, & lpit_isr_100, NULL);
  INT_SYS_InstallHandler(PORTE_IRQn, & isr_port_e, NULL);
  INT_SYS_EnableIRQ(PORTE_IRQn);

  /* Initialize LPIT instance 0
   *  -   Reset and enable peripheral
   */
  LPIT_DRV_Init(INST_LPIT_CONFIG_1, & lpit_InitConfig);
  /* Initialize LPIT channel 0 and configure it as a periodic counter
   * which is used to generate an interrupt every second.
   */
  /* Initialize LPIT channel 0 and configure it as a periodic counter
   * which is used to generate an interrupt every second.
   */
  error = LPIT_DRV_InitChannel(INST_LPIT_CONFIG_1, LPIT_CHANNEL_1MS, & lpit_1ms_ChnConfig);
  DEV_ASSERT(error == STATUS_SUCCESS);

  error = LPIT_DRV_InitChannel(INST_LPIT_CONFIG_1, LPIT_CHANNEL_100MS, & lpit_100ms_ChnConfig);
  DEV_ASSERT(error == STATUS_SUCCESS);

  /* Start LPIT0 channel 0 and 1 counter */
  LPIT_DRV_StartTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL_1MS) | (1 << LPIT_CHANNEL_100MS));

}
