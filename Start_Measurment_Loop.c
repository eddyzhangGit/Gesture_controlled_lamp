/*
*Function Name  :Start_Measurment
*Description    :
  This program is used to measure the Time differene between the
2 income pulses and toggole the switches.

*Input         :None
*Return        :None
*/
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c/spidev.h>
#include "Start_Measurment_Loop.h"
#include<bcm2835.h>

#define CTRL0_BOOT          0x10
#define CTRL0_INT           0x11
#define CTRL0_INT_CLEAR     0x12
#define DATA_L              0x13
#define DATA_H              0x14
#define INT_HIGH            0x15
#define INT_DATA_READY      0x16
#define I2C                 0x17
#define SPI                 0x18

int ON_OFF = 0;
int initilize()  //The functiuon is used to initialize sensors and set interrupts
{

	bcm2835_I2C_RegisterWrite(CTRL0_BOOT, 0x10); //pOWER ON
	bcm2835_I2C_RegisterWrite(CTRL0_INT, 0x04); //int triger at low 
	bcm2835_I2C_RegisterWrite(INT_HIGH, 0x50); //Set low threhold

}

void timeval_print(struct timeval *tv)                                                       //This timevel function is only used to measure the measurement rate
{
	char buffer[30];
	time_t curtime;

	printf("%ld.%06ld", tv->tv_sec, tv->tv_usec);
	curtime = tv->tv_sec;
	strftime(buffer, 30, "%m-%d-%Y  %T", localtime(&curtime));
	printf(" = %s.%06ld\n", buffer, tv->tv_usec);
}


void Start_sampling()
{

	while (1)                               //measurement loop
	{
		char distance[2];
		bcm2835_I2C_write(0x12, distance);
		printf("Distance is %d cm\n", (int)((distance[1] << 8 || distance[0])*0.072)); //2 byte value and apply sensitivity--->get distance
		delay(1000);
	}
}














void Start_Measurment()
{

	initilize();

	while (1)                               //measurement loop
	{
		bcm2835_gpio_read(GP24, &GP24_);    //continues polling the GPIO to check interrupt
		bcm2835_gpio_read(GP23, &GP23_);    //continues polling the GPIO to check interrupt
		if (GP24_ == 1 && GP23_ != 1)       //If sensor 1's interrupt trigger first --->right sweep motion
		{
			handle_right_motion();          //Clear interrupt and swtich light
		}
		else if (GP24_ != 1 && GP23_ == 1) //If sensor 0's interrupt trigger first --->left sweep motion
		{
			handle_left_motion();          //Clear interrupt and swtich light
		}
		printf("No motion detected\n");
	}  //End of the while loop
}

void handle_left_motion()
{
	bcm2835_I2C0_RegisterWrite(CTRL0_INT_CLEAR, 0x10);
	bcm2835_I2C1_RegisterWrite(CTRL0_INT_CLEAR, 0x10);//clear the interrupt

	if (ON_OFF == 1)
	{
		;                                  //do nothing the light is on
	}
	else{
		bcm2835_gpio_Write(GP25, 0);  //switch off the luight
	}

	printf("Left motion detected\n");
}

void handle_left_motion()
{

	bcm2835_I2C0_RegisterWrite(CTRL0_INT_CLEAR, 0x10);   //clear the interrupt sensor 0
	bcm2835_I2C1_RegisterWrite(CTRL0_INT_CLEAR, 0x10);  //clear the interrupt  sensor 1

	if (ON_OFF == 0)
	{
		; //doing nothing the light is on
	}
	else{
		bcm2835_gpio_Write(GP25, 0);  //switch off the luight
	}
	printf("Right motion detected\n");
}
