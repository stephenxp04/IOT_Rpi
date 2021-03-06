#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//PCF8574 start addr
#define AF_BASE 64
#define AF_RS (AF_BASE+0)
#define AF_RW (AF_BASE+1)
#define AF_E (AF_BASE+2)
#define AF_LED (AF_BASE+3)
#define AF_DB4 (AF_BASE+4)
#define AF_DB5 (AF_BASE+5)
#define AF_DB6 (AF_BASE+6)
#define AF_DB7 (AF_BASE+7)

//global lcd handle
static int lcdHandle;

int main(void)
{
	int i;
	wiringPiSetup(); //Initialise wiringPi
	pcf8574Setup(AF_BASE, 0x3F);
	lcdHandle = lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0, 0, 0, 0);
	if(lcdHandle<0)
	{
		fprintf(stderr, "lcdInit failed\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<8;i++)
	pinMode(AF_BASE+i, OUTPUT); //will expand to IO port as the output mode
	digitalWrite(AF_LED, 1); //open back light
	digitalWrite(AF_RW, 0); //set the R/Wall to low, LCD write state
	lcdClear(lcdHandle); //clear display
	lcdPosition(lcdHandle, 0, 0); //Position cursor on the first line in the first column
	lcdPuts(lcdHandle, "Welcome to"); //print the text on the LCD at the current cursor position
	lcdPosition(lcdHandle, 8, 1);
	lcdPuts(lcdHandle, "M360");
	return 0;
}
