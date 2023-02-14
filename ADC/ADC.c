/*
 * ADC.c
 *
 *  Created on: 30.01.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "ADC.h"


/* Private variables -------------------------------------------------------------*/

uint16_t adcResultDMA[READED_ADC_CHANNEL];			/*block for ADC result for DMA*/
uint16_t adcBuffer[READED_ADC_CHANNEL];				  /*ADC Buffer for later usage*/
uint32_t adcChannelCount = sizeof (adcResultDMA) / sizeof (adcResultDMA[0]);

uint8_t adcConversationComplete = NO;			   	/*Complete flag set by callback*/



/*Private functions ---------------------------------------------------------------*/

/*--------------------Start ADC conversation with DMA-----------------------------*/
ADC_status_t ADC1_DMA1_Read(ADC_HandleTypeDef *hadc)
{
	if(hadc == 0)
	{
		return ADC_NOK;
	}

	for (int i = 0; i < READED_ADC_CHANNEL; i++)
		{
		adcBuffer[i] = adcResultDMA[i];
		}

	adcConversationComplete = NO;
	HAL_ADC_Start_DMA(hadc, (uint32_t *)&adcResultDMA[0], adcChannelCount);

	return ADC_OK;
}

/*-------------------ADC complete callback----------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

	adcConversationComplete = YES;

}

/*------------------ADC Conversation Complete check-------------------------------*/

ADC_complete_t ADC_ConvCpltCheck(ADC_HandleTypeDef *hadc)
{
	return adcConversationComplete;
}




/*-------------------VREFINT request funktion-------------------------------------*/

uint16_t ADC_Value_VREFINT(void)
{
	return VREFINT;
}

/*-------------------UVLO request funktion-------------------------------------*/

uint16_t ADC_Value_UVLO(void)
{
	return UVLO;
}

/*-------------------FB1 request funktion-------------------------------------*/

uint16_t ADC_Value_FB1(void)
{
	return FB1;
}

/*-------------------FB2 request funktion-------------------------------------*/

uint16_t ADC_Value_FB2(void)
{
	return FB2;
}

/*-------------------NTC_CH1 request funktion-------------------------------------*/

uint16_t ADC_Value_NTC_CH1(void)
{
	return NTC_CH1;
}

/*-------------------NTC_CH2 request funktion-------------------------------------*/

uint16_t ADC_Value_NTC_CH2(void)
{
	return NTC_CH2;
}

/*-------------------NTC_CH3 request funktion-------------------------------------*/

uint16_t ADC_Value_NTC_CH3(void)
{
	return NTC_CH3;
}

/*-------------------NTC_CH4 request funktion-------------------------------------*/

uint16_t ADC_Value_NTC_CH4(void)
{
	return NTC_CH4;
}

/*-------------------NTC_max value request funktion-------------------------------*/

uint16_t ADC_Value_NTC_MAX(void)
{
	uint16_t Max_NTC_Value = 0;

	for (int i = 4; i < READED_ADC_CHANNEL; i++)	/* 4 is the first NTC channel*/
	{
	if(Max_NTC_Value < adcBuffer[i])
	{
		Max_NTC_Value = adcBuffer[i];
	}
	}

	return Max_NTC_Value;
}


