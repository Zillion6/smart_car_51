#include "reg52.h"
#include "intrins.h"
#include "configuration.h"
#include "delay.h"
#include "time.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"

#define MIDDLE       1
#define LEFT         2
#define RIGHT        3

#define TRACK        4
#define FOLLOW       6
#define AVOID        7

char position = 0;
	
double middle_dis = 0;
double left_dis   = 0;
double right_dis  = 0;

int mode_mark = 0;

void Avoid_mode()
{
		Delay50ms();
		
		if(position != MIDDLE)
		{
			sg90_90_middle();
			position = MIDDLE;
			Delay333ms();
		}
		middle_dis = getDis();
		
		if(middle_dis > 33)
		{
			go_Forward();
		}
		
		else if(middle_dis < 15)
		{
			go_Backward();
		}
		
		else
		{
			stop();
			
			sg90_180_left();
			position = LEFT;
			Delay333ms();
			left_dis = getDis();
			
			sg90_90_middle();
			position = MIDDLE;
			Delay333ms();
			
			sg90_0_right();
			position = RIGHT;
			Delay333ms();
			right_dis = getDis();
			
			if(left_dis > right_dis)
			{
				go_Left();
				Delay150ms();
				stop();
			}
			if(left_dis < right_dis)
			{
				go_Right();
				Delay150ms();
				stop();
			}
		}
}

void Track_mode()
{	
	if(track_Left_Sensor == 0 && track_Right_Sensor == 0)
	{
		go_Forward();
	}
	
	if(track_Left_Sensor == 1 && track_Right_Sensor == 0)
	{
		go_Right();
	}
	
	if(track_Left_Sensor == 0 && track_Right_Sensor == 1)
	{
		go_Left();
	}
	
	if(track_Left_Sensor == 1 && track_Right_Sensor == 1)
	{
		stop();
	}
}

void Follow_mode()
{
	if(follow_Left_Sensor == 0 && follow_Right_Sensor == 0)
	{
		go_Forward();
	}
	
	if(follow_Left_Sensor == 1 && follow_Right_Sensor == 0)
	{
		go_Right();
	}
	
	if(follow_Left_Sensor == 0 && follow_Right_Sensor == 1)
	{
		go_Left();
	}
	
	if(follow_Left_Sensor == 1 && follow_Right_Sensor == 1)
	{
		stop();
	}
}

void main()
{
	Timer0Init_500us();
	Timer1Init();
	//舵机的初始位置

	sg90_90_middle();
	Delay333ms();
	Delay333ms();
	position = MIDDLE;
	
	Oled_Init();
	Oled_Clear();
	Oled_Show_Str(2,1,"---Ready---");
	
	while(1)
	{
		if(A25 == 0 && A26 == 1 && A27 == 1)
		{
			if(mode_mark != TRACK)
			{
				Oled_Clear();
				Oled_Show_Str(2,1,"---Tracking---");
			}
			Track_mode();
			mode_mark = TRACK;
		}
		
		if(A26 == 0 && A25 == 1 && A27 == 1)
		{
			if(mode_mark != FOLLOW)
			{
				Oled_Clear();
				Oled_Show_Str(2,1,"---Following---");
			}
			Follow_mode();
			mode_mark = FOLLOW;
		}
		
		if(A27 == 0 && A25 == 1 && A26 == 1)
		{
			if(mode_mark != AVOID)
			{
				Oled_Clear();
				Oled_Show_Str(2,1,"---Avoiding---");
			}
			Avoid_mode();
			mode_mark = AVOID;
		}
	}
}
