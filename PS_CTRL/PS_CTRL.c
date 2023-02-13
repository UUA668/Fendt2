/*
 * PS_CTRL.c
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "PS_CTRL.h"
#include "PS_CTRL_CFG.h"


/* Private variables -------------------------------------------------------------*/

uint16_t UVLO_Buffer[UVLOBUFFERSIZE] = {0};
uint8_t UVLOBufferCounter = 0;

uint32_t vrefint_PS;

/* Private prototypes --------------------------------------------------------------*/
void ValidityCheck(uint16_t Voltage);


/*-----------------------------Validity check limits-------------------------------*/
/*The UVLO Voltage cannot be below 680mV. 										   */
/*It would mean that the Vin is below 4,5V--> uC cannot function                   */
/*The UVLO Voltage cannot be above 3000mV.                                         */
/*It would mean that the Vin is above 20V--> input protection switch off Vin       */

s_Limits_t UVLO_Limits = {680, 3000};

/*Private functions --------------------------------------------------------------*/

/*---------------Read UVLO from ADC block and convert to voltage------------------*/
void UVLO_Read(void)
{
	/*Refresh the vrefint at first*/
	vrefint_PS = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_Value_VREFINT(),LL_ADC_RESOLUTION_12B);

	/*read the max value and convert to voltage*/
	UVLO_Buffer[UVLOBufferCounter] =  __LL_ADC_CALC_DATA_TO_VOLTAGE(vrefint_PS,ADC_Value_UVLO(),LL_ADC_RESOLUTION_12B);
	ValidityCheck(UVLO_Buffer[UVLOBufferCounter], UVLO_Limits);
	UVLOBufferCounter++;
	if (UVLOBufferCounter == (UVLOBUFFERSIZE))
	{
		UVLOBufferCounter = 0;
	}

}

/*-----------------------universal validity check function----------------------*/
void ValidityCheck(uint16_t Voltage)
{
	if ((Voltage < UVLOLOWERLIMIT) || (Voltage > UVLOUPPERLIMIT))
			{
			HAL_Delay(1);/*call error handler*/
			}
	return;
}


