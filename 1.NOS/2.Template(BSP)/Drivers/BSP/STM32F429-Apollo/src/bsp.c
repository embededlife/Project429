/**
  ******************************************************************************
  * @file    bsp.c
  * @author  Wendell
  * @date    2019-2-28 
  * @brief   Board Support Package
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "bsp.h"

 /**
  * @brief STM32F429 APOLLO BSP Driver version number V1.0.0
  */
#define __STM32F429_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32F429_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32F429_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32F429_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F429_BSP_VERSION        ((__STM32F429_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F429_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F429_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F429_BSP_VERSION_RC)) 
											 
/**
  * @brief  This method returns the STM32F429 APOLLO BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F429_BSP_VERSION;
}

void BSP_PrintfLogo(void)
{
	uint32_t HAL_Version;
	HAL_Version = HAL_GetHalVersion();
	printf("* HAL版本 : V%d.%d.%d (STM32F4xx HAL driver version )\r\n", (HAL_Version>>24)&0xff,
			(HAL_Version>>16)&0xff,(HAL_Version>>8)&0xff);
	printf("* BSP版本 : V%d.%d.%d (STM32F429-Apollo BSP version )\r\n", __STM32F429_BSP_VERSION_MAIN,
			__STM32F429_BSP_VERSION_SUB1,__STM32F429_BSP_VERSION_SUB2);	
	
}


/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化硬件设备。只需要调用一次。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。
*			
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Init(void)
{
	/*
		由于ST固件库的启动文件已经执行了CPU系统时钟的初始化，所以不必再次重复配置系统时钟。
		启动文件配置了CPU主时钟频率、内部Flash访问速度和可选的外部SRAM FSMC初始化。

		系统时钟缺省配置为180MHz，如果需要更改，可以修改 system_stm32f4xx.c 文件
	*/
	/* STM32F4xx HAL library initialization:
	   - Configure the Flash prefetch, Flash preread and Buffer caches
	   - Systick timer is configured by default as source of time base, but user 
			 can eventually implement his proper time base source (a general purpose 
			 timer for example or other time source), keeping in mind that Time base 
			 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
			 handled in milliseconds basis.
	   - Low Level Initialization
	 */
	HAL_Init();
	/* Configure the System clock to 180 MHz */
	SystemClock_Config();
	
	HAL_Delay(10);				/*初始化延时，等待时钟稳定*/
//	SystemCoreClockUpdate();	/* 根据PLL配置更新系统时钟频率变量 SystemCoreClock */
	/* 优先级分组设置为4 */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	BSP_LED_Init();		/* 配置LED */
//	BSP_GPIO_Init();	/* 配置输入输出端口 */
	BSP_UART_Init();	/* 初始化串口 */
//	bsp_InitKey();		/* 初始化按键 */
//	bsp_InitTimer();	/* 初始化系统滴答定时器 (此函数会开 systick 中断, tim2-5中断) */
	printf("Hardware Abstraction Layer init completed!\r\n");
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer10ms
*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_RunPer10ms(void)
{
//	bsp_KeyScan();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1ms
*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
*			 可以放在此函数。比如：触摸坐标扫描。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_RunPer1ms(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void BSP_Idle(void)
{
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/


