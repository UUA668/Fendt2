/*
 * LV_CTRL_CFG.h
 *
 *  Created on: 14.02.2023
 *      Author: markfe1
 */

#ifndef LV_CTRL_CFG_H_
#define LV_CTRL_CFG_H_

/* Private macros-------------------------------------------------------------*/

#define LV_BUFFERSIZE 5

/*-----------------------------Validity check limits-------------------------------*/
/*The LV Voltage cannot be below 534mV. It would mean 							   */
/*that the LED chain voltage is below 20V--> Boost topology does not function      */
/*The LV Voltage cannot be above 1200mV.                                           */
/*It would mean that the LED chain voltage is above 45V--> LED Driver switches off */
#define LV_LOWERLIMIT 534
#define LV_UPPERLIMIT 1200
#define ALLOWED_INVALID_FB 1

#endif /* LV_CTRL_CFG_H_ */
