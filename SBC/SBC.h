/*
 * SBC.h
 *
 *  Created on: 26.06.2023
 *      Author: markfe1
 */

#ifndef SBC_H_
#define SBC_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"


/* Private defines------------------------------------------------------------*/

/*SBC Status def*/
typedef enum {
	SBC_OK = 0,
	SBC_NOK,
} SBC_status_t;

/*SBC standard read commands*/
#define 	SBC_READ_WATCHDOG					0x0100	//0b0000000 1 00000000
#define 	SBC_READ_MODE_CTRL					0x0300	//0b0000001 1 00000000
#define 	SBC_READ_MAIN_STATUS				0x0700	//0b0000011 1 00000000
#define 	SBC_READ_SYS_EVENT_EN				0x0900	//0b0000100 1 00000000

#define 	SBC_WRITE_WATCHDOG					0x0100	//0b0000000 0 00000000
#define 	SBC_WRITE_MODE_CTRL					0x0300	//0b0000001 0 00000000
#define 	SBC_WRITE_MAIN_STATUS				0x0700	//0b0000011 0 00000000
#define 	SBC_WRITE_SYS_EVENT_EN				0x0900	//0b0000100 0 00000000

/*other defines*/
#define		EMPTY_DATA				0x00				/*by SPI read the data block should be 0x00*/

/* Private function prototypes -----------------------------------------------*/

extern SBC_status_t SBC_Init(SPI_HandleTypeDef *hspi);

#endif /* SBC_H_ */
