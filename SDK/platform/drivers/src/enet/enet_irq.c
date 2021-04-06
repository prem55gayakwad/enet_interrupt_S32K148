/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * NXP Confidential. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */
 
 /*!
 * @file enet_irq.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, external could be made static.
 * The functions are called by the interrupt controller when the appropriate event
 * occurs.
 *
 */

#include "enet_hw_access.h"

#if (defined(MPC574x_SERIES) || defined(S32R_SERIES))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET0_Tx_IRQHandler(void);
void ENET0_Rx_IRQHandler(void);
void ENET0_Err_IRQHandler(void);
void ENET0_Timer_IRQHandler(void);
#if (FEATURE_ENET_RING_COUNT > 1U)
void ENET0_Tx_1_IRQHandler(void);
void ENET0_Rx_1_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
void ENET0_Tx_2_IRQHandler(void);
void ENET0_Rx_2_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
#if FEATURE_ENET_HAS_RECEIVE_PARSER
void ENET0_Parser_IRQHandler(void);
#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */
#endif /* (ENET_INSTANCE_COUNT > 0U) */

#if (ENET_INSTANCE_COUNT > 1U)
void ENET1_Tx_IRQHandler(void);
void ENET1_Rx_IRQHandler(void);
void ENET1_Err_IRQHandler(void);
void ENET1_Timer_IRQHandler(void);
#if (FEATURE_ENET_RING_COUNT > 1U)
void ENET1_Tx_1_IRQHandler(void);
void ENET1_Rx_1_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
void ENET1_Tx_2_IRQHandler(void);
void ENET1_Rx_2_IRQHandler(void);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
#if FEATURE_ENET_HAS_RECEIVE_PARSER
void ENET1_Parser_IRQHandler(void);
#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */
#endif /* (ENET_INSTANCE_COUNT > 1U) */

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of ENET0 IRQ handler for transmit interrupts. */
void ENET0_Tx_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for receive interrupts. */
void ENET0_Rx_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for error interrupts. */
void ENET0_Err_IRQHandler(void)
{
    ENET_WakeIRQHandler(0);
    ENET_ErrorIRQHandler(0);
    ENET_TimerIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for timer interrupts. */
void ENET0_Timer_IRQHandler(void)
{
    ENET_TimerIRQHandler(0);
}

#if (FEATURE_ENET_RING_COUNT > 1U)

/* Implementation of ENET0 IRQ handler for transmit interrupts for ring 1. */
void ENET0_Tx_1_IRQHandler(void)
{
    ENET_Transmit1IRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for receive interrupts for ring 1. */
void ENET0_Rx_1_IRQHandler(void)
{
    ENET_Receive1IRQHandler(0);
}

#endif /* (FEATURE_ENET_RING_COUNT > 1U) */

#if (FEATURE_ENET_RING_COUNT > 2U)

/* Implementation of ENET0 IRQ handler for transmit interrupts for ring 2. */
void ENET0_Tx_2_IRQHandler(void)
{
    ENET_Transmit2IRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for receive interrupts for ring 2. */
void ENET0_Rx_2_IRQHandler(void)
{
    ENET_Receive2IRQHandler(0);
}

#endif /* (FEATURE_ENET_RING_COUNT > 2U) */

#if FEATURE_ENET_HAS_RECEIVE_PARSER

/* Implementation of ENET0 IRQ handler for the receive parser. */
void ENET0_Parser_IRQHandler(void)
{
    ENET_ParserIRQHandler(0);
}

#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */

#endif /* (ENET_INSTANCE_COUNT > 0U) */

#if (ENET_INSTANCE_COUNT > 1U)

/* Implementation of ENET1 IRQ handler for transmit interrupts. */
void ENET1_Tx_IRQHandler(void)
{
    ENET_TransmitIRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for receive interrupts. */
void ENET1_Rx_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for error interrupts. */
void ENET1_Err_IRQHandler(void)
{
    ENET_WakeIRQHandler(1);
    ENET_ErrorIRQHandler(1);
    ENET_TimerIRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for timer interrupts. */
void ENET1_Timer_IRQHandler(void)
{
    ENET_TimerIRQHandler(1);
}

#if (FEATURE_ENET_RING_COUNT > 1U)

/* Implementation of ENET1 IRQ handler for transmit interrupts for ring 1. */
void ENET1_Tx_1_IRQHandler(void)
{
    ENET_Transmit1IRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for receive interrupts for ring 1. */
void ENET1_Rx_1_IRQHandler(void)
{
    ENET_Receive1IRQHandler(1);
}

#endif /* (FEATURE_ENET_RING_COUNT > 1U) */

#if (FEATURE_ENET_RING_COUNT > 2U)

/* Implementation of ENET1 IRQ handler for transmit interrupts for ring 2. */
void ENET1_Tx_2_IRQHandler(void)
{
    ENET_Transmit2IRQHandler(1);
}

/* Implementation of ENET1 IRQ handler for receive interrupts for ring 2. */
void ENET1_Rx_2_IRQHandler(void)
{
    ENET_Receive2IRQHandler(1);
}

#endif /* (FEATURE_ENET_RING_COUNT > 2U) */

#if FEATURE_ENET_HAS_RECEIVE_PARSER

/* Implementation of ENET0 IRQ handler for the receive parser. */
void ENET1_Parser_IRQHandler(void)
{
    ENET_ParserIRQHandler(1);
}

#endif /* FEATURE_ENET_HAS_RECEIVE_PARSER */

#endif /* (ENET_INSTANCE_COUNT > 1U) */

#elif (defined(CPU_S32K148) || defined(CPU_SJA1110))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET_TX_IRQHandler(void);
void ENET_RX_IRQHandler(void);
void ENET_ERR_IRQHandler(void);
void ENET_WAKE_IRQHandler(void);
void ENET_TIMER_IRQHandler(void);
#endif /* (ENET_INSTANCE_COUNT > 0U) */

/*******************************************************************************
 * Code
 ******************************************************************************/
 
#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of ENET0 IRQ handler for transmit interrupts. */
void ENET_TX_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for receive interrupts. */
void ENET_RX_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for error interrupts. */
void ENET_ERR_IRQHandler(void)
{
    ENET_ErrorIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for wakeup interrupts. */
void ENET_WAKE_IRQHandler(void)
{
    ENET_WakeIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for timer interrupts. */
void ENET_TIMER_IRQHandler(void)
{
    ENET_TimerIRQHandler(0);
}

#endif /* (ENET_INSTANCE_COUNT > 0U) */

#elif (defined(CPU_S32V234))

/*******************************************************************************
 * Default interrupt handlers signatures
 ******************************************************************************/
#if (ENET_INSTANCE_COUNT > 0U)
void ENET_TX_IRQHandler(void);
void ENET_RX_IRQHandler(void);
void ENET_Err_IRQHandler(void);
void ENET_Timer_IRQHandler(void);
#endif /* (ENET_INSTANCE_COUNT > 0U) */

/*******************************************************************************
 * Code
 ******************************************************************************/
 
#if (ENET_INSTANCE_COUNT > 0U)

/* Implementation of ENET0 IRQ handler for transmit interrupts. */
void ENET_TX_IRQHandler(void)
{
    ENET_TransmitIRQHandler(0);
#if (FEATURE_ENET_RING_COUNT > 1U)
	ENET_Transmit1IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
	ENET_Transmit2IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
}

/* Implementation of ENET0 IRQ handler for receive interrupts. */
void ENET_RX_IRQHandler(void)
{
    ENET_ReceiveIRQHandler(0);
#if (FEATURE_ENET_RING_COUNT > 1U)
    ENET_Receive1IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 1U) */
#if (FEATURE_ENET_RING_COUNT > 2U)
    ENET_Receive2IRQHandler(0);
#endif /* (FEATURE_ENET_RING_COUNT > 2U) */
}

/* Implementation of ENET0 IRQ handler for error interrupts. */
void ENET_Err_IRQHandler(void)
{
    ENET_ErrorIRQHandler(0);
	ENET_ParserIRQHandler(0);
	ENET_WakeIRQHandler(0);
}

/* Implementation of ENET0 IRQ handler for timer interrupts. */
void ENET_Timer_IRQHandler(void)
{
    ENET_TimerIRQHandler(0);
}

#endif /* (ENET_INSTANCE_COUNT > 0U) */

#else
    #error "No valid CPU defined!"
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
