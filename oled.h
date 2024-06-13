void IIC_start();

void IIC_stop();

char IIC_ack();

void IIC_sendByte(char send_data);

void Oled_Write_Cmd(char cmd);

void Oled_Write_Data(char data1);

void Oled_Clear();

void Oled_Show_Char(char row,char col,char oledChar);

void Oled_Show_Str(char row,char col,char *str);

void Oled_Init(void);