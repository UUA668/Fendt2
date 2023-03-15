/*
 * LED_DRIVER.c
 *
 *  Created on: 14.03.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "LED_DRV.h"
#include "stm32g0xx_hal_spi.h"

/* Private variables -------------------------------------------------------------*/



uint16_t SPI_Response = 0;

/* Private prototypes ------------------------------------------------------------*/


/*Private functions --------------------------------------------------------------*/


LED_DRV_status_t LED_DRV_Init(SPI_HandleTypeDef *hspi)
{
/*----------------------------------------------1--------------------------------------------------------------------*/

/* set INTPWM (0x40-->0b 0100 0000), internal PWM inputs are used, if is set to 0, the PWM pin has to be connected to VDD */
	SPI_Response = SPI_TXRX(hspi, WRITE_CFG1, 0x40);

/* read FLT1 registers on POR to clear all the fault read bits and the PC-bit, Data has to be 0x00 by read command */
	SPI_Response = SPI_TXRX(hspi, READ_FLT1, 0x00);

/* read FLT2 registers on POR to clear all the fault read bits and the PC-bit, Data has to be 0x00 by read command */
	SPI_Response = SPI_TXRX(hspi, READ_FLT2, 0x00);

/* set the FPINRST bit in order for the Fault-PINS to be cleared, this bit is write only any read return 0 */
	/*Read EN*/
	SPI_Response = SPI_TXRX(hspi, READ_EN, 0x00);
	/*set only the FPINRST, all other stay the same*/
	SPI_Response |= (1UL << 7);
	/*write the whole EN*/
	SPI_Response = SPI_TXRX(hspi, WRITE_EN, (uint8_t)SPI_Response);

/* program the DAC Output for CH1, if CH1IADJ <=8 channel is off; can be set from 30mA to 857mA (9 to 255) */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1IADJ, START_LED_CURRENT);

/* program the DAC Output for CH1, if CH1IADJ <=8 channel is off; can be set from 30mA to 857mA (9 to 255) */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2IADJ, START_LED_CURRENT);

/* Switch off Softstart */
	SPI_Response = SPI_TXRX(hspi, WRITE_SOFTSTART, 0x00);

/* set EN bit*/
	/*Read EN*/
	SPI_Response = SPI_TXRX(hspi, READ_EN, 0x00);
	/*set only the CH1EN, all other stay the same*/
	SPI_Response |= (1UL << 1);
	/*set only the CH1EN, all other stay the same*/
	SPI_Response |= (1UL << 0);
	/*write the whole EN*/
	SPI_Response = SPI_TXRX(hspi, WRITE_EN, (uint8_t)SPI_Response);

/*-------------------------------------------------2---------------------------------------------------------------*/

/*Read EN, FLT1 and FLT2 to check the status*/
	SPI_Response = SPI_TXRX(hspi, READ_FLT1, 0x00);
	SPI_Response = SPI_TXRX(hspi, READ_FLT2, 0x00);
	SPI_Response = SPI_TXRX(hspi, READ_EN, 0x00);

/* Frequency Modulation configuration
 * FMMAG1:0--> 11: The modulation magnitude is set to ±15%.
 * FMFREQ3:0--> 0001: FM frequency is 1÷3584 of CLKM frequency. */
	SPI_Response = SPI_TXRX(hspi, WRITE_FM, 0x31);

/* configuration of FEN2 register - enable overcurrent, ILIM and ISN open pin fault for CH1 */
	SPI_Response = SPI_TXRX(hspi, WRITE_FEN2, 0x15);

/* set PWM width; 10bit value! */
/* write first to PWMH register; transfer to the CHxPWM counter only upon the write to the CHxPWML register */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1PWMH, 0x03);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1PWML, 0xFF);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2PWMH, 0x03);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2PWML, 0xFF);

return LED_DRV_OK;
}
