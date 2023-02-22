/*
 * Temp_CTRL_CFG.h
 *
 *  Created on: 14.02.2023
 *      Author: markfe1
 */

#ifndef TEMP_CTRL_CFG_H_
#define TEMP_CTRL_CFG_H_

/* Private macros------------------------------------------------------------------*/

#define TEMP_BUFFERSIZE 5


/*-----------------------------Validity check limits-------------------------------*/
/*The NTC Voltage cannot be below 100mV. 										   */
/*It would mean that the Temperature is below -40°C--> ASS COLD			          */
/*The NTC Voltage cannot be above 4700mV.                                         */
/*It would mean that the Temperature is above 125°C--> TOO HOT                    */
#define NTC_LOWERLIMIT 100
#define NTC_UPPERLIMIT 4700
#define ALLOWED_INVALID_NTC 1

#endif /* TEMP_CTRL_CFG_H_ */
