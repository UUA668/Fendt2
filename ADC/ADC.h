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

#define VREFINT adcBuffer[0]
#define UVLO adcBuffer[1]
#define NTC_CH6 adcBuffer[2]
#define NTC_CH1 adcBuffer[3]
#define NTC_CH2 adcBuffer[4]
#define NTC_CH3 adcBuffer[5]
#define NTC_CH4 adcBuffer[6]
#define NTC_CH5 adcBuffer[7]


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
extern uint16_t ADC_Value_VREFINT(void);
extern uint16_t ADC_Value_UVLO(void);
extern uint16_t ADC_Value_NTC_CH1(void);
extern uint16_t ADC_Value_NTC_CH2(void);
extern uint16_t ADC_Value_NTC_CH3(void);
extern uint16_t ADC_Value_NTC_CH4(void);
extern uint16_t ADC_Value_NTC_CH5(void);
extern uint16_t ADC_Value_NTC_CH6(void);
extern uint16_t ADC_Value_NTC_MAX(void);

extern void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);


#endif /* ADC_H_ */
