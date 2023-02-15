/*
 * PS_CTRL_CFG.h
 *
 *  Created on: 10.02.2023
 *      Author: markfe1
 */

#ifndef PS_CTRL_CFG_H_
#define PS_CTRL_CFG_H_

/* Private macros-------------------------------------------------------------*/

#define UVLO_BUFFERSIZE 5

/*-----------------------------Validity check limits-------------------------------*/
/*The UVLO Voltage cannot be below 680mV. 										   */
/*It would mean that the Vin is below 4,5V--> uC cannot function                   */
/*The UVLO Voltage cannot be above 3000mV.                                         */
/*It would mean that the Vin is above 20V--> input protection switch off Vin       */
#define UVLO_LOWERLIMIT 680
#define UVLO_UPPERLIMIT 3000
#define ALLOWED_INVALID_UVLO 1


#endif /* PS_CTRL_CFG_H_ */
