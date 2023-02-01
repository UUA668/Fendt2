/*
 * ADC.h
 *
 *  Created on: 30.01.2023
 *      Author: markfe1
 */

#ifndef ADC_H_
#define ADC_H_


/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private macro -------------------------------------------------------------*/
#define READED_ADC_CHANNEL 8			  /*how many channel are read wint ADC*/

/* Private defines------------------------------------------------------------*/

/*ADC status def*/
typedef enum {
	ADC_OK = 0,
	ADC_NOK,
} ADC_status_t;

/*ADC complete flag*/
typedef enum {
	YES = 0,
	NO,
};

/* Private function prototypes -----------------------------------------------*/
extern ADC_status_t ADC1_DMA1_Read(ADC_HandleTypeDef *hadc);
//extern void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);


#endif /* ADC_H_ */
