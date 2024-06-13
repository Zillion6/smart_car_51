#include "reg52.h"
#include "configuration.h"
#include "intrins.h"
#include "string.h"
#include "delay.h"
#include "motor.h"
#include "uart.h"
#include "time.h"

char cmd[12] = {'\0'};


void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//??????
	SCON  = 0x50;		//8???,?????
	AUXR &= 0xBF;		//???1???Fosc/12,?12T
	AUXR &= 0xFE;		//??1?????1???????
	TMOD &= 0x0F;		//?????1???
	TMOD |= 0x20;		//?????1?8???????
	TL1 = 0xFD;		//??????
	TH1 = 0xFD;		//????????
	ET1 = 0;		//?????1??
	TR1 = 1;		//?????1
}

void my_UartInit()
{
	SCON = 0x50;//0100 0000          0111 1111        01xx xxxx
	PCON &= 0x7F;//                   0111 1111
 	AUXR |= 0x01;//                       0000 0001
	TMOD &= 0x0F;//                1100 1111         xx10 xxxx
	TMOD |= 0x20;//                  0010 0000
	TH1 = 0xFD;					//		smod = 0					 9600 = (2^smod) / 32 x 11059200 / 12/(256 - THL)
	TH1 = 0xFD;						//               THL = 253 = FD(HEX)
	ET1 = 0;
	TR1 = 1;
	ES  = 1;
	EA  = 1;
}

void sendByte(char msg_data)
{
	SBUF = msg_data;
	
	while(TI == 0);//??TI=1,TI==0??
	TI = 0;
}

void sendString(char *str)
{
	while(*str != '\0')
	{
		sendByte(*str);
		str++;
	}
}

void UartHandler() interrupt 4
{
	static int i = 0;
	char tmp;
	
	if(RI)
	{	
		RI = 0;
		
		tmp = SBUF;
		if(tmp == 'M')
		{
			i = 0;
		}
		cmd[i] = tmp;
		i++;
		
		if(cmd[0] == 'M')
		{
			switch(cmd[1])
			{
				case '1':
					go_Forward();
					Delay10ms();	
				break;
				case '2':
					go_Backward();
					Delay10ms();
				break;
				case '3':
					go_Left();
					Delay10ms();
				break;
				case '4':
					go_Right();
					Delay10ms();
				break;
				case '5':
					stop();
				break;
			}
		}
		if(i == 12)
		{
			memset(cmd, '\0', 12);
			i = 0;
		}
	}
}