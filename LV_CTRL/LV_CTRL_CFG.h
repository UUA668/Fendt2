/*
 * LV_CTRL_CFG.h
 *
 *  Created on: 14.02.2023
 *      Author: markfe1
 */

#ifndef LV_CTRL_CFG_H_
#define LV_CTRL_CFG_H_

/* Private macros-------------------------------------------------------------*/

#define LVBUFFERSIZE 5

/*-----------------------------Validity check limits-------------------------------*/
/*The LV Voltage cannot be below 534mV. It would mean 							   */
/*that the LED chain voltage is below 20V--> Boost topology does not function      */
/*The LV Voltage cannot be above 1200mV.                                           */
/*It would mean that the LED chain voltage is above 45V--> LED Driver switches off */
#define LVLOWERLIMIT 534
#define LVUPPERLIMIT 1200


#endif /* LV_CTRL_CFG_H_ */
