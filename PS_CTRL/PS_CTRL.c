/*
 * PS_CTRL.c
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "ADC.h"
#include "PS_CTRL.h"
#include "PS_CTRL_CFG.h"


/* Private variables -------------------------------------------------------------*/

uint16_t UVLO_Buffer[UVLOBUFFERSIZE] = {0};
uint8_t UVLOBufferCounter = 0;
Validity_status_t UVLO_Valid_Buffer[UVLOBUFFERSIZE] = {NOT_VALID};

uint32_t vrefint_PS;

/* Private prototypes --------------------------------------------------------------*/
Validity_status_t UVLOValidityCheck(uint16_t Voltage);

/*Private functions --------------------------------------------------------------*/

/*---------------Read UVLO from ADC block and convert to voltage------------------*/
void UVLO_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_PS = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/
	UVLO_Buffer[UVLOBufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_PS,ADC_Value_UVLO(),LL_ADC_RESOLUTION_12B);
	UVLO_Valid_Buffer[UVLOBufferCounter] = UVLOValidityCheck(UVLO_Buffer[UVLOBufferCounter]);
	UVLOBufferCounter++;
	if (UVLOBufferCounter == (UVLOBUFFERSIZE))
	{
		UVLOBufferCounter = 0;
	}

}

/*-------------------------------validity check function---------------------------*/
Validity_status_t UVLOValidityCheck(uint16_t Voltage)
{
	if ((Voltage < UVLOLOWERLIMIT) || (Voltage > UVLOUPPERLIMIT))
			{
			return NOT_VALID;
			}
	return VALID;
}


