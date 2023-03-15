/*
 * SPI.h
 *
 *  Created on: Feb 22, 2023
 *      Author: markfe1
 */

#ifndef SPI_H_
#define SPI_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private defines------------------------------------------------------------*/

/*SPI Status def*/
typedef enum {
	SPI_OK = 0,
	SPI_NOK,
} SPI_status_t;


/*SPI Error format*/
#define 	SPI_ERROR				0x8000	//0b1 000000 0 00000000

/*SPI masks*/
#define 	BITMASK_SPI_ERROR		0x8000	//0b1 000000 0 00000000


#define PLACE_ODD_PARITY 9								/*the place of the parity bit in byte*/

/* Private function prototypes -----------------------------------------------*/

extern uint16_t SPI_TXRX(SPI_HandleTypeDef *hspi, uint16_t CommandFrame, uint8_t Data);
extern uint16_t GetOddParity(uint16_t input);


#endif /* SPI_H_ */
