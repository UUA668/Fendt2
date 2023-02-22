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

uint16_t UVLO_Buffer[UVLO_BUFFERSIZE] = {UVLO_START_VALUE};
uint8_t UVLOBufferCounter = UVLO_START_VALUE;
Validity_status_t UVLO_Valid_Buffer[UVLO_BUFFERSIZE] = {VALID};


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
	if (UVLOBufferCounter == (UVLO_BUFFERSIZE))
	{
		UVLOBufferCounter = 0;
	}

}

/*-------------------------------validity check function---------------------------*/
Validity_status_t UVLOValidityCheck(uint16_t Voltage)
{
	if ((Voltage < UVLO_LOWERLIMIT) || (Voltage > UVLO_UPPERLIMIT))
			{
			return NOT_VALID;
			}
	return VALID;
}

/*------------------------------Calculate debounced UVLO value---------------------*/
uint16_t Get_Debounced_UVLO()
{
	uint8_t ValidityCounter = 0;
	uint16_t Debounced_UVLO = 0;

	/*Check the validity statuses in the buffer and if there is more invalid as    */
	/*allowed (ALLOWED_INVALID_UVLO), call the error handler*/
	for(int i = 0; i < UVLO_BUFFERSIZE; i++)
		{
		ValidityCounter += UVLO_Valid_Buffer[i];
		}

	if (ValidityCounter > ALLOWED_INVALID_UVLO)
		{

		HAL_Delay(1);/*call error handler instead of HAL_Delay*/
		}

	/*calculate the debounced UVLO value */
	ValidityCounter = 0; 											/*reset counter*/
	for(int j = 0; j < UVLO_BUFFERSIZE; j++)
		{
		if((UVLO_Valid_Buffer[j] == VALID) && (UVLO_Buffer[j] |= UVLO_START_VALUE))
			{
			Debounced_UVLO += UVLO_Buffer[j];
			ValidityCounter += 1;
			}

		}

	Debounced_UVLO /= ValidityCounter;
	return Debounced_UVLO;
}
