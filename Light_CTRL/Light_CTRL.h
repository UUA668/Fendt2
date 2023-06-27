/*
 * Light_CTRL.h
 *
 *  Created on: 11.04.2023
 *      Author: markfe1
 */

#ifndef LIGHT_CTRL_H_
#define LIGHT_CTRL_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private defines------------------------------------------------------------*/



#define LED_MISSING_L 	700
#define LED_MISSING_H 	740
#define VIN_LOW 		830

/* Private function prototypes -----------------------------------------------*/

extern void Output_Voltage(SPI_HandleTypeDef *hspi, uint16_t FB1_Value, uint16_t FB2_Value);
extern void Calc_Current_V(SPI_HandleTypeDef *hspi, uint16_t UVLO);
extern void Calc_Current_T(SPI_HandleTypeDef *hspi, uint16_t NTC_Max);
extern void CurrentUp(SPI_HandleTypeDef *hspi);

#endif /* LIGHT_CTRL_H_ */
