/*
 * Temp_CTRL_CFG.h
 *
 *  Created on: 14.02.2023
 *      Author: markfe1
 */

#ifndef TEMP_CTRL_CFG_H_
#define TEMP_CTRL_CFG_H_

/* Private macros-------------------------------------------------------------*/

#define TEMPBUFFERSIZE 5

/*-----------------------------Validity check limits-------------------------------*/
/*The NTC Voltage cannot be below 100mV. 										   */
/*It would mean that the Temperature is below -40°C--> ASS COLD			          */
/*The NTC Voltage cannot be above 4700mV.                                         */
/*It would mean that the Temperature is above 125°C--> TOO HOT                    */
#define TEMPLOWERLIMIT 100
#define TEMPUPPERLIMIT 4700


#endif /* TEMP_CTRL_CFG_H_ */
