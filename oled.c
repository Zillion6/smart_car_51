#include "reg52.h"
#include "intrins.h"
#include "configuration.h"
#include "delay.h"
#include "time.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"
#include "Oledfont.h"

sbit scl = P1^1;
sbit sda = P1^3;

void IIC_start()
{
	scl = 1;
	sda = 0;
	_nop_();
	
	sda = 1;
	_nop_();
	
	sda = 0;
	_nop_();
	
	scl = 0;
}

void IIC_stop()
{
	scl = 0;
	sda = 0;
	_nop_();
	
	scl = 1;
	_nop_();
	
	sda = 1;
	_nop_();
	
	sda = 0;
}

char IIC_ack()
{
	char flag;
	
	scl = 0;
	sda = 1;
	
	scl = 1;
	_nop_();
	
	flag = sda;
	_nop_();
	scl = 0;
	_nop_();
	
	
	return flag;
}

void IIC_sendByte(char send_data)
{
	int i = 0;
	
	for(i = 0; i<8; i++)
	{
		scl = 0;	
		sda = send_data & 0x80;
		_nop_();
		
		scl = 1;
		_nop_();
		
		scl = 0;
		_nop_();
		
		send_data = send_data << 1;
	}
}

void Oled_Write_Cmd(char cmd)
{
	IIC_start();
	
	IIC_sendByte(0x78);
	
	IIC_ack();
	
	IIC_sendByte(0x00);
	
	IIC_ack();
	
	IIC_sendByte(cmd);
	
	IIC_ack();
	
	IIC_stop();
}

void Oled_Write_Data(char data1)
{
	IIC_start();
	
	IIC_sendByte(0x78);
	
	IIC_ack();
	
	IIC_sendByte(0x40);
	
	IIC_ack();
	
	IIC_sendByte(data1);
	
	IIC_ack();
	
	IIC_stop();
}

void Oled_Clear()
{
	unsigned char i,j; //-128 --- 127
	
	for(i=0;i<8;i++){
		Oled_Write_Cmd(0xB0 + i);//page0--page7
		//??page?0?
		Oled_Write_Cmd(0x00);
		Oled_Write_Cmd(0x10);
		//0?127?,????0,?????,???????
		for(j = 0;j<128;j++){
			Oled_Write_Data(0);
		}
	}
}

/******************************************************************************/
// ????:Oled_Show_Char 
// ????:oledChar 
// ????:? 
// ????:OLED??????
/******************************************************************************/
void Oled_Show_Str(char row,char col,char *str){
	while(*str!=0){
		Oled_Show_Char(row,col,*str);
		str++;
		col += 8;	
	}		
}

void Oled_Show_Char(char row,char col,char oledChar){ //row*2-2
	unsigned int  i;
	Oled_Write_Cmd(0xb0+(row*2-2));                           //page 0
	Oled_Write_Cmd(0x00+(col&0x0f));                          //low
	Oled_Write_Cmd(0x10+(col>>4));                            //high	
	for(i=((oledChar-32)*16);i<((oledChar-32)*16+8);i++){
		Oled_Write_Data(F8X16[i]);                            //???oledTable1
	}

	Oled_Write_Cmd(0xb0+(row*2-1));                           //page 1
	Oled_Write_Cmd(0x00+(col&0x0f));                          //low
	Oled_Write_Cmd(0x10+(col>>4));                            //high
	for(i=((oledChar-32)*16+8);i<((oledChar-32)*16+8+8);i++){
		Oled_Write_Data(F8X16[i]);                            //???oledTable1
	}		
}

void Oled_Init(void)
{
	Oled_Write_Cmd(0xAE);//--display off
	Oled_Write_Cmd(0x00);//---set low column address
	Oled_Write_Cmd(0x10);//---set high column address
	Oled_Write_Cmd(0x40);//--set start line address
	Oled_Write_Cmd(0xB0);//--set page address
	Oled_Write_Cmd(0x81); // contract control
	Oled_Write_Cmd(0xFF);//--128
	Oled_Write_Cmd(0xA1);//set segment remap
	Oled_Write_Cmd(0xA6);//--normal / reverse
	Oled_Write_Cmd(0xA8);//--set multiplex ratio(1 to 64)
	Oled_Write_Cmd(0x3F);//--1/32 duty
	Oled_Write_Cmd(0xC8);//Com scan direction
	Oled_Write_Cmd(0xD3);//-set display offset
	Oled_Write_Cmd(0x00);//
	Oled_Write_Cmd(0xD5);//set osc division
	Oled_Write_Cmd(0x80);//
	Oled_Write_Cmd(0xD8);//set area color mode off
	Oled_Write_Cmd(0x05);//
	Oled_Write_Cmd(0xD9);//Set Pre-Charge Period
	Oled_Write_Cmd(0xF1);//
	Oled_Write_Cmd(0xDA);//set com pin configuartion
	Oled_Write_Cmd(0x12);//
	Oled_Write_Cmd(0xDB);//set Vcomh
	Oled_Write_Cmd(0x30);//
	Oled_Write_Cmd(0x8D);//set charge pump enable
	Oled_Write_Cmd(0x14);//
	Oled_Write_Cmd(0xAF);//--turn on oled panel
}