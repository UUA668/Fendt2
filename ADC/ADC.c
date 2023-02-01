/*
 * ADC.c
 *
 *  Created on: 30.01.2023
 *      Author: markfe1
 */

/* Private includes ----------------------------------------------------------*/
#include "ADC.h"


/* Private variables ---------------------------------------------------------*/

uint16_t adcResultDMA[READED_ADC_CHANNEL];		/*block for ADC result for DMA*/
uint16_t adcBuffer[(READED_ADC_CHANNEL)*5];		/*5 ADC block buffer*/
uint8_t BufferCounter = 0;						/*Start address counter for buffer*/

uint32_t adcChannelCount = sizeof (adcResultDMA) / sizeof (adcResultDMA[0]);

uint8_t adcConversationComplete = NO;			   	/*Complete flag set by callback*/
uint8_t adcFirstUse = YES;
/*Private functions*/

/*--------------------Start ADC conversation with DMA-------------------------*/
ADC_status_t ADC1_DMA1_Read(ADC_HandleTypeDef *hadc)
{
	if(hadc == 0)
	{
		return ADC_NOK;
	}

	if (adcFirstUse == YES)
	{
		adcConversationComplete = NO;
		HAL_ADC_Start_DMA(hadc, (uint32_t *)&adcResultDMA[0], adcChannelCount);
		adcFirstUse = NO;
		return ADC_OK;
	}

	if(adcConversationComplete >= NO)
	{
		return ADC_NOK;
	}


	for (int i = BufferCounter; i < (BufferCounter+READED_ADC_CHANNEL); i++)
		{
		adcBuffer[i] = adcResultDMA[(i-BufferCounter)];
		}

	BufferCounter = (BufferCounter+READED_ADC_CHANNEL);
	if(BufferCounter >= (READED_ADC_CHANNEL*5))
	{
		BufferCounter = 0;
	}


	adcConversationComplete = NO;
	HAL_ADC_Start_DMA(hadc, (uint32_t *)&adcResultDMA[0], adcChannelCount);

	return ADC_OK;
}

/*-------------------ADC complete callback------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	adcConversationComplete = YES;

}
