/***********************************************************************************************************************
 * This file was generated by the S32 Configuration Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Configuration Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v7.0
processor: S32K148
package_id: S32K148_LQFP144
mcu_data: s32sdk_s32k1xx_rtm_400
processor_version: 0.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: c8c1c60f-278f-410a-9763-9bf2572e4dfe
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "peripherals_enet_config_1.h"

/*******************************************************************************
 * enet_config_1 initialization code
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'enet_config_1'
- type: 'enet_config'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'enet'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'ENET'
- config_sets:
  - enet:
    - enet_state_name: 'enetState'
    - enet_mac: '22:33:44:55:66:77'
    - enetCfg:
      - name: 'enetInitConfig'
      - readonly: 'false'
      - enetCfg_maxFrameLen: '1518'
      - callback: 'enet_cb'
      - enetCfg_interrupts:
        - enetCfg_rxInt: 'true'
        - enetCfg_txInt: 'false'
        - enetCfg_errInt: 'true'
        - enetCfg_wakeInt: 'false'
        - enetCfg_timerInt: 'false'
      - enetCfg_miiConfig:
        - enetCfg_miiMode: 'ENET_RMII_MODE'
        - enetCfg_miiSpeed: 'ENET_MII_SPEED_100M'
        - enetCfg_miiDuplex: 'ENET_MII_FULL_DUPLEX'
      - enetCfg_txAccelerConfig:
        - ENET_TX_ACCEL_ENABLE_SHIFT16: 'false'
        - ENET_TX_ACCEL_INSERT_IP_CHECKSUM: 'false'
        - ENET_TX_ACCEL_INSERT_PROTO_CHECKSUM: 'false'
      - enetCfg_rxAccelerConfig:
        - ENET_RX_ACCEL_REMOVE_PAD: 'false'
        - ENET_RX_ACCEL_ENABLE_IP_CHECK: 'false'
        - ENET_RX_ACCEL_ENABLE_PROTO_CHECK: 'false'
        - ENET_RX_ACCEL_ENABLE_MAC_CHECK: 'false'
        - ENET_RX_ACCEL_ENABLE_SHIFT16: 'false'
      - enetCfg_rxSpecialConfig:
        - ENET_RX_CONFIG_ENABLE_PAYLOAD_LEN_CHECK: 'false'
        - ENET_RX_CONFIG_STRIP_CRC_FIELD: 'false'
        - ENET_RX_CONFIG_FORWARD_PAUSE_FRAMES: 'false'
        - ENET_RX_CONFIG_REMOVE_PADDING: 'false'
        - ENET_RX_CONFIG_ENABLE_FLOW_CONTROL: 'false'
        - ENET_RX_CONFIG_REJECT_BROADCAST_FRAMES: 'false'
        - ENET_RX_CONFIG_ENABLE_PROMISCUOUS_MODE: 'false'
        - ENET_RX_CONFIG_ENABLE_MII_LOOPBACK: 'false'
      - enetCfg_txSpecialConfig:
        - ENET_TX_CONFIG_DISABLE_CRC_APPEND: 'false'
        - ENET_TX_CONFIG_ENABLE_MAC_ADDR_INSERTION: 'false'
    - enetCfg_ringConfig:
      - 0:
        - enet_rx_size: '1'
        - enet_tx_size: '1'
    - enetTimerCfg_enable: 'false'
    - enetTimerCfg:
      - name: 'enetTimerInitConfig'
      - readonly: 'false'
      - enetTimerCfg_timerPeriod: '1000000000'
      - enetTimerCfg_timerInc: '1'
      - enetTimerCfg_correctionPeriod: '1'
      - enetTimerCfg_correctionInc: '1'
      - enetTimerCfg_irqEnable: 'false'
      - enetTimerCfg_callback: 'NULL'
    - enetTimerCfg_channels: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files in application code.
 *
 */
/*! @brief Number of receive buffer descriptors for ring  0 */
#define ENET_RXBD_NUM_0  (1U)
/*! @brief Number of transmit buffer descriptors for ring  0 */
#define ENET_TXBD_NUM_0  (1U)

/*! @brief Driver state structure which holds driver runtime data */
enet_state_t enetState;

/*! @brief The MAC address of the module */
uint8_t enet_MacAddr[6] = {0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

/*! @brief Module configuration structures */
enet_config_t enetInitConfig = {
	.interrupts      = (uint32_t)ENET_RX_FRAME_INTERRUPT | (uint32_t)ENET_BABR_INTERRUPT | ENET_BABT_INTERRUPT | ENET_EBERR_INTERRUPT | ENET_LATE_COLLISION_INTERRUPT | ENET_RETRY_LIMIT_INTERRUPT | ENET_UNDERRUN_INTERRUPT | ENET_PAYLOAD_RX_INTERRUPT,
	.maxFrameLen     = 1518U,
	.miiMode         = ENET_RMII_MODE,
	.miiSpeed        = ENET_MII_SPEED_100M,
	.miiDuplex       = ENET_MII_FULL_DUPLEX,
	.rxAccelerConfig = 0,
	.txAccelerConfig = 0,
	.rxConfig        = 0,
	.txConfig        = 0,
	.ringCount       = ENET_NUM_RINGS,
	.callback        = enet_cb
};

/*! @brief Receive buffer descriptors for ring  0 */
ALIGNED(FEATURE_ENET_BUFFDESCR_ALIGNMENT) static enet_buffer_descriptor_t enet_rxBuffDescrip0[ENET_RXBD_NUM_0];
/*! @brief Transmit buffer descriptors for ring  0 */
ALIGNED(FEATURE_ENET_BUFFDESCR_ALIGNMENT) static enet_buffer_descriptor_t enet_txBuffDescrip0[ENET_TXBD_NUM_0];
/*! @brief Receive data buffers for ring  0 */
ALIGNED(FEATURE_ENET_BUFF_ALIGNMENT) static uint8_t enet_rxDataBuff0[ENET_RXBD_NUM_0 * ENET_BUFF_ALIGN(1518U)];

/*! @brief Buffer configuration structures */
enet_buffer_config_t enet_buffConfigArr[] = {
	{ 
		ENET_RXBD_NUM_0,
		ENET_TXBD_NUM_0,
		&enet_rxBuffDescrip0[0],
		&enet_txBuffDescrip0[0],
		&enet_rxDataBuff0[0]
	}, 
};


