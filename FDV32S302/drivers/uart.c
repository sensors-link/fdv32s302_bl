/**
  ******************************************************************************
  * @file    uart.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-27
  * @brief   This file provides all the UART firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "sysc.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @defgroup UART
  * @brief UART driver modules
  * @{
  */

/** @defgroup UART_Private_Defines
  * @{
  */

/* UART_SCON register Mask */
#define UART_SCON_CLEAR_Mask ((u32)0xFFFFF0BF)

/**
  * @}
  */

/** @defgroup UART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the UART peripheral registers to their default reset values.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @retval None
  */
void UART_DeInit(UART_TypeDef *UARTx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	if (UARTx == UART1)
	{
		/* Reset the UART1 module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_UART1);
	}
	else if (UARTx == UART2)
	{
		/* Reset the UART2 module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_UART2);
	}
}

/**
  * @brief  Initializes the UARTx peripheral according to the specified parameters
  *         in the UART_InitStruct.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
  *         the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
	u32 tempreg = 0, bauddiv = 0;
	SYSC_ClocksTypeDef SYSC_Clocks;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_UART_PARITY(UART_InitStruct->UART_Parity));
	PARAM_CHECK(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));

	/*---------------------------- UART SCON Configuration -----------------------*/
	tempreg = UARTx->SCON;
	/* Clear UART_SCON initialization configuration bit */
	tempreg &= UART_SCON_CLEAR_Mask;

	/* Configure UART Parity and Work Mode ---------------------------------------*/
	/* Set the PACFG and SM01 bits according to UART_Parity value */
	tempreg |= UART_InitStruct->UART_Parity;

	/* Enable UART reception */
	tempreg |= UART_SCON_REN;

	/* Write to UART SCON */
	UARTx->SCON = tempreg;

	/*---------------------------- UART BDIV Configuration -----------------------*/
	/* Get system clock */
	SYSC_GetClocksFreq(&SYSC_Clocks);

	/* Baud rate calculation for UART mode 1/2/3 */
	bauddiv = SYSC_Clocks.PCLK_Frequency * 64 / (16 * UART_InitStruct->UART_BaudRate);

	/* Check the value written to the baud rate register (BDIV) */
	PARAM_CHECK(IS_UART_BAUDDIV(bauddiv));

	/* Write to UART BDIV */
	UARTx->BDIV = bauddiv;
}

/**
  * @brief  Sets the slave device address and mask for the selected UARTx peripheral.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  Addr: Specifies the slave device address of the UARTx peripheral.
  * @param  Mask: Specifies the slave device address mask for the UARTx peripheral.
  * @retval None
  */
void UART_SetAddrAndMask(UART_TypeDef *UARTx, u8 Addr, u8 Mask)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	/* Set UARTx slave device address */
	UARTx->SADDR = Addr;
	/* Set UARTx slave device address mask */
	UARTx->SADEN = Mask;
}

/**
  * @brief  Enables or disables multi-master communication for specified UARTx peripherals.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  NewState: The new state of multi-master communication.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_SM2Cmd(UART_TypeDef *UARTx, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enables multi-master communication for selected UARTx peripherals */
		UARTx->SCON |= UART_SCON_SM2;
	}
	else
	{
		/* Disable multi-master communication for selected UARTx peripherals */
		UARTx->SCON &= ~UART_SCON_SM2;
	}
}

/**
  * @brief  Enables or disables start bit detection for selected UARTx peripherals.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  NewState: New state of start bit detection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_StartDetectCmd(UART_TypeDef *UARTx, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable start bit detection for selected UARTx peripherals */
		UARTx->SCON |= UART_SCON_SFDEN;
	}
	else
	{
		/* Disable start bit detection for selected UARTx peripherals */
		UARTx->SCON &= ~UART_SCON_SFDEN;
	}
}

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg UART_IT_RXSIEN: Receive START bit interrupt
  *     @arg UART_IT_RIEN: receive interrupt
  *     @arg UART_IT_TIEN: send interrupt
  * @param  NewState: new state of the specified UART interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(UART_TypeDef *UARTx, u8 UART_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_UART_CONFIG_IT(UART_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected UART interrupts */
		UARTx->SCON |= UART_IT;
	}
	else
	{
		/* Disable the selected UART interrupts */
		UARTx->SCON &= ~UART_IT;
	}
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  UART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg UART_FLAG_RXSF: Receive start bit flag
  *     @arg UART_FLAG_PE: Receive parity error flag
  *     @arg UART_FLAG_FE: Receive frame error flag
  *     @arg UART_FLAG_RI: Receive complete interrupt flag
  *     @arg UART_FLAG_TI: Transmit complete interrupt flag
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(UART_TypeDef *UARTx, u8 UART_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_UART_GET_FLAG(UART_FLAG));

	/* Check the status of the UART flag */
	if (UARTx->ISR & UART_FLAG)
	{
		/* UART_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* UART_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the UART_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg UART_IT_RXSIEN: Receive START bit interrupt
  *     @arg UART_IT_RIEN: receive interrupt
  *     @arg UART_IT_TIEN: send interrupt
  * @retval The new state of UART_IT (SET or RESET).
  */
ITStatus UART_GetITStatus(UART_TypeDef *UARTx, u8 UART_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_UART_GET_IT(UART_IT));

	/* Check the status of the specified UART interrupt */
	if ((UARTx->SCON & UART_IT) && (UARTx->ISR & (UART_IT >> 1)))
	{
		/* UART_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* UART_IT is reset */
		bitstatus = RESET;
	}
	/* Return the UART_IT status */
	return bitstatus;
}

/**
  * @brief  Clears the UARTx's pending flags.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  UART_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg UART_FLAG_RXSF: Receive start bit flag
  *     @arg UART_FLAG_PE: Receive parity error flag
  *     @arg UART_FLAG_FE: Receive frame error flag
  *     @arg UART_FLAG_RI: Receive complete interrupt flag
  *     @arg UART_FLAG_TI: Transmit complete interrupt flag
  * @retval None
  */
void UART_ClearFlag(UART_TypeDef *UARTx, u8 UART_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));
	PARAM_CHECK(IS_UART_CLEAR_FLAG(UART_FLAG));

	/* Clear the selected UART flags */
	UARTx->ISR = UART_FLAG;
}

/**
  * @brief  Check if bit 8 of UARTx's receive data is set.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetRxBit8(UART_TypeDef *UARTx)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	if (UARTx->SCON & UART_SCON_RB8)
	{
		/* The 8th bit of the received data is set */
		bitstatus = SET;
	}
	else
	{
		/* The 8th bit of the received data is reset */
		bitstatus = RESET;
	}
	/* Returns the status of the 8th bit of the received data */
	return bitstatus;
}

/**
  * @brief  Clear the 8th bit of UARTx's receive data.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @retval None
  */
void UART_ClrRxBit8(UART_TypeDef *UARTx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	/* Clear the 8th bit of UARTx's receive data */
	UARTx->SCON &= ~UART_SCON_RB8;
}

/**
  * @brief  Set the 8th bit of UARTx's transmit data.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @retval None
  */
void UART_SetTxBit8(UART_TypeDef *UARTx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	/* Set the 8th bit of UARTx's transmit data */
	UARTx->SCON |= UART_SCON_TB8;
}

/**
  * @brief  Clear the 8th bit of UARTx's transmit data.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @retval None
  */
void UART_ClrTxBit8(UART_TypeDef *UARTx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	/* Clear the 8th bit of UARTx's transmit data */
	UARTx->SCON &= ~UART_SCON_TB8;
}

/**
  * @brief  Send a data through the UARTx peripheral.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void UART_SendData(UART_TypeDef *UARTx, u8 Data)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	/* Write in the SBUF register the data to be sent */
	UARTx->SBUF = Data;
}

/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *     UART1, UART2.
  * @retval The value of the received data.
  */
u8 UART_ReceiveData(UART_TypeDef *UARTx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_ALL_PERIPH(UARTx));

	/* Return the data in the SBUF register */
	return (u8)(UARTx->SBUF);
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

