/**
  ******************************************************************************
  * @file    twc.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-26
  * @brief   This file provides all the TWC firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "twc.h"
#include "sysc.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @defgroup TWC
  * @brief TWC driver modules
  * @{
  */

/** @defgroup TWC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the TWC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */ 
void TWC_DeInit(void)
{
	/* Reset the TWC module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TWC);
}

/**
  * @brief  Initializes the TWC SEBUS peripheral according to the parameters
  *         specified in TWC_SEBUSInitStruct.
  * @param  TWC_SEBUSInitStruct: Pointer to an TWC_SEBUSInitTypeDef structure
  *         containing configuration information for the TWC SEBUS peripheral.
  * @retval None
  */
void TWC_SEBUSInit(TWC_SEBUSInitTypeDef *TWC_SEBUSInitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_TWC_SEBUS_MODE(TWC_SEBUSInitStruct->TWC_SEBUSMode));
	PARAM_CHECK(IS_TWC_TX_DEFAULT_LEVEL(TWC_SEBUSInitStruct->TWC_TxDefaultLevel));
	PARAM_CHECK(IS_TWC_RX_DECODE(TWC_SEBUSInitStruct->TWC_RXDecode));
	PARAM_CHECK(IS_TWC_GLITCH_FILT(TWC_SEBUSInitStruct->TWC_GlitchFilt));
	PARAM_CHECK(IS_TWC_SEBUS_LOW_THR(TWC_SEBUSInitStruct->TWC_StartBLowMin));
	PARAM_CHECK(IS_TWC_SEBUS_LOW_THR(TWC_SEBUSInitStruct->TWC_StartBLowMax));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_StartBHighMin));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_StartBHighMax));
	PARAM_CHECK(IS_TWC_SEBUS_LOW_THR(TWC_SEBUSInitStruct->TWC_DataBLowMin));
	PARAM_CHECK(IS_TWC_SEBUS_LOW_THR(TWC_SEBUSInitStruct->TWC_DataBLowMax));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_Data0BHighMin));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_Data0BHighMax));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_Data1BHighMin));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_Data1BHighMax));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_TxStartGap));
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(TWC_SEBUSInitStruct->TWC_TxStopGap));

	/*---------------------------- TWC CR Configuration -----------------------*/
	tempreg = TWC->CR;

	/* Set up to use the SE_BUS protocol */
	tempreg |= TWC_CR_SEBUSEN;

	if (TWC_SEBUSInitStruct->TWC_SEBUSMode == TWC_SEBUS_MODE_IN_HIGH)
	{
		/* Set SE_BUS mode to 9000 mode */
		tempreg &= ~TWC_CR_SEBUSMODE;
	}
	else
	{
		/* Set SE_BUS mode to EPC mode */
		tempreg |= TWC_CR_SEBUSMODE;
	}

	if (TWC_SEBUSInitStruct->TWC_TxDefaultLevel == TWC_TX_DEFAULT_LEVEL_HIGH)
	{
		/* Set the default level of the TX port to high */
		tempreg &= ~TWC_CR_TXLELCFG;
	}
	else
	{
		/* Set the default level of the TX port to low */
		tempreg |= TWC_CR_TXLELCFG;
	}

	if (TWC_SEBUSInitStruct->TWC_RXDecode == TWC_RX_DEC_MATCH_CMD)
	{
		/* Set only the instructions in TWC_CMDx can generate the flag */
		tempreg &= ~TWC_CR_RXDECCFG;
	}
	else
	{
		/* Set only instructions other than TWC_CMDx can generate the flag */
		tempreg |= TWC_CR_RXDECCFG;
	}

	/* Set receive data digital glitch filtering */
	tempreg &= ~TWC_CR_RXGLITCHFILTCFG;
	tempreg |= TWC_SEBUSInitStruct->TWC_GlitchFilt << TWC_CR_RXGLITCHFILTCFG_pos;

	/* Write to TWC_CR */
	TWC->CR = tempreg;

	/* Set the start bit level width in SE_BUS mode */
	TWC->STARBLOW &= ~TWC_STARBLOW_THR_STARB_LOW_MAX;
	TWC->STARBLOW |= TWC_SEBUSInitStruct->TWC_StartBLowMax << TWC_STARBLOW_THR_STARB_LOW_MAX_pos;

	TWC->STARBLOW &= ~TWC_STARBLOW_THR_STARB_LOW_MIN;
	TWC->STARBLOW |= TWC_SEBUSInitStruct->TWC_StartBLowMin << TWC_STARBLOW_THR_STARB_LOW_MIN_pos;

	
	TWC->STARBHIG &= ~TWC_STARBHIG_THR_STARB_HIG_MAX;
	TWC->STARBHIG |= TWC_SEBUSInitStruct->TWC_StartBHighMax << TWC_STARBHIG_THR_STARB_HIG_MAX_pos;

	TWC->STARBHIG &= ~TWC_STARBHIG_THR_STARB_HIG_MIN;
	TWC->STARBHIG |= TWC_SEBUSInitStruct->TWC_StartBHighMin << TWC_STARBHIG_THR_STARB_HIG_MIN_pos;

	/* Set the data bit level width in SE_BUS mode */
	TWC->DATABLOW &= ~TWC_DATABLOW_THR_DATAB_LOW_MAX;
	TWC->DATABLOW |= TWC_SEBUSInitStruct->TWC_DataBLowMax << TWC_DATABLOW_THR_DATAB_LOW_MAX_pos;
	
	TWC->DATABLOW &= ~TWC_DATABLOW_THR_DATAB_LOW_MIN;
	TWC->DATABLOW |= TWC_SEBUSInitStruct->TWC_DataBLowMin << TWC_DATABLOW_THR_DATAB_LOW_MIN_pos;
	
	TWC->DAT0BHIG &= ~TWC_DAT0BHIG_THR_DAT0B_HIG_MAX;
	TWC->DAT0BHIG |= TWC_SEBUSInitStruct->TWC_Data0BHighMax << TWC_DAT0BHIG_THR_DAT0B_HIG_MAX_pos;
	
	TWC->DAT0BHIG &= ~TWC_DAT0BHIG_THR_DAT0B_HIG_MIN;
	TWC->DAT0BHIG |= TWC_SEBUSInitStruct->TWC_Data0BHighMin << TWC_DAT0BHIG_THR_DAT0B_HIG_MIN_pos;
	
	TWC->DAT1BHIG &= ~TWC_DAT1BHIG_THR_DAT1B_HIG_MAX;
	TWC->DAT1BHIG |= TWC_SEBUSInitStruct->TWC_Data1BHighMax << TWC_DAT1BHIG_THR_DAT1B_HIG_MAX_pos;
	
	TWC->DAT1BHIG &= ~TWC_DAT1BHIG_THR_DAT1B_HIG_MIN;
	TWC->DAT1BHIG |= TWC_SEBUSInitStruct->TWC_Data1BHighMin << TWC_DAT1BHIG_THR_DAT1B_HIG_MIN_pos;

	/* Set the start and end interval for SEBUS to send data */
	TWC->TXMASK &= ~TWC_TXMASK_THR_TX_GAP_STA;
	TWC->TXMASK |= TWC_SEBUSInitStruct->TWC_TxStartGap << TWC_TXMASK_THR_TX_GAP_STA_pos;
	
	TWC->TXMASK &= ~TWC_TXMASK_THR_TX_GAP_STP;
	TWC->TXMASK |= TWC_SEBUSInitStruct->TWC_TxStopGap << TWC_TXMASK_THR_TX_GAP_STP_pos;
}

/**
  * @brief  Initializes the TWC SWANBUS peripheral according to the parameters
  *         specified in TWC_SWANBUSInitStruct.
  * @param  TWC_SWANBUSInitStruct: Pointer to an TWC_SWANBUSInitTypeDef structure
  *         containing configuration information for the TWC SWANBUS peripheral.
  * @retval None
  */
void TWC_SWANBUSInit(TWC_SWANBUSInitTypeDef *TWC_SWANBUSInitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_TWC_TX_DEFAULT_LEVEL(TWC_SWANBUSInitStruct->TWC_TxDefaultLevel));
	PARAM_CHECK(IS_TWC_RX_DECODE(TWC_SWANBUSInitStruct->TWC_RXDecode));
	PARAM_CHECK(IS_TWC_GLITCH_FILT(TWC_SWANBUSInitStruct->TWC_GlitchFilt));
	PARAM_CHECK(IS_TWC_RX_CHECK(TWC_SWANBUSInitStruct->TWC_RxCheck));
	PARAM_CHECK(IS_TWC_TX_CODE(TWC_SWANBUSInitStruct->TWC_TxCode));
	PARAM_CHECK(IS_TWC_TX_PARITY(TWC_SWANBUSInitStruct->TWC_TxParity));
	PARAM_CHECK(IS_TWC_TX_BIT(TWC_SWANBUSInitStruct->TWC_TxBit));
	PARAM_CHECK(IS_TWC_TX_BAUDRATE(TWC_SWANBUSInitStruct->TWC_TxBaudRate));
	PARAM_CHECK(IS_TWC_RX_BAUDRATE(TWC_SWANBUSInitStruct->TWC_RxBaudRate));

	/*---------------------------- TWC CR Configuration -----------------------*/
	tempreg = TWC->CR;

	/* Set up to use the SWAN_BUS protocol */
	tempreg &= ~TWC_CR_SEBUSEN;

	if (TWC_SWANBUSInitStruct->TWC_TxDefaultLevel == TWC_TX_DEFAULT_LEVEL_HIGH)
	{
		/* Set the default level of the TX port to high */
		tempreg &= ~TWC_CR_TXLELCFG;
	}
	else
	{
		/* Set the default level of the TX port to low */
		tempreg |= TWC_CR_TXLELCFG;
	}

	if (TWC_SWANBUSInitStruct->TWC_RXDecode == TWC_RX_DEC_MATCH_CMD)
	{
		/* Set only the instructions in TWC_CMDx can generate the flag */
		tempreg &= ~TWC_CR_RXDECCFG;
	}
	else
	{
		/* Set only instructions other than TWC_CMDx can generate the flag */
		tempreg |= TWC_CR_RXDECCFG;
	}

	/* Set receive data digital glitch filtering */
	tempreg &= ~TWC_CR_RXGLITCHFILTCFG;
	tempreg |= TWC_SWANBUSInitStruct->TWC_GlitchFilt << TWC_CR_RXGLITCHFILTCFG_pos;

	/* Write to TWC_CR */
	TWC->CR = tempreg;

	/*---------------------------- TWC SWCR Configuration -----------------------*/
	tempreg = TWC->SWCR;

	if (TWC_SWANBUSInitStruct->TWC_RxCheck == TWC_RX_CHECK_PARITY)
	{
		/* Set the received data to parity */
		tempreg &= ~TWC_SWCR_RXPARITYCFG;
	}
	else
	{
		/* Set the received data as Hamming code encoding */
		tempreg |= TWC_SWCR_RXPARITYCFG;
	}

	if (TWC_SWANBUSInitStruct->TWC_TxCode == TWC_TX_CODE_NRZ)
	{
		/* Set the send data to NRZ encoding */
		tempreg &= ~TWC_SWCR_TXCODECFG;
	}
	else
	{
		/* Set send data to Manchester encoding */
		tempreg |= TWC_SWCR_TXCODECFG;
	}

	if (TWC_SWANBUSInitStruct->TWC_TxParity == TWC_TX_PARITY_EVEN)
	{
		/* Set send data to even parity */
		tempreg &= ~TWC_SWCR_TXPARITYCFG;
	}
	else
	{
		/* Set send data to odd parity */
		tempreg |= TWC_SWCR_TXPARITYCFG;
	}

	/* Set the 32-bit data valid bit in the TWC_TXD register */
	tempreg &= ~TWC_SWCR_TXBITCFG;
	tempreg |= TWC_SWANBUSInitStruct->TWC_TxBit << TWC_SWCR_TXBITCFG_pos;

	/* Write to TWC_SWCR */
	TWC->SWCR = tempreg;

	/* Set the send data baud rate */
	TWC->SWBR &= ~TWC_SWBR_TXBR;
	TWC->SWBR |= TWC_SWANBUSInitStruct->TWC_TxBaudRate << TWC_SWBR_TXBR_pos;

	/* Set the receive data baud rate */
	TWC->SWBR &= ~TWC_SWBR_RXBR;
	TWC->SWBR |= TWC_SWANBUSInitStruct->TWC_RxBaudRate << TWC_SWBR_RXBR_pos;

	/* Set the boundary between the RX and TX start bits */
	TWC->SWCR &= ~TWC_SWCR_THR_RX_GAP_MAX;
	TWC->SWCR |= TWC_SWANBUSInitStruct->TWC_SWANBUSStartGap << TWC_SWCR_THR_RX_GAP_MAX_pos;
}

/**
  * @brief  Configure the high level hold time of the space code according to the input parameters.
  * @param  HoldVal: Specifies the space code hold time.
  *   This parameter value must be lower than 0x7FF.
  * @retval None
  */
void TWC_SpaceHighHoldConfig(u16 HoldVal)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(HoldVal));

	/* Set space code hold time */
	TWC->SPACEHIG &= ~TWC_SPACEHIG_THR_SPACE_HIG;
	TWC->SPACEHIG |= HoldVal << TWC_SPACEHIG_THR_SPACE_HIG_pos;
}

/**
  * @brief  Configure the level hold time of the rxd according to the input parameters.
  * @param  HoldVal: Specifies the rxd hold time.
  *   This parameter value must be lower than 0x7FF.
  * @retval None
  */
void TWC_RxHoldConfig(u16 HoldVal)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TWC_SEBUS_HIGH_THR(HoldVal));

	/* Set space code hold time */
	TWC->RXMASK &= ~TWC_RXMASK_THR_RX_GAP;
	TWC->RXMASK |= HoldVal << TWC_RXMASK_THR_RX_GAP_pos;
}

/**
  * @brief  Set hardware decode commands and masks for selected CMDx registers.
  * @param  CMDx: Specifies the selected hardware decode instruction register number.
  *   This parameter must be between 1 and 12.
  * @param  Cmd: Specifies the hardware decode command for the selected register.
  *   This parameter must be a 16bit value.
  * @param  Mask: Specifies the hardware decode mask for the selected register.
  *   This parameter must be a 16bit value.
  * @retval None
  */
void TWC_SetCMDAndMask(u8 CMDx, u16 Cmd, u16 Mask)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TWC_CMD(CMDx));

	/* Set hardware decode commands and masks for selected registers */
	TWC->CMD[CMDx - 1] = (Cmd << 16) | Mask;
}

/**
  * @brief  Set the TWC sending mode.
  * @param  Specifies the TWC sending mode.
  *   This parameter can be one of the following values:
  *     @arg TWC_SEND_MODE_SOFT: Software return code
  *     @arg TWC_SEND_MODE_AUTO: The hardware automatically returns the code
  * @retval None
  */
void TWC_SetSendMode(u8 SendMode)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TWC_SEND_MODE(SendMode));

	/* Set the TWC sending mode */
	if (SendMode == TWC_SEND_MODE_SOFT)
	{
		TWC->TXS &= ~TWC_TXS_TXMODE;
	}
	else
	{
		TWC->TXS |= TWC_TXS_TXMODE;
	}
}

/**
  * @brief  Returns the Hamming code check value.
  * @param  None
  * @retval The Hamming code check value.
  */
u8 TWC_GetHanmCheckValue(void)
{
	/* Return the Hamming code check value */
	return ((TWC->STS & TWC_STS_HANMCHKPAR) >> TWC_STS_HANMCHKPAR_pos);
}

/**
  * @brief  Returns the original value of the received checksum.
  * @param  None
  * @retval Check result.
  */
u8 TWC_GetCheckValue(void)
{
	/* Returns the original value of the received checksum */
	return ((TWC->STS & TWC_STS_RXPARITY) >> TWC_STS_RXPARITY_pos);
}

/**
  * @brief  Enable or disable SEBUS automatic coding.
  * @param  NewState: New status of SEBUS automatic encoding.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TWC_AutoCodeCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable SEBUS automatic coding */
		TWC->CR |= TWC_CR_AUTOCODEEN;
	}
	else
	{
		/* Disable SEBUS automatic coding */
		TWC->CR &= ~TWC_CR_AUTOCODEEN;
	}
}

/**
  * @brief  Enable or disable to reverse the received data.
  * @param  NewState: New state of data reversal.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TWC_RecieveInvertCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable receiving data inversion */
		TWC->CR |= TWC_CR_RX_INV_CFG;
	}
	else
	{
		/* Disable receiving data inversion */
		TWC->CR &= ~TWC_CR_RX_INV_CFG;
	}
}

/**
  * @brief  Enable or disable TWC peripheral data hardware reception.
  * @param  NewState: The new state of data hardware reception.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TWC_RecieveCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable TWC peripheral data hardware reception */
		TWC->CR |= TWC_CR_RXRECEN;
	}
	else
	{
		/* Disable TWC peripheral data hardware reception */
		TWC->CR &= ~TWC_CR_RXRECEN;
	}
}

/**
  * @brief  Enable or disable the TWC peripheral to return send data.
  * @param  NewState: The new state of the return sent data.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TWC_ReturnSendCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable TWC peripheral to return send data */
		TWC->TXS |= TWC_TXS_RETURNTXEN;
	}
	else
	{
		/* Disable TWC peripheral to return send data */
		TWC->TXS &= ~TWC_TXS_RETURNTXEN;
	}
}

/**
  * @brief  Enable or disable the TWC peripheral to trans send data.
  * @param  NewState: The new state of the trans sent data.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TWC_TransSendCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable TWC peripheral to trans send data */
		TWC->TXS |= TWC_TXS_TRANSTXEN;
	}
	else
	{
		/* Disable TWC peripheral to trans send data */
		TWC->TXS &= ~TWC_TXS_TRANSTXEN;
	}
}

/**
  * @brief  Enable TWC peripheral software TX start.
  * @param  None
  * @retval None
  */
void TWC_SoftTxStartEnable(void)
{
	/* Enable TWC peripheral software TX start */
	TWC->TXS |= TWC_TXS_SOFTTXSTART;
}

/**
  * @brief  Enables or disables the specified TWC interrupts.
  * @param  TWC_IT: specifies the TWC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg TWC_IT_RXFRMEEND: Normal receive data completion interrupt
  *     @arg TWC_IT_FRMEEND: Entire frame data end interrupt
  * @param  NewState: new state of the specified TWC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TWC_ITConfig(u8 TWC_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TWC_CONFIG_IT(TWC_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected TWC interrupts */
		TWC->INTEN |= TWC_IT;
	}
	else
	{
		/* Disable the selected TWC interrupts */
		TWC->INTEN &= ~TWC_IT;
	}
}

/**
  * @brief  Checks whether the specified TWC flag is set or not.
  * @param  TWC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg TWC_FLAG_STARBFLAG: Start bit valid flag
  *     @arg TWC_FLAG_RXPARERR: Receive parity check error flag
  *     @arg TWC_FLAG_RXBITERR: Receive data bit error flag
  *     @arg TWC_FLAG_RXFRMEERR: Receive data frame error flag
  *     @arg TWC_FLAG_RXMUTEFRME: Correctly receive a frame silent frame flag
  *     @arg TWC_FLAG_AUTOCODEERR: Automatic unique encoding error flag
  *     @arg TWC_FLAG_RXDATLEV: rxd signal level flag
  *     @arg TWC_FLAG_RXFRMEEND: Normal receive data completion flag
  *     @arg TWC_FLAG_FRAMEEND: Entire frame data end flag
  * @retval The new state of TWC_FLAG (SET or RESET).
  */
FlagStatus TWC_GetFlagStatus(u32 TWC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_TWC_GET_FLAG(TWC_FLAG));

	/* Check the status of the TWC flag */
	if (TWC->STS & TWC_FLAG)
	{
		/* TWC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* TWC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the TWC_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified TWC interrupt has occurred or not.
  * @param  TWC_IT: specifies the TWC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg TWC_IT_RXFRMEEND: Normal receive data completion interrupt
  *     @arg TWC_IT_FRMEEND: Entire frame data end interrupt
  * @retval The new state of TWC_IT (SET or RESET).
  */
ITStatus TWC_GetITStatus(u8 TWC_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_TWC_GET_IT(TWC_IT));

	/* Check the status of the specified TWC interrupt */
	if ((TWC->INTEN & TWC_IT) && (TWC->STS & TWC_IT))
	{
		/* TWC_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* TWC_IT is reset */
		bitstatus = RESET;
	}
	/* Return the TWC_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for TWC.
  * @param  TWC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TWC_FLAG_STARBFLAG: Start bit valid flag
  *     @arg TWC_FLAG_RXBITERR: Receive data bit error flag
  *     @arg TWC_FLAG_RXFRMEERR: Receive data frame error flag
  *     @arg TWC_FLAG_AUTOCODEERR: Automatic unique encoding error flag
  *     @arg TWC_FLAG_RXFRMEEND: Normal receive data completion flag
  *     @arg TWC_FLAG_FRAMEEND: Entire frame data end flag
  * @retval None
  */
void TWC_ClearFlag(u32 TWC_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TWC_CLEAR_FLAG(TWC_FLAG));

	/* Clear the selected TWC flags */
	TWC->STS = TWC_FLAG;
}

/**
  * @brief  Send return data through the TWC peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void TWC_ReturnSendData(u32 Data)
{
	/* Write in the RETUN_TXD register the data to be sent */
	TWC->RETUN_TXD = Data;
}

/**
  * @brief  Send trans data through the TWC peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void TWC_TransSendData(u32 Data)
{
	/* Write in the TRANS_TXD register the data to be sent */
	TWC->TRANS_TXD = Data;
}

/**
  * @brief  Returns the most recent received data by the TWC peripheral.
  * @param  None
  * @retval The value of the received data.
  */
u32 TWC_ReceiveData(void)
{
	/* Return the data in the RXD register */
	return TWC->RXD;
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

