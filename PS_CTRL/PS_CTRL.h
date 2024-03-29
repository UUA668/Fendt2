/*
 * PC_CTRL.h
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */

#ifndef PS_CTRL_H_
#define PS_CTRL_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private defines------------------------------------------------------------*/

#define UVLO_START_VALUE 0

/* Private function prototypes -----------------------------------------------*/

extern void UVLO_Read(void);
extern uint16_t Get_Debounced_UVLO();


#endif /* PS_CTRL_H_ */
