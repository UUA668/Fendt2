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

/* Private macros-------------------------------------------------------------*/

#define VoltBufferSize 10

/* Private function prototypes -----------------------------------------------*/

extern void UVLO_Read(void);
extern void FB1_Read(void);
extern void FB2_Read(void);


#endif /* PS_CTRL_H_ */
