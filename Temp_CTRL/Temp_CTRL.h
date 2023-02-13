/*
 * Temp_CTRL.h
 *
 *  Created on: 02.02.2023
 *      Author: markfe1
 */

#ifndef TEMP_CTRL_H_
#define TEMP_CTRL_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"


/* Private macros-------------------------------------------------------------*/

#define TempBufferSize 5

/* Private function prototypes -----------------------------------------------*/

extern void NTC_Value_Read(void);
extern void NTC_Max_Read(void);

#endif /* TEMP_CTRL_H_ */
