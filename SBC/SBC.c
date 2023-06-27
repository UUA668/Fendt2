/*
 * SBC.c
 *
 *  Created on: 26.06.2023
 *      Author: markfe1
 */
/* Private includes --------------------------------------------------------------*/
#include "SBC.h"
#include "SPI.h"
#include "stm32g0xx_hal_spi.h"

/* Private variables -------------------------------------------------------------*/

uint16_t 	SBC_Response = 0;

/*Private functions --------------------------------------------------------------*/

SBC_status_t SBC_Init(SPI_HandleTypeDef *hspi)
{

	SBC_Response = SBC_TXRX(hspi, SBC_READ_MAIN_STATUS, EMPTY_DATA);
	SBC_Response = SBC_TXRX(hspi, SBC_WRITE_MODE_CTRL, 0x01);





return SBC_OK;
}
