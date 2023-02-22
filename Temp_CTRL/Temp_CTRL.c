/*
 * Temp_CTRL.c
 *
 *  Created on: 02.02.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "Temp_CTRL.h"
#include "Temp_CTRL_CFG.h"
#include "ADC.h"

/* Private variables -------------------------------------------------------------*/


//uint16_t CH1_Buffer[TEMP_BUFFERSIZE] = {NTC_START_VALUE};
//uint16_t CH2_Buffer[TEMP_BUFFERSIZE] = {NTC_START_VALUE};
//uint16_t CH3_Buffer[TEMP_BUFFERSIZE] = {NTC_START_VALUE};
//uint16_t CH4_Buffer[TEMP_BUFFERSIZE] = {NTC_START_VALUE};

uint16_t NTC_Max_Buffer[TEMP_BUFFERSIZE] = {NTC_START_VALUE};
Validity_status_t NTC_Max_Valid_Buffer[TEMP_BUFFERSIZE] = {VALID};
uint8_t NTCMaxBufferCounter = 0;

uint32_t vrefint_Temp;


/* Private prototypes --------------------------------------------------------------*/
Validity_status_t TempValidityCheck(uint16_t Voltage);



/* Read the NTC values and fill the buffer----------------------------------------*/
/*Function void NTC_Value_Read(void) read the values separately					  */
/*Function void NTC_Max_Read(void) read the max Value only   					  */
/* Voltage limits with temperatures */
/*  -40°C --> 108mV					*/
/*    0°C --> 814mV					*/
/*  +50°C --> 2897mV				*/
/* +100°C --> 4261mV				*/
/* +115°C --> 4460mV				*/

//void NTC_Value_Read(void)
//		{
//			/*Refresh the vrefint at first*/
//			vrefint_Temp = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);
//
//
//			/*CH1*/
//			for (int i = 0; i < (TEMP_BUFFERSIZE-1); i++)
//			{
//				CH1_Buffer[i] = CH1_Buffer[i+1];
//			}
//			CH1_Buffer[TEMP_BUFFERSIZE-1] = __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH1(),LL_ADC_RESOLUTION_12B);
//
//			/*CH2*/
//			for (int i = 0; i < (TEMP_BUFFERSIZE-1); i++)
//			{
//				CH2_Buffer[i] = CH2_Buffer[i+1];
//			}
//			CH2_Buffer[TEMP_BUFFERSIZE-1] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH2(),LL_ADC_RESOLUTION_12B);
//
//			/*CH3*/
//			for (int i = 0; i < (TEMP_BUFFERSIZE-1); i++)
//			{
//				CH3_Buffer[i] = CH3_Buffer[i+1];
//			}
//			CH3_Buffer[TEMP_BUFFERSIZE-1] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH3(),LL_ADC_RESOLUTION_12B);
//
//			/*CH4*/
//			for (int i = 0; i < (TEMP_BUFFERSIZE-1); i++)
//			{
//				CH4_Buffer[i] = CH4_Buffer[i+1];
//			}
//			CH4_Buffer[TEMP_BUFFERSIZE-1] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH4(),LL_ADC_RESOLUTION_12B);
//
//		}

void NTC_Max_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_Temp = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/

	NTC_Max_Buffer[NTCMaxBufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_MAX(),LL_ADC_RESOLUTION_12B);
	NTC_Max_Valid_Buffer [NTCMaxBufferCounter]= TempValidityCheck(NTC_Max_Buffer[NTCMaxBufferCounter]);
	NTCMaxBufferCounter++;
	if (NTCMaxBufferCounter == (TEMP_BUFFERSIZE))
	{
		NTCMaxBufferCounter = 0;
	}
}



/*-------------------------------validity check function---------------------------*/
Validity_status_t TempValidityCheck(uint16_t Voltage)
{
	if ((Voltage < NTC_LOWERLIMIT) || (Voltage > NTC_UPPERLIMIT))
			{
			return NOT_VALID;
			}
	return VALID;
}

/*------------------------------Calculate debounced NTC_Max value---------------------*/
uint16_t Get_Debounced_NTC_Max()
{
	uint8_t ValidityCounter = 0;
	uint16_t Debounced_NTC_Max = 0;

	/*Check the validity statuses in the buffer and if there is more invalid as    */
	/*allowed (ALLOWED_INVALID_NTC), call the error handler*/
	for(int i = 0; i < TEMP_BUFFERSIZE; i++)
		{
		ValidityCounter += NTC_Max_Valid_Buffer[i];
		}

	if (ValidityCounter > ALLOWED_INVALID_NTC)
		{

		HAL_Delay(1);/*call error handler instead of HAL_Delay*/
		}

	/*calculate the debounced UVLO value */
	ValidityCounter = 0; 											/*reset counter*/
	for(int j = 0; j < TEMP_BUFFERSIZE; j++)
		{
		if((NTC_Max_Valid_Buffer[j] == VALID) && (NTC_Max_Buffer[j] |= NTC_START_VALUE))
			{
			Debounced_NTC_Max += NTC_Max_Buffer[j];
			ValidityCounter += 1;
			}

		}

	Debounced_NTC_Max /= ValidityCounter;
	return Debounced_NTC_Max;
}
