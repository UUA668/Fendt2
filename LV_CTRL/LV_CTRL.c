/*
 * LV_CTRL.c
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */
/* Private includes --------------------------------------------------------------*/
#include "LV_CTRL.h"
#include "ADC.h"

/* Private variables -------------------------------------------------------------*/


uint16_t FB1_Buffer[FBBufferSize] = {0};
uint16_t FB2_Buffer[FBBufferSize] = {0};

uint32_t vrefint_LV;

uint8_t FB1BufferCounter = 0;
uint8_t FB2BufferCounter = 0;

/*-----------------------------Validity check limits-------------------------------*/
/*The LV Voltage cannot be below 534mV. It would mean 							   */
/*that the LED chain voltage is below 20V--> Boost topology does not function      */
/*The LV Voltage cannot be above 1200mV.                                           */
/*It would mean that the LED chain voltage is above 45V--> LED Driver switches off */

s_Limits_t LV_Limits = {534, 1200};


/*Private functions --------------------------------------------------------------*/

void FB1_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_LV = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/
	FB1_Buffer[FB1BufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_LV,ADC_Value_FB1(),LL_ADC_RESOLUTION_12B);
	FB1BufferCounter++;
	if (FB1BufferCounter == (FBBufferSize))
	{
		FB1BufferCounter = 0;
	}
}

void FB2_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_LV = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/
	FB2_Buffer[FB2BufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_LV,ADC_Value_FB2(),LL_ADC_RESOLUTION_12B);
	FB2BufferCounter++;
	if (FB2BufferCounter == (FBBufferSize))
	{
		FB2BufferCounter = 0;
	}
}
