/*
 * Light_CTRL.c
 *
 *  Created on: 11.04.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "Light_CTRL.h"
#include "LED_DRV.h"
//#include "SPI.h"
//#include "stm32g0xx_hal_spi.h"

/* Private variables -------------------------------------------------------------*/


uint8_t 	SetCurrent = 0;
uint16_t	SetPWM = 0;


/* Private prototypes ------------------------------------------------------------*/


/* Private functions --------------------------------------------------------------*/

void Output_Voltage(SPI_HandleTypeDef *hspi, uint16_t FB1_Value, uint16_t FB2_Value)
{
	if (((FB1_Value < LED_MISSING_L) || (FB2_Value < LED_MISSING_L)) && (Get_ENStatusFLAG() == ENABLED))
		{
		Switch_OFF(hspi);
		return;
		}

	if (((FB1_Value > LED_MISSING_H) || (FB2_Value > LED_MISSING_H)) && (Get_ENStatusFLAG() == DISABLED))
		{
		Switch_ON(hspi);
		return;
		}
return;
}

void Calc_Current_V(SPI_HandleTypeDef *hspi, uint16_t UVLO)
{
	if(UVLO < VIN_LOW)
		{
		Switch_OFF(hspi);
		/*call Status LED function*/
		return;
		}
}


void CurrentStartup(SPI_HandleTypeDef *hspi)
{
	for (int i = 25; i > 0; i--)
		{
		Set_Current(hspi, (DEFINED_LED_CURRENT/i));
		HAL_Delay(20);
		}
}
