#include "reg52.h"
#include "intrins.h"
#include "configuration.h"
#include "delay.h"
#include "time.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"

int cnt             = 0;
int sg90_angle      = 0;

void Timer1Init()		//0??@11.0592MHz
{
//	AUXR &= 0x7F;	 //?????12T??
	TMOD &= 0x0F;		 //???????
	TMOD |= 0x10;		 //???????
	TL1 = 0;		     //??????
	TH1 = 0;		     //??????
}

void Timer0Init_500us()		//0.5??@11.0592MHz
{
//	AUXR &= 0x7F;		//?????12T??
	TMOD &= 0xF0;		//???????
	TMOD |= 0x01;		//???????
	TL0 = 0x33;		
	TH0 = 0xFE;		
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	ET0 = 1;
	EA = 1;
}

void Timer0_Handler() interrupt 1
{
	cnt++;
	
	TL0 = 0x33;
	TH0 = 0xFE;
	
	if(cnt < sg90_angle)
	{
		sg90_Steering = 1;
	}
	else
	{
		sg90_Steering = 0;
	}
	
	if(cnt == 39)
	{
		sg90_Steering = 1;
		cnt = 0;
	}
}