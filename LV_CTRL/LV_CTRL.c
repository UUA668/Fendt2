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


uint16_t FB1_Buffer[LV_BUFFERSIZE] = {FB_START_VALUE};
uint8_t FB1BufferCounter = FB_START_VALUE;
Validity_status_t FB1_Valid_Buffer[LV_BUFFERSIZE] = {VALID};

uint16_t FB2_Buffer[LV_BUFFERSIZE] = {FB_START_VALUE};
uint8_t FB2BufferCounter = FB_START_VALUE;
Validity_status_t FB2_Valid_Buffer[LV_BUFFERSIZE] = {VALID};

uint32_t vrefint_LV;


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
	if (FB1BufferCounter == (LV_BUFFERSIZE))
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
	if (FB2BufferCounter == (LV_BUFFERSIZE))
	{
		FB2BufferCounter = 0;
	}
}

/*-------------------------------validity check function---------------------------*/
Validity_status_t LVValidityCheck(uint16_t Voltage)
{
	if ((Voltage < LV_LOWERLIMIT) || (Voltage > LV_UPPERLIMIT))
			{
			return NOT_VALID;
			}
	return VALID;
}

/*------------------------------Calculate debounced FB1 value--------------------*/
uint16_t Get_Debounced_FB1()
{
	uint8_t ValidityCounter = 0;
	uint16_t Debounced_FB1 = 0;

	/*Check the validity statuses in the buffer and if there is more invalid as    */
	/*allowed (ALLOWED_INVALID_FB), call the error handler*/
	for(int i = 0; i < LV_BUFFERSIZE; i++)
		{
		ValidityCounter += FB1_Valid_Buffer[i];
		}

	if (ValidityCounter > ALLOWED_INVALID_FB)
		{

		HAL_Delay(1);/*call error handler instead of HAL_Delay*/
		}

	/*calculate the debounced UVLO value */
	ValidityCounter = 0; 											/*reset counter*/
	for(int j = 0; j < LV_BUFFERSIZE; j++)
		{
		if((FB1_Valid_Buffer[j] == VALID) && (FB1_Buffer[j] |= FB_START_VALUE))
			{
			Debounced_FB1 += FB1_Buffer[j];
			ValidityCounter += 1;
			}

		}

	Debounced_FB1 /= ValidityCounter;
	return Debounced_FB1;
}

/*------------------------------Calculate debounced FB2 value--------------------*/
uint16_t Get_Debounced_FB2()
{
	uint8_t ValidityCounter = 0;
	uint16_t Debounced_FB2 = 0;

	/*Check the validity statuses in the buffer and if there is more invalid as    */
	/*allowed (ALLOWED_INVALID_FB), call the error handler*/
	for(int i = 0; i < LV_BUFFERSIZE; i++)
		{
		ValidityCounter += FB2_Valid_Buffer[i];
		}

	if (ValidityCounter > ALLOWED_INVALID_FB)
		{

		HAL_Delay(1);/*call error handler instead of HAL_Delay*/
		}

	/*calculate the debounced UVLO value */
	ValidityCounter = 0; 											/*reset counter*/
	for(int j = 0; j < LV_BUFFERSIZE; j++)
		{
		if((FB2_Valid_Buffer[j] == VALID) && (FB2_Buffer[j] |= FB_START_VALUE))
			{
			Debounced_FB2 += FB2_Buffer[j];
			ValidityCounter += 1;
			}

		}

	Debounced_FB2 /= ValidityCounter;
	return Debounced_FB2;
}
