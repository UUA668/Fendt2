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

/*SPI standard read commands, it contains the odd parity bit too*/
#define 	READ_EN					0x0100	//0b0 000000 1 00000000
#define		READ_CFG1				0x0200	//0b0 000001 0 00000000
#define		READ_CFG2				0x0400	//0b0 000010 0 00000000
#define 	READ_FLT1				0x2300	//0b0 010001 1 00000000
#define 	READ_FLT2				0x2500	//0b0 010010 1 00000000
#define 	READ_CH1IADJ			0x0E00	//0b0 000111 0 00000000
#define 	READ_CH2IADJ			0x1000	//0b0 001000 0 00000000
#define 	READ_CH1PWML			0x1500	//0b0 001010 1 00000000
#define 	READ_CH1PWMH			0x1600	//0b0 001011 0 00000000
#define 	READ_CH2PWML			0x1900	//0b0 001100 1 00000000
#define 	READ_CH2PWMH			0x1A00	//0b0 001101 0 00000000
#define 	READ_FM					0x0B00	//0b0 000101 1 00000000
#define 	READ_FEN1				0x2600	//0b0 010011 0 00000000
#define 	READ_FEN2				0x2900	//0b0 010100 1 00000000
#define 	READ_SOFTSTART			0x0D00	//0b0 000110 1 00000000

/*SPI standard write commands, without odd parity bit, it will be added later*/
#define		WRITE_EN				0x8000	//0b1 000000 0 00000000
#define		WRITE_CFG1				0x8200	//0b1 000001 0 00000000
#define		WRITE_CFG2				0x8400	//0b1 000010 0 00000000
#define 	WRITE_CH1IADJ			0x8F00	//0b1 000111 0 00000000
#define 	WRITE_CH2IADJ			0x9100	//0b1 001000 0 00000000
#define 	WRITE_CH1PWML			0x9400	//0b1 001010 0 00000000
#define 	WRITE_CH1PWMH			0x9600	//0b1 001011 0 00000000
#define 	WRITE_CH2PWML			0x9800	//0b1 001100 0 00000000
#define 	WRITE_CH2PWMH			0x9A00	//0b1 001101 0 00000000
#define 	WRITE_FM				0x8A00	//0b1 000101 0 00000000
#define 	WRITE_FEN1				0xA600	//0b1 010011 0 00000000
#define 	WRITE_FEN2				0xA800	//0b1 010100 0 00000000
#define 	WRITE_SOFTSTART			0x8C00	//0b1 000110 0 00000000

/*Bitmasks*/
#define		BITMASK_CHX_EN			0x0003	//0b0000000000000011			/*mask for CH2EN and CH1EN*/
#define		BITMASK_HIGH_BYTE		0xFF00	//0b1111111100000000			/*mask for higher byte*/
#define		BITMASK_LOW_BYTE		0x00FF	//0b0000000011111111			/*mask for lower byte*/

/*other defines*/
#define 	START_LED_CURRENT		0x0A									/*9--> 30mA, 255--> 857mA*/


/* Private function prototypes -----------------------------------------------*/

extern LED_DRV_status_t LED_DRV_Init(SPI_HandleTypeDef *hspi);

#endif /* LED_DRV_H_ */
