#include "reg52.h"
#include "intrins.h"
#include "configuration.h"
#include "delay.h"
#include "time.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 90;
	j = 163;
	do
	{
		while (--j);
	} while (--i);
}

void Delay150ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay333ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 86;
	k = 9;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
