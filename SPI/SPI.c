/*
 * SPI.c
 *
 *  Created on: Feb 22, 2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "SPI.h"
#include "stm32g0xx_hal_gpio.h"

/* Private variables -------------------------------------------------------------*/

/*Read frame for TSP92682 consists of a CMD bit,
six bits of ADDRESS, a PARITY bit (odd parity), and eight bits of DATA. The format of the Command frame is
shown in Figure 45. The bit sequence is as follows:
1. The COMMAND bit (CMD). CMD = 1 means the transfer is a write command; CMD = 0 means it is a read
command.
2. Six bits of ADDRESS (A5..A0).
3. The PARITY bit (PAR). This bit is set by the following equation: PARITY = XNOR(CMD, A5..A0, D7..D0).
4. Eight bits of DATA (D7..D0). For read commands, the DATA bits must be set to zero*/
uint8_t ReadFrameHigh = 0b00000000;
uint8_t ReadFrameLow = 0b00000000;
uint8_t *ptr_ReadFrame = &ReadFrameHigh;

uint16_t SPI_Receive_Buffer = 0;
uint16_t *ptr_SPI_Receiver_Buffer = &SPI_Receive_Buffer;

/* Private prototypes ------------------------------------------------------------*/


/*Private functions --------------------------------------------------------------*/

SPI_status_t SPI_Init(SPI_HandleTypeDef *hspi)
{
	/*check the incoming parameters*/
	if(NULL == hspi)
	{
		return SPI_NOK;
	}
	ReadFrameLow = 0b00000000; 								/*read EN register on address 00h*/
	ReadFrameHigh = 0b00000001;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);			/*SSN1 chip selected */
	HAL_SPI_Transmit(hspi, ptr_ReadFrame, 2, 100);
	HAL_SPI_Receive(hspi, &SPI_Receive_Buffer, 1, 100);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);				/*SSN1 chip deselected */


	return SPI_OK;
}
