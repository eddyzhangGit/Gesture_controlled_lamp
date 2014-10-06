#include <stdio.h>

#include <bcm2835.h>

int main(void)
{
	init_all();
	float CLKHS_fre_corr_fact = clock_cal();
	Start_Measurment(CLKHS_fre_corr_fact);

	bcm2835_I2C_end();
	bcm2835_close();
	return 0;
}
