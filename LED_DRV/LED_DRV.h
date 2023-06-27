/*
 * LED_DRIVER.h
 *
 *  Created on: 14.03.2023
 *      Author: markfe1
 */

#ifndef LED_DRV_H_
#define LED_DRV_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"


/* Private defines------------------------------------------------------------*/

/*LED Driver Status def*/
typedef enum {
	LED_DRV_OK = 0,
	LED_DRV_NOK,
} LED_DRV_status_t;

/*LED Driver ENABLE Status def*/
typedef enum {
	DISABLED = 0,
	ENABLED,
} EN_status_t;

/*SPI standard read commands, it contains the odd parity bit too*/
#define 	READ_EN					0x0000	//0b0 000000 0 00000000
#define		READ_CFG1				0x0200	//0b0 000001 0 00000000
#define		READ_CFG2				0x0400	//0b0 000010 0 00000000
#define 	READ_FLT1				0x2200	//0b0 010001 0 00000000
#define 	READ_FLT2				0x2400	//0b0 010010 0 00000000
#define 	READ_CH1IADJ			0x0E00	//0b0 000111 0 00000000
#define 	READ_CH2IADJ			0x1000	//0b0 001000 0 00000000
#define		READ_PWMDIV				0x1200	//0b0 001001 0 00000000
#define 	READ_CH1PWML			0x1400	//0b0 001010 0 00000000
#define 	READ_CH1PWMH			0x1600	//0b0 001011 0 00000000
#define 	READ_CH2PWML			0x1800	//0b0 001100 0 00000000
#define 	READ_CH2PWMH			0x1A00	//0b0 001101 0 00000000
#define 	READ_FM					0x0A00	//0b0 000101 0 00000000
#define 	READ_FEN1				0x2600	//0b0 010011 0 00000000
#define 	READ_FEN2				0x2800	//0b0 010100 0 00000000
#define 	READ_SOFTSTART			0x0C00	//0b0 000110 0 00000000
#define		READ_FLATEN				0x2A00	//0b0 010101 0 00000000

/*SPI standard write commands, without odd parity bit, it will be added later*/
#define		WRITE_EN				0x8000	//0b1 000000 0 00000000
#define		WRITE_CFG1				0x8200	//0b1 000001 0 00000000
#define		WRITE_CFG2				0x8400	//0b1 000010 0 00000000
#define 	WRITE_CH1IADJ			0x8E00	//0b1 000111 0 00000000
#define 	WRITE_CH2IADJ			0x9000	//0b1 001000 0 00000000
#define		WRITE_PWMDIV			0x9200	//0b1 001001 0 00000000
#define 	WRITE_CH1PWML			0x9400	//0b1 001010 0 00000000
#define 	WRITE_CH1PWMH			0x9600	//0b1 001011 0 00000000
#define 	WRITE_CH2PWML			0x9800	//0b1 001100 0 00000000
#define 	WRITE_CH2PWMH			0x9A00	//0b1 001101 0 00000000
#define 	WRITE_FM				0x8A00	//0b1 000101 0 00000000
#define 	WRITE_FEN1				0xA600	//0b1 010011 0 00000000
#define 	WRITE_FEN2				0xA800	//0b1 010100 0 00000000
#define 	WRITE_SOFTSTART			0x8C00	//0b1 000110 0 00000000
#define		WRITE_FLATEN			0xAA00	//0b1 010101 0 00000000

/*Bitmasks*/
#define		BITMASK_CHX_EN			0x0003	//0b0000000000000011			/*mask for CH2EN and CH1EN*/
#define		BITMASK_HIGH_BYTE		0xFF00	//0b1111111100000000			/*mask for higher byte*/
#define		BITMASK_LOW_BYTE		0x00FF	//0b0000000011111111			/*mask for lower byte*/

/*LED current defines*/
#define 	START_LED_CURRENT		0x64									/*ILED=(CHxIADJ*2,4)/892,5; 9--> 24mA, 255--> 685mA*/
#define 	MAX_LED_CURRENT			0xFF									/*absolute max LED current is 255--> 685mA*/
#define		DEFINED_LED_CURRENT		0xEE									/*as 100% is defined 238 --> 640mA*/
#define		MIN_LED_CURRENT			0x09									/*max LED current is 9--> 24mA*/

/*PWM defines*/
#define		MAX_PWM					0x3FF									/*10bit!!!, 0x3FF --> 1023*/
#define		HALF_PWM				0x1FF									/*10bit!!!, 0x1FF --> 511*/
#define		NULL_PWM				0x000									/*10bit!!!, 0x000 --> 0*/

/*other defines*/
#define		EMPTY_DATA				0x00									/*by SPI read the data block should be 0x00*/
#define 	NO_FLT					0x6000									/*By read FLTx registers the response on SPI should be 0b1100 0000 0000 0000 = no fault*/




/* Private function prototypes -----------------------------------------------*/

extern LED_DRV_status_t LED_DRV_Init(SPI_HandleTypeDef *hspi);
extern LED_DRV_status_t Set_Current(SPI_HandleTypeDef *hspi, uint8_t SetCurrent);
extern LED_DRV_status_t Set_PWM(SPI_HandleTypeDef *hspi, uint16_t SetPWM);
extern LED_DRV_status_t Read_FLTx(SPI_HandleTypeDef *hspi);
extern LED_DRV_status_t Switch_OFF(SPI_HandleTypeDef *hspi);
extern LED_DRV_status_t Switch_ON(SPI_HandleTypeDef *hspi);
extern EN_status_t Get_ENStatusFLAG(void);

#endif /* LED_DRV_H_ */
