/*
 ============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello RISC-V World in C
 ============================================================================
 */

#include "lib_include.h"
#include <stdio.h>
#include <string.h>
#include "mcuboot.h"
#include "bl_cfg.h"

static uint8_t force_enter_bl = 0;
static uint8_t timeout_jump = 0;
static mcuboot_t mcuboot;

volatile UART_TypeDef *UARTx = UART1;

void TIM_ClkInit(void)
{
	// 设置TIM时钟分频，TIM1_CLK=1MHz, TIM2_CLK=1MHz
	SYSC->TIMCLKDIV = 0x00000707;

	// 配置TIM计数值
	TIM1->CTCG1 = 0x00000000;
	TIM1->CTCG2 = 0x00000000;
	TIM2->CTCG1 = 0x0000c34f;
	TIM2->CTCG2 = 0x00000000;

	// 配置TIMER2中断
	PLIC_SetPriority(TIMER2_IRQn, 1);
	PLIC_EnableIRQ(TIMER2_IRQn);
	TIMERS->INTCLR = TIM_INTCLR_TIM2;

	// 打开TIM1, TIM2
	TIMERS->CON = 0x00000223;
}

void Delay_Nus(u32 delay)
{
    u32 start = TIM1->CTVAL;
    while((start -(u32)TIM1->CTVAL) < delay) __asm("NOP");
}

void UART_HalInit(void)
{
	// 配置GP14, GP15复用为UART1
	IOM->ADS   = 0x00000000;
	IOM->AF0   = 0x10000200;
	IOM->AF1   = 0x00000000;
	IOM->OE    = 0x00000000;
	IOM->PU    = 0x00000000;
	IOM->PD    = 0x00000000;
	IOM->OTYPE = 0x00000000;
	IOM->DRS   = 0x00000000;

	// 配置UART: 115200
	UART1->SCON = 0x00000140;
	UART1->BDIV = 0x00000115;
	
	UART2->SCON = 0x00000140;
	UART2->BDIV = 0x00000115;
}

void FLASH_HalInit(void)
{
	// 初始化EFC
	EFC_WPT_UNLOCK();
	EFC->CR    = 0xf9c39000;
	EFC_WPT_UNLOCK();
	EFC->TNVS  = 0x0000000e;
	EFC_WPT_UNLOCK();
	EFC->TPROG = 0x0000000e;
	EFC_WPT_UNLOCK();
	EFC->TPGS  = 0x0000000c;
	EFC_WPT_UNLOCK();
	EFC->TRCV  = 0x000cf1e0;
	EFC_WPT_UNLOCK();
	EFC->TERS  = 0x000004c6;
}

static int memory_erase(uint32_t start_addr, uint32_t byte_cnt)
{
    uint32_t addr;
    addr = start_addr;

    while(addr < (byte_cnt + start_addr))
    {
        EFC_PageErase(addr);
		if(((addr) >= 0x10100000) && ((addr) < 0x10108000))
        	addr += 512;
		else if(((addr) >= 0x10140000) && ((addr) < 0x10140400))
			addr += 128;
		else
			addr += 8;
    }
    return 0;
}

static int memory_write(uint32_t start_addr, uint8_t *buf, uint32_t byte_cnt)
{
	for(uint32_t i=0; i<byte_cnt; i++)
	    EFC_SingleProgram(start_addr+i, buf[i], EFC_PRG_BYTE);
	
    return 0;
}

int memory_read(uint32_t addr, uint8_t *buf, uint32_t len)
{
    memcpy(buf, (void*)addr, len);
    return 0;
}

static int mcuboot_send(uint8_t *buf, uint32_t len)
{
	// 发送数据前打开TX复用
	if(UARTx == UART1)
	{
		if(IOM->AF0 == 0x10000200)					// GP14, GP15
		{
			IOM->AF0 = 0x50000000;
			IOM->AF1 = 0x00000000;
		}
		else if(IOM->AF0 == 0x00003000)				// GP18, GP19
		{
			IOM->AF0 = 0x00000000;
			IOM->AF1 = 0x000000F0;
		}
	}
	else
	{
		if(IOM->AF0 == 0x10000200)					// GP04, GP05
		{
			IOM->AF0 = 0x00000A00;
			IOM->AF1 = 0x00000000;
		}
		else if(IOM->AF0 == 0x00003000)				// GP06, GP07
		{
			IOM->AF0 = 0x0000F000;
			IOM->AF1 = 0x00000000;
		}
	}

    while(len--)
    {
    	UARTx->SBUF = *buf++;
		while(!(UARTx->ISR & UART_FLAG_TI));
		UARTx->ISR = UART_FLAG_TI;
    }
    return CH_OK;
}

static void mcuboot_reset(void)
{
    /* delay for a while to wait mcuboot send respond packet */
    Delay_Nus(200000);
	SYSC_WPT_UNLOCK();
    SYSC->MSFTRSTCFG = SYSC_MSFTRSTCFG_DIG;
}

static void mcuboot_complete(void) { }

bool is_app_addr_validate(uint32_t addr)
{
    if (addr < APPLICATION_BASE || addr > (APPLICATION_BASE + TARGET_FLASH_SIZE))
    {
        return false;
    }
    else
    {
        return true;
    } 
}

static void Jump_to_APP(uint32_t addr)
{
	void (*Jump_To_Application)(void);

	// 关闭全局中断
	DisableGlobleIRQ();
	
	IOM->AF0   = 0x00005500;
	IOM->AF1   = 0x00000000;
	
	TIMERS->INTCLR = TIM_INTCLR_TIM2;
	PLIC_DisableIRQ(TIMER2_IRQn);
	SYSC_WPT_UNLOCK();
	SYSC->MSFTRSTCFG = 0x3E;
	
	// 关闭模块时钟门控
	SYSC->CLKENCFG = 0x00004801;
 
	Jump_To_Application = (void (*)(void))addr;
	Jump_To_Application();
}

static void mcuboot_jump(uint32_t addr, uint32_t arg, uint32_t sp)
{
    if(is_app_addr_validate(addr) == true)
    {
        /* clean up resouces */
        Jump_to_APP(addr);
    }

	(void)arg;
	(void)sp;
}

int main(void)
{
	uint8_t c;

	TIM_ClkInit();
	UART_HalInit();
	FLASH_HalInit();

	/* config the mcuboot */
	mcuboot.op_send = mcuboot_send;
	mcuboot.op_reset = mcuboot_reset;
	mcuboot.op_jump = mcuboot_jump;
	mcuboot.op_complete = mcuboot_complete;

	mcuboot.op_mem_erase = memory_erase;
	mcuboot.op_mem_write = memory_write;
	mcuboot.op_mem_read = memory_read;

	mcuboot.cfg_flash_start = APPLICATION_BASE; 
	mcuboot.cfg_flash_size = TARGET_FLASH_SIZE;
	mcuboot.cfg_flash_sector_size = 512;
	mcuboot.cfg_ram_start = 0x20000000;
	mcuboot.cfg_ram_size = 4*1024;
	mcuboot.cfg_device_id = 0x12345678;
	mcuboot.cfg_uuid = 0x87654321;

	if(REG32(0x10140080) == 0x0FFAF005)
		mcuboot.flash_encrypt = 1;
	else
		mcuboot.flash_encrypt = 0;
	mcuboot.encrypt_erase = 0;

	mcuboot_init(&mcuboot);

//	u32 data = 0x0FFAF005;
//	data = 0xA5A5A5A5;
//	memory_erase(0x10140000, 0x80);
//	memory_write(0x1014007C, (uint8_t *)&data, 4);
	
//	printf("SYSC->CLKENCFG: %08x\n", SYSC->CLKENCFG);
//	printf("SYSC->TIMCLKDIV: %08x\n", SYSC->TIMCLKDIV);
//	printf("TIMERS->CON: %08x\n", TIMERS->CON);
//	printf("TIM1->CTCG1: %08x\n", TIM1->CTCG1);
//	printf("TIM1->CTCG2: %08x\n", TIM1->CTCG2);
//	printf("TIM2->CTCG1: %08x\n", TIM2->CTCG1);
//	printf("TIM2->CTCG2: %08x\n", TIM2->CTCG2);
//	
//	printf("IOM->ADS: %08x\n", IOM->ADS);
//	printf("IOM->AF0: %08x\n", IOM->AF0);
//	printf("IOM->AF1: %08x\n", IOM->AF1);
//	printf("IOM->OE: %08x\n", IOM->OE);
//	printf("IOM->PU: %08x\n", IOM->PU);
//	printf("IOM->PD: %08x\n", IOM->PD);
//	printf("IOM->OTYPE: %08x\n", IOM->OTYPE);
//	printf("IOM->DRS: %08x\n", IOM->DRS);
//	
//	printf("UART1->SCON: %08x\n", UART1->SCON);
//	printf("UART1->BDIV: %08x\n", UART1->BDIV);
//	
//	printf("EFC->CR: 0x%08x\n", EFC->CR);
//	printf("EFC->TNVS: 0x%08x\n", EFC->TNVS);
//	printf("EFC->TPROG: 0x%08x\n", EFC->TPROG);
//	printf("EFC->TPGS: 0x%08x\n", EFC->TPGS);
//	printf("EFC->TRCV: 0x%08x\n", EFC->TRCV);
//	printf("EFC->TERS: 0x%08x\n", EFC->TERS);

	printf("fdv32s302 boot loader start!!!\r\n");
	while (1)
	{
		if(UARTx->ISR & UART_FLAG_RI)
		{
			UARTx->ISR = UART_FLAG_RI;
			c = (u8)(UARTx->SBUF);
			mcuboot_recv(&mcuboot, &c, 1);
		}

		if(timeout_jump == 1)
		{
			mcuboot_jump(APPLICATION_BASE, 0, 0);
			timeout_jump = 0;
		}
		mcuboot_proc(&mcuboot);

		if(!mcuboot.is_connected)			// 未连接上切换串口试探
		{
			UARTx = (UARTx == UART1) ? UART2 : UART1;		// 切换串口试探
		}
	}

	return 0;
}

void TIMER2_IrqHandler(void)
{
    static int timeout = 0;

	TIMERS->INTCLR = TIM_INTCLR_TIM2;
	
    if(timeout > BL_TIMEOUT_MS/100)
    {
        if(force_enter_bl == 0 && mcuboot_is_connected(&mcuboot) == 0)
        {
            timeout_jump = 1;
        }
		TIMERS->CON &= ~TIM_CON_IE_TIM2;
    }
    timeout++;
	if(timeout == 2 && !mcuboot.is_connected)			// 200ms后切换复用端口检测
	{
		IOM->AF0 = 0x00003000;
		IOM->AF1 = 0x00000030;
	}
}

