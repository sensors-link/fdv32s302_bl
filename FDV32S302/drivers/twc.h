/**
  ******************************************************************************
  * @file    twc.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-26
  * @brief   This file contains all functional prototypes of the TWC firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TWC_H__
#define __TWC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup TWC
  * @{
  */

/** @defgroup TWC_module_register_bit_definition
  * @{
  */

/* TWC_CR */
#define TWC_CR_AUTOCODEEN	   BIT(10)
#define TWC_CR_RX_INV_CFG	   BIT(9)
#define TWC_CR_RXRECEN		   BIT(8)
#define TWC_CR_SEBUSMODE	   BIT(7)
#define TWC_CR_SEBUSEN		   BIT(6)
#define TWC_CR_TXLELCFG		   BIT(5)
#define TWC_CR_RXDECCFG		   BIT(4)
#define TWC_CR_RXGLITCHFILTCFG BITS(0, 3) /* [0-0x0f] = 0-30cycle */

#define TWC_CR_RXGLITCHFILTCFG_pos (0)

/* TWC_STARBLOW */
#define TWC_STARBLOW_THR_STARB_LOW_MAX BITS(9, 17)
#define TWC_STARBLOW_THR_STARB_LOW_MIN BITS(0, 8)

#define TWC_STARBLOW_THR_STARB_LOW_MAX_pos (9)
#define TWC_STARBLOW_THR_STARB_LOW_MIN_pos (0)

/* TWC_STARBHIG */
#define TWC_STARBHIG_THR_STARB_HIG_MAX BITS(11, 21)
#define TWC_STARBHIG_THR_STARB_HIG_MIN BITS(0, 10)

#define TWC_STARBHIG_THR_STARB_HIG_MAX_pos (11)
#define TWC_STARBHIG_THR_STARB_HIG_MIN_pos (0)

/* TWC_DATABLOW */
#define TWC_DATABLOW_THR_DATAB_LOW_MAX BITS(9, 17)
#define TWC_DATABLOW_THR_DATAB_LOW_MIN BITS(0, 8)

#define TWC_DATABLOW_THR_DATAB_LOW_MAX_pos (9)
#define TWC_DATABLOW_THR_DATAB_LOW_MIN_pos (0)

/* TWC_DAT0BHIG */
#define TWC_DAT0BHIG_THR_DAT0B_HIG_MAX BITS(11, 21)
#define TWC_DAT0BHIG_THR_DAT0B_HIG_MIN BITS(0, 10)

#define TWC_DAT0BHIG_THR_DAT0B_HIG_MAX_pos (11)
#define TWC_DAT0BHIG_THR_DAT0B_HIG_MIN_pos (0)

/* TWC_DAT1BHIG */
#define TWC_DAT1BHIG_THR_DAT1B_HIG_MAX BITS(11, 21)
#define TWC_DAT1BHIG_THR_DAT1B_HIG_MIN BITS(0, 10)

#define TWC_DAT1BHIG_THR_DAT1B_HIG_MAX_pos (11)
#define TWC_DAT1BHIG_THR_DAT1B_HIG_MIN_pos (0)

/* TWC_SPACEHIG */
#define TWC_SPACEHIG_THR_SPACE_HIG BITS(0, 10)

#define TWC_SPACEHIG_THR_SPACE_HIG_pos (0)

/* TWC_TXMASK */
#define TWC_TXMASK_THR_TX_GAP_STP BITS(11, 21)
#define TWC_TXMASK_THR_TX_GAP_STA BITS(0, 10)

#define TWC_TXMASK_THR_TX_GAP_STP_pos (11)
#define TWC_TXMASK_THR_TX_GAP_STA_pos (0)

/* TWC_RXMASK */
#define TWC_RXMASK_THR_RX_GAP BITS(0, 10)

#define TWC_RXMASK_THR_RX_GAP_pos (0)

/* TWC_CMD */
#define TWC_CMD_CMD BITS(16, 31)
#define TWC_CMD_MSK BITS(0, 15)

#define TWC_CMD_CMD_pos (16)
#define TWC_CMD_MSK_pos (0)

/* TWC_SWCR */
#define TWC_SWCR_THR_RX_GAP_MAX BITS(5, 13)
#define TWC_SWCR_RXPARITYCFG    BIT(4)
#define TWC_SWCR_TXCODECFG	    BIT(3)
#define TWC_SWCR_TXPARITYCFG    BIT(2)
#define TWC_SWCR_TXBITCFG	    BITS(0, 1)

#define TWC_SWCR_TXBITCFG_8BIT	(0 << 0)
#define TWC_SWCR_TXBITCFG_16BIT (1 << 0)
#define TWC_SWCR_TXBITCFG_24BIT (2 << 0)
#define TWC_SWCR_TXBITCFG_32BIT (3 << 0)

#define TWC_SWCR_THR_RX_GAP_MAX_pos	(5)
#define TWC_SWCR_TXBITCFG_pos	    (0)

/* TWC_SWBR */
#define TWC_SWBR_TXBR BITS(4, 7)
#define TWC_SWBR_RXBR BITS(0, 3)

#define TWC_SWBR_TXBR_1K  (0 << 4)
#define TWC_SWBR_TXBR_2K  (1 << 4)
#define TWC_SWBR_TXBR_3K  (2 << 4)
#define TWC_SWBR_TXBR_4K  (3 << 4)
#define TWC_SWBR_TXBR_5K  (4 << 4)
#define TWC_SWBR_TXBR_6K  (5 << 4)
#define TWC_SWBR_TXBR_8K  (6 << 4)
#define TWC_SWBR_TXBR_10K (7 << 4)
#define TWC_SWBR_TXBR_12K (8 << 4)
#define TWC_SWBR_TXBR_15K (9 << 4)
#define TWC_SWBR_TXBR_20K (10 << 4)
#define TWC_SWBR_TXBR_25K (11 << 4)
#define TWC_SWBR_TXBR_30K (12 << 4)
#define TWC_SWBR_TXBR_40K (13 << 4)
#define TWC_SWBR_TXBR_50K (14 << 4)
#define TWC_SWBR_TXBR_60K (15 << 4)

#define TWC_SWBR_RXBR_1K  (0 << 0)
#define TWC_SWBR_RXBR_2K  (1 << 0)
#define TWC_SWBR_RXBR_3K  (2 << 0)
#define TWC_SWBR_RXBR_4K  (3 << 0)
#define TWC_SWBR_RXBR_5K  (4 << 0)
#define TWC_SWBR_RXBR_6K  (5 << 0)
#define TWC_SWBR_RXBR_8K  (6 << 0)
#define TWC_SWBR_RXBR_10K (7 << 0)
#define TWC_SWBR_RXBR_12K (8 << 0)
#define TWC_SWBR_RXBR_15K (9 << 0)
#define TWC_SWBR_RXBR_20K (10 << 0)
#define TWC_SWBR_RXBR_25K (11 << 0)
#define TWC_SWBR_RXBR_30K (12 << 0)
#define TWC_SWBR_RXBR_40K (13 << 0)
#define TWC_SWBR_RXBR_50K (14 << 0)
#define TWC_SWBR_RXBR_60K (15 << 0)

#define TWC_SWBR_TXBR_pos (4)
#define TWC_SWBR_RXBR_pos (0)

/* TWC_TXS */
#define TWC_TXS_TRANSTXEN   BIT(3)
#define TWC_TXS_TXMODE      BIT(2)
#define TWC_TXS_SOFTTXSTART BIT(1)
#define TWC_TXS_RETURNTXEN  BIT(0)

/* TWC_INTEN */
#define TWC_INTEN_RXFRAMENDINTEN BIT(1)
#define TWC_INTEN_FRMEENDINTEN BIT(0)

/* TWC_STS */
#define TWC_STS_STARBFLAG   BIT(20)
#define TWC_STS_HANMCHKPAR  BITS(14, 19)
#define TWC_STS_RXPARITY    BITS(8, 13)
#define TWC_STS_RXPARERR    BIT(7)
#define TWC_STS_RXBITERR    BIT(6)
#define TWC_STS_RXFRMEERR   BIT(5)
#define TWC_STS_RXMUTEFRME  BIT(4)
#define TWC_STS_AUTOCODEERR BIT(3)
#define TWC_STS_RXDATLEV    BIT(2)
#define TWC_STS_RXFRMEEND   BIT(1)
#define TWC_STS_FRAMEEND    BIT(0)

#define TWC_STS_HANMCHKPAR_pos (14)
#define TWC_STS_RXPARITY_pos   (8)

/* TWC_DBG */
#define TWC_DBG_HILEVCNT BITS(16, 26)
#define TWC_DBG_RXSTATE	 BITS(13, 15)
#define TWC_DBG_TXSTATE	 BITS(11, 12)
#define TWC_DBG_LOLEVCNT BITS(0, 8)

#define TWC_DBG_HILEVCNT_pos  (16)
#define TWC_DBG_RXSTATE_pos   (13)
#define TWC_DBG_TXSTATE_pos	  (11)
#define TWC_DBG_LOLEVCNT_pos  (0)

/**
  * @}
  */

/** @defgroup TWC_Exported_Types
  * @{
  */

/**
  * @brief TWC SE_BUS Init structure definition
  */

typedef struct
{
	u8 TWC_SEBUSMode; 						/*!< Specifies that SEBUS returns code at this level.
											 	 This parameter can be a value of @ref TWC_SEBUS_mode. */

	u8 TWC_TxDefaultLevel; 					/*!< Specify TX port default level configuration.
											 	 This parameter can be a value of @ref TWC_TX_default_level. */

	u8 TWC_RXDecode; 						/*!< Specify the hardware decoding configuration of the received data.
											 	 This parameter can be a value of @ref TWC_RX_decode_config. */

	u8 TWC_GlitchFilt; 						/*!< Specifies the number of digital filtering cycles for received data.
                                  				 This parameter can be a number between 0x0 and 0xF. */

	u16 TWC_StartBLowMin; 					/*!< Specifies the lower limit of the starting low level threshold.
                                  				 This parameter can be a number between 0x00 and 0x1FF. */

	u16 TWC_StartBLowMax; 					/*!< Specifies the upper limit of the start bit low level threshold.
                                  				 This parameter can be a number between 0x00 and 0x1FF. */

	u16 TWC_StartBHighMin; 					/*!< Specifies the lower limit of the starting high level threshold.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_StartBHighMax; 					/*!< Specifies the upper limit of the starting high level threshold.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_DataBLowMin; 					/*!< Specifies the lower limit of the data bit low level threshold.
                                  				 This parameter can be a number between 0x00 and 0x1FF. */

	u16 TWC_DataBLowMax; 					/*!< Specifies the upper limit of the data bit low level threshold.
                                  				 This parameter can be a number between 0x00 and 0x1FF. */

	u16 TWC_Data0BHighMin; 					/*!< Specifies the lower limit of the data 0 high level threshold.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_Data0BHighMax; 					/*!< Specifies the upper limit of the data 0 high level threshold.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_Data1BHighMin; 					/*!< Specifies the lower limit of the data 1 high level threshold.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_Data1BHighMax; 					/*!< Specifies the upper limit of the data 1 high level threshold.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_TxStartGap; 					/*!< Specifies the start interval for sending data.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */

	u16 TWC_TxStopGap; 						/*!< Specifies the end interval for sending data.
                                  				 This parameter can be a number between 0x00 and 0x7FF. */
} TWC_SEBUSInitTypeDef;

/**
  * @brief TWC SWAN_BUS Init structure definition
  */

typedef struct
{
	u8 TWC_TxDefaultLevel; 					/*!< Specify TX port default level configuration.
											 	 This parameter can be a value of @ref TWC_TX_default_level. */

	u8 TWC_RXDecode; 						/*!< Specify the hardware decoding configuration of the received data.
											 	 This parameter can be a value of @ref TWC_RX_decode_config. */

	u8 TWC_GlitchFilt; 						/*!< Specifies digital filtering of received data.
                                  				 This parameter can be a number between 0x0 and 0xF. */

	u8 TWC_RxCheck; 						/*!< Specify the verification method of the received data.
											 	 This parameter can be a value of @ref TWC_RX_check. */

	u8 TWC_TxCode; 							/*!< Specify the encoding method of sending data.
											 	 This parameter can be a value of @ref TWC_TX_code. */

	u8 TWC_TxParity; 						/*!< Specifies parity of sent data.
											 	 This parameter can be a value of @ref TWC_TX_parity. */

	u8 TWC_TxBit; 							/*!< Specifies the 32-bit data valid bit in the TWC_TXD register.
											 	 This parameter can be a value of @ref TWC_TX_valid_bit. */

	u8 TWC_TxBaudRate; 						/*!< Specify the baud rate for sending data.
											 	 This parameter can be a value of @ref TWC_TX_baud_rate. */

	u8 TWC_RxBaudRate; 						/*!< Specify the baud rate of the received data.
											 	 This parameter can be a value of @ref TWC_RX_baud_rate. */

	u8 TWC_SWANBUSStartGap; 				/*!< Specifies the boundary between the RX and TX start bits in SWAN_BUS mode.
												  - Gap <= TWC_SWANBUSStartGap, RX start bit
												  - Gap > TWC_SWANBUSStartGap, TX start bit
                                  				 This parameter can be a number between 0x00 and 0xFF. */
} TWC_SWANBUSInitTypeDef;

/**
  * @}
  */

/** @defgroup TWC_Exported_Constants
  * @{
  */

/** @defgroup TWC_SEBUS_mode
  * @{
  */

#define TWC_SEBUS_MODE_IN_HIGH (0)
#define TWC_SEBUS_MODE_IN_LOW	(1)

#define IS_TWC_SEBUS_MODE(MODE) (((MODE) == TWC_SEBUS_MODE_IN_HIGH) || ((MODE) == TWC_SEBUS_MODE_IN_LOW))
/**
  * @}
  */

/** @defgroup TWC_TX_default_level
  * @{
  */
	
#define TWC_TX_DEFAULT_LEVEL_HIGH (0)
#define TWC_TX_DEFAULT_LEVEL_LOW  (1)

#define IS_TWC_TX_DEFAULT_LEVEL(LEVEL) (((LEVEL) == TWC_TX_DEFAULT_LEVEL_HIGH) || ((LEVEL) == TWC_TX_DEFAULT_LEVEL_LOW))
/**
  * @}
  */

/** @defgroup TWC_RX_decode_config
  * @{
  */

#define TWC_RX_DEC_MATCH_CMD	(0)
#define TWC_RX_DEC_NOTMATCH_CMD (1)

#define IS_TWC_RX_DECODE(DECODE) (((DECODE) == TWC_RX_DEC_MATCH_CMD) || ((DECODE) == TWC_RX_DEC_NOTMATCH_CMD))
/**
  * @}
  */

/** @defgroup TWC_glitch_filter
  * @{
  */

#define IS_TWC_GLITCH_FILT(FILT) ((FILT) <= 0xF)
/**
  * @}
  */

/** @defgroup TWC_SEBUS_level_threshold
  * @{
  */
	
#define IS_TWC_SEBUS_LOW_THR(THR) ((THR) <= 0x1FF)
#define IS_TWC_SEBUS_HIGH_THR(THR) ((THR) <= 0x7FF)
/**
  * @}
  */

/** @defgroup TWC_RX_check
  * @{
  */

#define TWC_RX_CHECK_PARITY	 (0)
#define TWC_RX_CHECK_HAMMING (1)

#define IS_TWC_RX_CHECK(CHECK) (((CHECK) == TWC_RX_CHECK_PARITY) || ((CHECK) == TWC_RX_CHECK_HAMMING))
/**
  * @}
  */

/** @defgroup TWC_TX_code
  * @{
  */

#define TWC_TX_CODE_NRZ (0)
#define TWC_TX_CODE_MCT (1)

#define IS_TWC_TX_CODE(CODE) (((CODE) == TWC_TX_CODE_NRZ) || ((CODE) == TWC_TX_CODE_MCT))
/**
  * @}
  */

/** @defgroup TWC_TX_parity
  * @{
  */

#define TWC_TX_PARITY_EVEN (0)
#define TWC_TX_PARITY_ODD  (1)

#define IS_TWC_TX_PARITY(PARITY) (((PARITY) == TWC_TX_PARITY_EVEN) || ((PARITY) == TWC_TX_PARITY_ODD))
/**
  * @}
  */

/** @defgroup TWC_TX_valid_bit
  * @{
  */

#define TWC_TX_BIT_8BIT	 (0)
#define TWC_TX_BIT_16BIT (1)
#define TWC_TX_BIT_24BIT (2)
#define TWC_TX_BIT_32BIT (3)

#define IS_TWC_TX_BIT(BIT)                                                                                             \
	(((BIT) == TWC_TX_BIT_8BIT) || ((BIT) == TWC_TX_BIT_16BIT) || ((BIT) == TWC_TX_BIT_24BIT) ||                       \
	 ((BIT) == TWC_TX_BIT_32BIT))
/**
  * @}
  */

/** @defgroup TWC_TX_baud_rate
  * @{
  */

#define TWC_TX_BAUDRATE_1K	(0)
#define TWC_TX_BAUDRATE_2K	(1)
#define TWC_TX_BAUDRATE_3K	(2)
#define TWC_TX_BAUDRATE_4K	(3)
#define TWC_TX_BAUDRATE_5K	(4)
#define TWC_TX_BAUDRATE_6K	(5)
#define TWC_TX_BAUDRATE_8K	(6)
#define TWC_TX_BAUDRATE_10K (7)
#define TWC_TX_BAUDRATE_12K (8)
#define TWC_TX_BAUDRATE_15K (9)
#define TWC_TX_BAUDRATE_20K (10)
#define TWC_TX_BAUDRATE_25K (11)
#define TWC_TX_BAUDRATE_30K (12)
#define TWC_TX_BAUDRATE_40K (13)
#define TWC_TX_BAUDRATE_50K (14)
#define TWC_TX_BAUDRATE_60K (15)

#define IS_TWC_TX_BAUDRATE(BAUDRATE)                                                                                   \
	(((BAUDRATE) == TWC_TX_BAUDRATE_1K) || ((BAUDRATE) == TWC_TX_BAUDRATE_2K) || ((BAUDRATE) == TWC_TX_BAUDRATE_3K) || \
	 ((BAUDRATE) == TWC_TX_BAUDRATE_4K) || ((BAUDRATE) == TWC_TX_BAUDRATE_5K) || ((BAUDRATE) == TWC_TX_BAUDRATE_6K) || \
	 ((BAUDRATE) == TWC_TX_BAUDRATE_8K) || ((BAUDRATE) == TWC_TX_BAUDRATE_10K) ||                                      \
	 ((BAUDRATE) == TWC_TX_BAUDRATE_12K) || ((BAUDRATE) == TWC_TX_BAUDRATE_15K) ||                                     \
	 ((BAUDRATE) == TWC_TX_BAUDRATE_20K) || ((BAUDRATE) == TWC_TX_BAUDRATE_25K) ||                                     \
	 ((BAUDRATE) == TWC_TX_BAUDRATE_30K) || ((BAUDRATE) == TWC_TX_BAUDRATE_40K) ||                                     \
	 ((BAUDRATE) == TWC_TX_BAUDRATE_50K) || ((BAUDRATE) == TWC_TX_BAUDRATE_60K))
/**
  * @}
  */

/** @defgroup TWC_RX_baud_rate
  * @{
  */

#define TWC_RX_BAUDRATE_1K	(0)
#define TWC_RX_BAUDRATE_2K	(1)
#define TWC_RX_BAUDRATE_3K	(2)
#define TWC_RX_BAUDRATE_4K	(3)
#define TWC_RX_BAUDRATE_5K	(4)
#define TWC_RX_BAUDRATE_6K	(5)
#define TWC_RX_BAUDRATE_8K	(6)
#define TWC_RX_BAUDRATE_10K (7)
#define TWC_RX_BAUDRATE_12K (8)
#define TWC_RX_BAUDRATE_15K (9)
#define TWC_RX_BAUDRATE_20K (10)
#define TWC_RX_BAUDRATE_25K (11)
#define TWC_RX_BAUDRATE_30K (12)
#define TWC_RX_BAUDRATE_40K (13)
#define TWC_RX_BAUDRATE_50K (14)
#define TWC_RX_BAUDRATE_60K (15)

#define IS_TWC_RX_BAUDRATE(BAUDRATE)                                                                                   \
	(((BAUDRATE) == TWC_RX_BAUDRATE_1K) || ((BAUDRATE) == TWC_RX_BAUDRATE_2K) || ((BAUDRATE) == TWC_RX_BAUDRATE_3K) || \
	 ((BAUDRATE) == TWC_RX_BAUDRATE_4K) || ((BAUDRATE) == TWC_RX_BAUDRATE_5K) || ((BAUDRATE) == TWC_RX_BAUDRATE_6K) || \
	 ((BAUDRATE) == TWC_RX_BAUDRATE_8K) || ((BAUDRATE) == TWC_RX_BAUDRATE_10K) ||                                      \
	 ((BAUDRATE) == TWC_RX_BAUDRATE_12K) || ((BAUDRATE) == TWC_RX_BAUDRATE_15K) ||                                     \
	 ((BAUDRATE) == TWC_RX_BAUDRATE_20K) || ((BAUDRATE) == TWC_RX_BAUDRATE_25K) ||                                     \
	 ((BAUDRATE) == TWC_RX_BAUDRATE_30K) || ((BAUDRATE) == TWC_RX_BAUDRATE_40K) ||                                     \
	 ((BAUDRATE) == TWC_RX_BAUDRATE_50K) || ((BAUDRATE) == TWC_RX_BAUDRATE_60K))
/**
  * @}
  */

/** @defgroup TWC_CMD_register
  * @{
  */
  
#define IS_TWC_CMD(CMD) (((CMD) >= 0x01) && ((CMD) <= 0x0C))
/**
  * @}
  */

/** @defgroup TWC_send_mode
  * @{
  */

#define TWC_SEND_MODE_SOFT (0)
#define TWC_SEND_MODE_AUTO (1)

#define IS_TWC_SEND_MODE(MODE) (((MODE) == TWC_SEND_MODE_SOFT) || ((MODE) == TWC_SEND_MODE_AUTO))
/**
  * @}
  */

/** @defgroup TWC_interrupts_definition
  * @{
  */

#define TWC_IT_RXFRMEEND BIT(1)
#define TWC_IT_FRMEEND BIT(0)

#define TWC_IT_ALL (TWC_IT_RXFRMEEND | TWC_IT_FRMEEND)

#define IS_TWC_CONFIG_IT(IT) (((IT)&TWC_IT_ALL) && (!((IT) & (~(TWC_IT_ALL)))))

#define IS_TWC_GET_IT(IT) (((IT) == TWC_IT_RXFRMEEND) || ((IT) == TWC_IT_FRMEEND))
/**
  * @}
  */

/** @defgroup TWC_flags_definition
  * @{
  */

#define TWC_FLAG_STARBFLAG   BIT(20)
#define TWC_FLAG_RXPARERR	 BIT(7)
#define TWC_FLAG_RXBITERR	 BIT(6)
#define TWC_FLAG_RXFRMEERR	 BIT(5)
#define TWC_FLAG_RXMUTEFRME  BIT(4)
#define TWC_FLAG_AUTOCODEERR BIT(3)
#define TWC_FLAG_RXDATLEV	 BIT(2)
#define TWC_FLAG_RXFRMEEND	 BIT(1)
#define TWC_FLAG_FRAMEEND	 BIT(0)

#define TWC_FLAG_ALL (TWC_FLAG_STARBFLAG | TWC_FLAG_RXBITERR | TWC_FLAG_RXFRMEERR | TWC_FLAG_AUTOCODEERR | 			   \
					  TWC_FLAG_RXFRMEEND | TWC_FLAG_FRAMEEND)

#define IS_TWC_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == TWC_FLAG_STARBFLAG) || ((FLAG) == TWC_FLAG_RXPARERR) || ((FLAG) == TWC_FLAG_RXBITERR) ||              \
	 ((FLAG) == TWC_FLAG_RXFRMEERR) || ((FLAG) == TWC_FLAG_RXMUTEFRME) || ((FLAG) == TWC_FLAG_AUTOCODEERR) ||         \
	 ((FLAG) == TWC_FLAG_RXDATLEV) || ((FLAG) == TWC_FLAG_RXFRMEEND) || ((FLAG) == TWC_FLAG_FRAMEEND))

#define IS_TWC_CLEAR_FLAG(FLAG) (((FLAG) & TWC_FLAG_ALL) && (!((FLAG) & (~(TWC_FLAG_ALL)))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup TWC_Exported_Functions
  * @{
  */

void	   TWC_DeInit(void);
void	   TWC_SEBUSInit(TWC_SEBUSInitTypeDef *TWC_SEBUSInitStruct);
void	   TWC_SWANBUSInit(TWC_SWANBUSInitTypeDef *TWC_SWANBUSInitStruct);
void	   TWC_SpaceHighHoldConfig(u16 HoldVal);
void	   TWC_RxHoldConfig(u16 HoldVal);
void	   TWC_SetCMDAndMask(u8 CMDx, u16 Cmd, u16 Mask);
void	   TWC_SetSendMode(u8 SendMode);
u8		   TWC_GetHanmCheckValue(void);
u8		   TWC_GetCheckValue(void);
void	   TWC_AutoCodeCmd(FunctionalState NewState);
void	   TWC_RecieveInvertCmd(FunctionalState NewState);
void	   TWC_RecieveCmd(FunctionalState NewState);
void	   TWC_ReturnSendCmd(FunctionalState NewState);
void	   TWC_TransSendCmd(FunctionalState NewState);
void	   TWC_SendCmd(FunctionalState NewState);
void	   TWC_SoftTxStartEnable(void);
void	   TWC_ITConfig(u8 TWC_IT, FunctionalState NewState);
FlagStatus TWC_GetFlagStatus(u32 TWC_FLAG);
ITStatus   TWC_GetITStatus(u8 TWC_IT);
void	   TWC_ClearFlag(u32 TWC_FLAG);
void	   TWC_ReturnSendData(u32 Data);
void	   TWC_TransSendData(u32 Data);
u32		   TWC_ReceiveData(void);

#ifdef __cplusplus
}
#endif

#endif /* __TWC_H__ */

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

