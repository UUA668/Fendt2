/*
 * PS_CTRL.c
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "PS_CTRL.h"
#include "ADC.h"

/* Private variables -------------------------------------------------------------*/

uint16_t UVLO_Buffer[UVLOBufferSize] = {0};
uint8_t UVLOBufferCounter = 0;

uint32_t vrefint_PS;

/*Private functions --------------------------------------------------------------*/

void UVLO_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_PS = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/
	UVLO_Buffer[UVLOBufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_PS,ADC_Value_UVLO(),LL_ADC_RESOLUTION_12B);
	UVLOBufferCounter++;
	if (UVLOBufferCounter == (UVLOBufferSize))
	{
		UVLOBufferCounter = 0;
	}
}


