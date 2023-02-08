/*
 * Temp_CTRL.c
 *
 *  Created on: 02.02.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "Temp_CTRL.h"
#include "ADC.h"

/* Private variables -------------------------------------------------------------*/


//uint16_t CH1_Buffer[TempBufferSize] = {0};
//uint16_t CH2_Buffer[TempBufferSize] = {0};
//uint16_t CH3_Buffer[TempBufferSize] = {0};
//uint16_t CH4_Buffer[TempBufferSize] = {0};

uint16_t NTC_Max_Buffer[TempBufferSize] = {0};
uint8_t NTCMaxBufferCounter = 0;

uint32_t vrefint_Temp;

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
//			for (int i = 0; i < (TempBufferSize-1); i++)
//			{
//				CH1_Buffer[i] = CH1_Buffer[i+1];
//			}
//			CH1_Buffer[TempBufferSize-1] = __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH1(),LL_ADC_RESOLUTION_12B);
//
//			/*CH2*/
//			for (int i = 0; i < (TempBufferSize-1); i++)
//			{
//				CH2_Buffer[i] = CH2_Buffer[i+1];
//			}
//			CH2_Buffer[TempBufferSize-1] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH2(),LL_ADC_RESOLUTION_12B);
//
//			/*CH3*/
//			for (int i = 0; i < (TempBufferSize-1); i++)
//			{
//				CH3_Buffer[i] = CH3_Buffer[i+1];
//			}
//			CH3_Buffer[TempBufferSize-1] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH3(),LL_ADC_RESOLUTION_12B);
//
//			/*CH4*/
//			for (int i = 0; i < (TempBufferSize-1); i++)
//			{
//				CH4_Buffer[i] = CH4_Buffer[i+1];
//			}
//			CH4_Buffer[TempBufferSize-1] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_CH4(),LL_ADC_RESOLUTION_12B);
//
//		}

void NTC_Max_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_Temp = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/

	NTC_Max_Buffer[NTCMaxBufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_Temp,ADC_Value_NTC_MAX(),LL_ADC_RESOLUTION_12B);
	NTCMaxBufferCounter++;
	if (NTCMaxBufferCounter == (TempBufferSize))
	{
		NTCMaxBufferCounter = 0;
	}


}
