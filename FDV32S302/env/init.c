/**
  ******************************************************************************
  * @file    init.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-24
  * @brief   This file provides the processing entry for all exception
  *			 handling and peripheral interrupts.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @defgroup FDV32S302_INIT
  * @{
  */

/**
  * @brief Weak declaration of exception and interrupt handlers
  */

__attribute__((weak)) void MSOFT_IntHandler(void){};
__attribute__((weak)) void MTIM_IntHandler(void){};
__attribute__((weak)) void MEXP_Handler(void){};
__attribute__((weak)) void NMI_Handler(void){};
__attribute__((weak)) void PMU_IrqHandler(void){};
__attribute__((weak)) void LPT_IrqHandler(void){};
__attribute__((weak)) void TIMER1_IrqHandler(void){};
__attribute__((weak)) void TIMER2_IrqHandler(void){};
__attribute__((weak)) void TIMER3_IrqHandler(void){};
__attribute__((weak)) void TIMER4_IrqHandler(void){};
__attribute__((weak)) void UART1_IrqHandler(void){};
__attribute__((weak)) void UART2_IrqHandler(void){};
__attribute__((weak)) void SPI_IrqHandler(void){};
__attribute__((weak)) void ANAC_IrqHandler(void){};
__attribute__((weak)) void EFC_IrqHandler(void){};
__attribute__((weak)) void IOM_IrqHandler(void){};
__attribute__((weak)) void I2C_IrqHandler(void){};
__attribute__((weak)) void RTC_IrqHandler(void){};
__attribute__((weak)) void TWC_IrqHandler(void){};
__attribute__((weak)) void LPU_IrqHandler(void){};

/**
  * @brief  Handling Machine Exception Traps.
  * @param  mcause: The cause of machine abnormality.
  * @param  epc: The PC value of the instruction the processor was executing
  *         before the exception was entered.
  * @retval None
  */
unsigned int handle_trap(unsigned int mcause, unsigned int epc)
{
	/* External Machine-Level interrupt from PLIC */
	if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == EXP_M_EXT_INT) && (PLIC_GetCLAIM() == TIMER2_IRQn))
	{
		/* Handle the corresponding interrupt */
		TIMER2_IrqHandler();
		
		/* Clear interrupt source */
		PLIC_SetCLAIM(TIMER2_IRQn);
	}

	/* Returns the return address of the exception */
	return epc;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

