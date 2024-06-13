#include "reg52.h"
#include "intrins.h"
#include "configuration.h"
#include "delay.h"
#include "time.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"

void Left_Forward()
{
	Left_Con_A  = 0;
	Left_Con_B  = 1;
}

void Left_Backward()
{
	Left_Con_A  = 1;
	Left_Con_B  = 0;
}

void Left_stop()
{
	Left_Con_A  = 0;
	Left_Con_B  = 0;
}

void Right_Forward()
{
	Right_Con_A = 0;
	Right_Con_B = 1;
}

void Right_Backward()
{
	Right_Con_A = 1;
	Right_Con_B = 0;
}

void Right_stop()
{
	Right_Con_A = 0;
	Right_Con_B = 0;
}

void go_Forward()
{
	Left_Forward();
	Right_Forward();
}

void go_Backward()
{
	Left_Backward();
	Right_Backward();
}

void go_Right()
{
	Left_Forward();
	
	Right_stop();
}

void go_Left()
{
	Right_Forward();
	
	Left_stop();
}

void stop()
{
	Left_Con_A  = 0;
	Left_Con_B  = 0;
	
	Right_Con_A = 0;
	Right_Con_B = 0;
}
