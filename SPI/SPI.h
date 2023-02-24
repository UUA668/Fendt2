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


/* Private function prototypes -----------------------------------------------*/

extern SPI_status_t SPI_Init(SPI_HandleTypeDef *hspi);


#endif /* SPI_H_ */
