/*
 * LV_CTRL.h
 *
 *  Created on: 07.02.2023
 *      Author: markfe1
 */

#ifndef LV_CTRL_H_
#define LV_CTRL_H_

/* Private includes ----------------------------------------------------------*/
#include "stm32g0xx_hal.h"


/* Private defines------------------------------------------------------------*/

#define FB_START_VALUE 0

/* Private function prototypes -----------------------------------------------*/

extern void FB1_Read(void);
extern void FB2_Read(void);
extern uint16_t Get_Debounced_FB1();
extern uint16_t Get_Debounced_FB2();


#endif /* LV_CTRL_H_ */
