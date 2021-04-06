/***********************************************************************************************************************
 * This file was generated by the S32 Config Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef lpit_config_1_H
#define lpit_config_1_H

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The global macro will be used in function call of the module.
 *
 */
/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "lpit_driver.h"

/*******************************************************************************
 * Definitions 
 ******************************************************************************/

/*Device instance number */
#define INST_LPIT_CONFIG_1  (0U)

/*******************************************************************************
 * Global variables 
 ******************************************************************************/

/* LPIT global configuration */
extern const lpit_user_config_t lpit_InitConfig;

/* LPIT channel configuration */
extern lpit_user_channel_config_t lpit_1ms_ChnConfig;

extern lpit_user_channel_config_t lpit_100ms_ChnConfig;



#endif /* lpit_config_1_H */
