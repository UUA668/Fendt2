/*
 * SPI.c
 *
 *  Created on: Feb 22, 2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "SPI.h"
#include "stm32g0xx_hal_gpio.h"
#include "stm32g0xx_hal_def.h"

/* Private variables -------------------------------------------------------------*/



/*Command frame for TSP92682 consists of a CMD bit,
six bits of ADDRESS, a PARITY bit (odd parity), and eight bits of DATA. The format of the Command frame is
shown in Figure 45. The bit sequence is as follows:
1. The COMMAND bit (CMD). CMD = 1 means the transfer is a write command; CMD = 0 means it is a read
command.
2. Six bits of ADDRESS (A5..A0).
3. The PARITY bit (PAR). This bit is set by the following equation: PARITY = XNOR(CMD, A5..A0, D7..D0).
4. Eight bits of DATA (D7..D0). For read commands, the DATA bits must be set to zero*/


/* Private prototypes ------------------------------------------------------------*/


/*Private functions --------------------------------------------------------------*/

uint16_t SPI_TXRX(SPI_HandleTypeDef *hspi, uint16_t CommandFrame, uint8_t Data)
{
	uint16_t 	*ptr_CommandFrame = &CommandFrame;
	uint16_t 	ResponseFrame = 0;
	uint16_t 	*ptr_ResponseFrame = &ResponseFrame;



	/*check the incoming parameters*/
	if(NULL == hspi)
	{
		HAL_Delay(1);/*instead of delay call error handler*/
	}

	/*add Data to CommandFrame*/
	CommandFrame += Data;
	/*complete the CommandFrame with Parity bit*/
	CommandFrame = GetOddParity(CommandFrame);

	/*TX...RX*/
	HAL_SPI_Transmit(hspi, ptr_CommandFrame, 1, 100);
	HAL_SPI_Receive(hspi, ptr_ResponseFrame, 1, 100);

	/*check SPI error*/
	if((ResponseFrame & BITMASK_SPI_ERROR) == SPI_ERROR)
	{
		HAL_Delay(1);/*instead of delay call error handler*/
	}

	return ResponseFrame;
}


/*Calculate Odd Parity from input, and add to input on the right place*/
uint16_t GetOddParity(uint16_t input)
{
	uint16_t buffer;
	uint16_t state;
	uint16_t i;

	buffer = input;

	for(i = 0, state = 0; i < ((sizeof(input)*8)); i++)
	{
	    state = state ^ (input & 1);
	    input = input >> 1;
	}

	/*toggle state because of odd parity*/
	state ^= 1;

	/*shift the parity in the right position*/
	state = state << (PLACE_ODD_PARITY-1);

	/*load parity bit to buffer*/
	buffer |= state;

	return buffer;
}

