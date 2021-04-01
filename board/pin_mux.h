#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "pins_driver.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*! @brief Definitions/Declarations for BOARD_InitPins Functional Group */
/*! @brief User definition pins */
#define LED_RED_PORT    PTE
#define LED_RED_PIN     21U
#define LED_GREEN_PORT    PTE
#define LED_GREEN_PIN     22U
#define TRIG_OUT_PORT    PTE
#define TRIG_OUT_PIN     1U
#define LED_BLUE_PORT    PTE
#define LED_BLUE_PIN     23U
#define TRIG_IN_PORT    PTE
#define TRIG_IN_PIN     0U
/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0 26
/*! @brief User configuration structure */
extern pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];


#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

