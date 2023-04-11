/*
 * LED_DRIVER.c
 *
 *  Created on: 14.03.2023
 *      Author: markfe1
 */

/* Private includes --------------------------------------------------------------*/
#include "LED_DRV.h"
#include "SPI.h"
#include "stm32g0xx_hal_spi.h"

/* Private variables -------------------------------------------------------------*/

uint16_t SPI_Response = 0;
uint16_t FLT1_Register = 0;
uint16_t FLT2_Register = 0;

/* Private prototypes ------------------------------------------------------------*/


/*Private functions --------------------------------------------------------------*/

/*Init LED Driver and setup the registers. Initial LED Current is START_LED_CURRENT, initial PWM is 100%*/
LED_DRV_status_t LED_DRV_Init(SPI_HandleTypeDef *hspi)
{
/*----------------------------------------------1--------------------------------------------------------------------*/

/* set INTPWM (0x40-->0b 0100 0000), internal PWM inputs are used, if is set to 0, the PWM pin has to be connected to VDD */
	SPI_Response = SPI_TXRX(hspi, WRITE_CFG1, 0x40);

/* read FLT1 registers on POR to clear all the fault read bits and the PC-bit, Data has to be 0x00 by read command */
	SPI_Response = SPI_TXRX(hspi, READ_FLT1, EMPTY_DATA);

/* read FLT2 registers on POR to clear all the fault read bits and the PC-bit, Data has to be 0x00 by read command */
	SPI_Response = SPI_TXRX(hspi, READ_FLT2, EMPTY_DATA);

/* set the FPINRST bit in order for the Fault-PINS to be cleared, this bit is write only any read return 0 */
	/*Read EN*/
	SPI_Response = SPI_TXRX(hspi, READ_EN, EMPTY_DATA);
	/*set only the FPINRST, all other stay the same*/
	SPI_Response |= (1UL << 7);
	/*write the whole EN*/
	SPI_Response = SPI_TXRX(hspi, WRITE_EN, (uint8_t)SPI_Response);

/* program the DAC Output for CH1, if CH1IADJ <=8 channel is off; can be set from 30mA to 857mA (9 to 255) */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1IADJ, START_LED_CURRENT);

/* program the DAC Output for CH2, if CH2IADJ <=8 channel is off; can be set from 30mA to 857mA (9 to 255) */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2IADJ, START_LED_CURRENT);

/* Switch off Softstart */
	SPI_Response = SPI_TXRX(hspi, WRITE_SOFTSTART, 0x00);

/*-------------------------------------------------2---------------------------------------------------------------*/

/* Frequency Modulation configuration
 * FMMAG1:0--> 11: The modulation magnitude is set to ±15%.
 * FMFREQ3:0--> 0001: FM frequency is 1÷3584 of CLKM frequency. */
	SPI_Response = SPI_TXRX(hspi, WRITE_FM, 0x31);

/* configuration of FEN2 register - ILIM and ISN open pin fault for CH1 and CH2 */
	SPI_Response = SPI_TXRX(hspi, WRITE_FEN2, 0x0F);

/* read FLATEN register*/
//	SPI_Response = SPI_TXRX(hspi, READ_FLATEN, EMPTY_DATA);

/* set PWM width; 10bit value! */
/* write first to PWMH register; transfer to the CHxPWM counter only upon the write to the CHxPWML register */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1PWMH, 0x03);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1PWML, 0xFF);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2PWMH, 0x03);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2PWML, 0xFF);

/* set EN bit*/
/*Read EN*/
	SPI_Response = SPI_TXRX(hspi, READ_EN, EMPTY_DATA);
/*set only the CH1EN, all other stay the same*/
	SPI_Response |= (1UL << 1);
/*set only the CH1EN, all other stay the same*/
	SPI_Response |= (1UL << 0);
/*write the whole EN*/
	SPI_Response = SPI_TXRX(hspi, WRITE_EN, (uint8_t)SPI_Response);

Read_FLTx(hspi);

return LED_DRV_OK;
}

/*Setup LED current*/
LED_DRV_status_t Set_Current(SPI_HandleTypeDef *hspi, uint8_t SetCurrent)
{
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1IADJ, SetCurrent);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2IADJ, SetCurrent);

	/*read faults*/
	Read_FLTx(hspi);

	return LED_DRV_OK;
}


/*Setup PWM duty cycle, 10bit value!*/
LED_DRV_status_t Set_PWM(SPI_HandleTypeDef *hspi, uint16_t SetPWM)
{
	/*define registers*/
	uint8_t	PWMH = 0;
	uint8_t	PWML = 0;

	/*split the 10bit SetPWM register to PWML and PWMH*/
	PWML = (uint8_t)SetPWM;
	SetPWM = SetPWM >> 8;
	PWMH = (uint8_t)SetPWM;

	/* important!! write first to PWMH register; transfer to the CHxPWM counter only upon the write to the CHxPWML register */
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1PWMH, PWMH);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH1PWML, PWML);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2PWMH, PWMH);
	SPI_Response = SPI_TXRX(hspi, WRITE_CH2PWML, PWML);

	/*read faults*/
	Read_FLTx(hspi);

	return LED_DRV_OK;
}


/*Read fault registers FLT1 and FLT2*/
LED_DRV_status_t Read_FLTx(SPI_HandleTypeDef *hspi)
{
	FLT1_Register = SPI_TXRX(hspi, READ_FLT1, EMPTY_DATA);
	FLT2_Register = SPI_TXRX(hspi, READ_FLT2, EMPTY_DATA);

	if(FLT1_Register != NO_FLT)
	{
		/*error handler is not finished yet*/
		return LED_DRV_NOK;
	}

	if(FLT2_Register != NO_FLT)
	{
		/*error handler is not finished yet*/
		return LED_DRV_NOK;
	}

	return LED_DRV_OK;
}
