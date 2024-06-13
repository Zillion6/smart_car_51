#include "reg52.h"
#include "intrins.h"
#include "configuration.h"
#include "delay.h"
#include "time.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"

extern int sg90_angle      ;
extern int cnt             ;

void Bo_init()
{
	Trig = 0;
	Trig = 1;
	Delay10us();
	Trig = 0;
}

void sg90_180_left()
{
	sg90_angle = 5;
}

void sg90_90_middle()
{
		sg90_angle = 3;
}

void sg90_0_right()
{
	sg90_angle = 1;
}


double getDis()
{
		double dis;
		double time;
		
		TH1 = 0;
		TL1 = 0;
	
		Bo_init();
		
		while(Echo == 0);
		TR1 = 1;
		
		while(Echo == 1);
		TR1 = 0;
		
		time =( TH1 * 256 + TL1 )* 1.085;
		
		dis = time * 0.017;
	
		return dis;
}
