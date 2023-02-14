/*
 * LV_CTRL.c
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */
/* Private includes --------------------------------------------------------------*/
#include "LV_CTRL.h"
#include "LV_CTRL_CFG.h"
#include "ADC.h"

/* Private variables -------------------------------------------------------------*/


uint16_t FB1_Buffer[LVBUFFERSIZE] = {0};
Validity_status_t FB1_Valid_Buffer[LVBUFFERSIZE] = {0};
uint16_t FB2_Buffer[LVBUFFERSIZE] = {0};
Validity_status_t FB2_Valid_Buffer[LVBUFFERSIZE] = {0};

uint32_t vrefint_LV;

uint8_t FB1BufferCounter = 0;
uint8_t FB2BufferCounter = 0;


/* Private prototypes --------------------------------------------------------------*/
Validity_status_t LVValidityCheck(uint16_t Voltage);

/*Private functions --------------------------------------------------------------*/

void FB1_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_LV = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the value and convert to voltage*/
	FB1_Buffer[FB1BufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_LV,ADC_Value_FB1(),LL_ADC_RESOLUTION_12B);
	FB1_Valid_Buffer[FB1BufferCounter]= LVValidityCheck(FB1_Buffer[FB1BufferCounter]);
	FB1BufferCounter++;
	if (FB1BufferCounter == (LVBUFFERSIZE))
	{
		FB1BufferCounter = 0;
	}
}

void FB2_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_LV = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the value and convert to voltage*/
	FB2_Buffer[FB2BufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_LV,ADC_Value_FB2(),LL_ADC_RESOLUTION_12B);
	FB2_Valid_Buffer[FB2BufferCounter]= LVValidityCheck(FB2_Buffer[FB2BufferCounter]);
	FB2BufferCounter++;
	if (FB2BufferCounter == (LVBUFFERSIZE))
	{
		FB2BufferCounter = 0;
	}
}

/*-------------------------------validity check function---------------------------*/
Validity_status_t LVValidityCheck(uint16_t Voltage)
{
	if ((Voltage < LVLOWERLIMIT) || (Voltage > LVUPPERLIMIT))
			{
			return NOT_VALID;
			}
	return VALID;
}

