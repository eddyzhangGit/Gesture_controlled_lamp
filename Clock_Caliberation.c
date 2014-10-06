/*
*Function Name  :Clock_Caliberation
*Description    :
  The measurement is based on the very precise 32.768 kHz clock.
  TDC-GP21 generates start/stop pulses from the 32.768 kHz and measures this time interval with
  its TDC unit. The result is used to adjust the 4Mhz high speed clock

*Input         :None
*Return        :CLKHS_fre_corr_fact
*/
#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "Clock_Caliberation.h"

#define PIN_INT RPI_GPIO_P1_15
#define PIN_SSN RPI_GPIO_P1_11
#define PIN_RESET RPI_GPIO_P1_16
#define PIN_FAKE RPI_GPIO_P1_18

float clock_cal(void)

{

	bcm2835_gpio_write(PIN_SSN, LOW);
	uint8_t data232d = bcm2835_spi_transfer(0x70);                     //Init the gp21
	bcm2835_gpio_write(PIN_SSN, HIGH);

	bcm2835_gpio_write(PIN_SSN, LOW);
	uint8_t data232g = bcm2835_spi_transfer(0x03);                    //Start_Cal_Resonator trigger a caliberation measurement of 4Mhz clock
	bcm2835_gpio_write(PIN_SSN, HIGH);

	while (bcm2835_gpio_lev(PIN_INT))                                 //wati for the ossilator to start
	{
		;
	}

	bcm2835_gpio_write(PIN_SSN, LOW);
	char buf122 [] = { 0xB0, 0xff, 0xff, 0xff, 0xff, };               //Read out the Caliberation result from Result registor 0
	bcm2835_spi_transfern(buf122, 5);
	bcm2835_gpio_write(PIN_SSN, HIGH);


	float fra_cal = (buf122[3] << 8) | buf122[4];                    //convert the 32bit fixed point number into a float number
	float interg_cal = (buf122[1] << 8) | buf122[2];

	float CLKHS_fre_corr_fact = 1953.124 / (interg_cal + fra_cal / 65536);        //ANZ_PER_CALRES=3 DIV_CLKHS=0   488.281=488.281uS/250ns
	printf("\n correction factor for clock is = %1.4f\n", CLKHS_fre_corr_fact);   //print out the correction factor

    bcm2835_gpio_write(PIN_SSN, LOW);
	uint8_t data23d2g = bcm2835_spi_transfer(0x04);                //update caliberation raw data
	bcm2835_gpio_write(PIN_SSN, HIGH);

	while (bcm2835_gpio_lev(PIN_INT))   //wati for the interrupt
	{
		;
	}


	return CLKHS_fre_corr_fact;

}
