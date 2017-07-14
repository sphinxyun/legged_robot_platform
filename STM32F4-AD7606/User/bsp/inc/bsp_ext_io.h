/*
*********************************************************************************************************
*
*	ģ������ : STM32-V6��������չIO��������
*	�ļ����� : bsp_ext_io.g
*	˵    �� : V6��������FMC��������չ��32λ���IO����ַΪ (0x6820 0000)
*
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#ifndef __BSP_EXT_IO_H
#define __BSP_EXT_IO_H

#include "stm32f4xx_conf.h"

/* ���ⲿ���õĺ������� */
/*
	������P03����չ���߷���: ���ߵ�ַ = 0x6820 0000
	D0  - GPRS_RERM_ON
	D1  - GPRS_RESET
	D2  - NRF24L01_CE
	D3  - NRF905_TX_EN
	D4  - NRF905_TRX_CE/VS1053_XDCS
	D5  - NRF905_PWR_UP
	D6  - ESP8266_G0
	D7  - ESP8266_G2
	
	D8  - LED1
	D9  - LED2
	D10 - LED3
	D11 - LED4
	D12 - TP_NRST
	D13 - AD7606_OS0
	D14 - AD7606_OS1
	D15 - AD7606_OS2
	
	Ԥ����8��5V���IO: Y50_0 - Y50_1
	D16  - Y50_0
	D17  - Y50_1
	D18  - Y50_2
	D19  - Y50_3
	D20  - Y50_4
	D21  - Y50_5
	D22  - Y50_6
	D23  - Y50_7	

	Ԥ����8��3.3V���IO: Y33_0 - Y33_1
	D24  - AD7606_RESET
	D25  - AD7606_RAGE
	D26  - Y33_2
	D27  - Y33_3
	D28  - Y33_4
	D29  - Y33_5
	D30  - Y33_6
	D31  - Y33_7				
*/

/* Ϊ�˷�����䣬����������ĺ� */
#define	GPRS_TERM_ON   GPIO_Pin_0
#define	GPRS_RESET     GPIO_Pin_1
#define	NRF24L01_CE    GPIO_Pin_2
#define	NRF905_TX_EN   GPIO_Pin_3
#define	NRF905_TRX_CE  GPIO_Pin_4
#define	NRF905_PWR_UP  GPIO_Pin_5
#define	ESP8266_G0     GPIO_Pin_6
#define	ESP8266_G2     GPIO_Pin_7
	
#define	LED1           GPIO_Pin_8
#define	LED2           GPIO_Pin_9
#define	LED3           GPIO_Pin_10
#define	LED4           GPIO_Pin_11
#define	TP_NRST        GPIO_Pin_12
#define	AD7606_OS0     GPIO_Pin_13
#define	AD7606_OS1     GPIO_Pin_14
#define	AD7606_OS2     GPIO_Pin_15
	
#define	Y50_0          GPIO_Pin_16
#define	Y50_1          GPIO_Pin_17
#define	Y50_2          GPIO_Pin_18
#define	Y50_3          GPIO_Pin_19
#define	Y50_4          GPIO_Pin_20
#define	Y50_5          GPIO_Pin_21
#define	Y50_6          GPIO_Pin_22
#define	Y50_7          GPIO_Pin_23	

#define	AD7606_RESET   (1u << 24)
#define	AD7606_RANGE   (1u << 25)
#define	Y33_2          GPIO_Pin_26
#define	Y33_3          GPIO_Pin_27
#define	Y33_4          GPIO_Pin_28
#define	Y33_5          GPIO_Pin_29
#define	Y33_6          GPIO_Pin_30
#define	Y33_7          GPIO_Pin_31

#define  HC574_PORT	 *(uint32_t *)0x64000000


void bsp_InitExtIO(void);
void HC574_SetPin(uint32_t _pin, uint8_t _value);
uint8_t HC574_GetPin(uint32_t _pin);

void bsp_SetY(uint8_t _id, uint8_t _state);
uint8_t bsp_GetY(uint8_t _id);

extern __IO uint32_t g_HC574;

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
