#ifndef __CONFIG_H__
#define __CONFIG_H__

sfr AUXR           				= 0x8E;

sbit Trig          				= P2^3;
sbit Echo          				= P2^2;
sbit sg90_Steering 				= P1^0;

sbit Right_Con_A   				= P3^7;
sbit Right_Con_B   				= P3^3;
sbit Left_Con_A    				= P3^4;
sbit Left_Con_B    				= P3^5;

sbit track_Left_Sensor 		= P2^5;
sbit track_Right_Sensor 	= P2^4;

sbit follow_Left_Sensor 	= P2^7;
sbit follow_Right_Sensor 	= P2^6;

sbit A25           				= P1^5;
sbit A26           				= P1^6;
sbit A27           				= P1^7;

sbit speedIO      				= P3^2;
                                                                                                                                                                                                                                                                                 
sbit led2          		   	= P3^6;
sbit led1                 = P3^7;

#endif