#include "Show.h"
#include "lcd.h"
#include "dht11.h"
#include<intrins.h>
#include<stdio.h>
#include "Gas.h"
#include "SIM800C.h"
#include "MAX6675.h"
extern unsigned char key_switch_f;
extern unsigned char key_state;		//状态

//----------------DHT11数据变量区-------------------------------
unsigned int rec_dat[4];
unsigned char rec_dat_lcd0[6];
unsigned char rec_dat_lcd1[6];
unsigned char rec_dat_lcd2[6];
unsigned char rec_dat_lcd3[6];



sbit BEEP=P2^3;
//初始化
void Show_iint()
{
	
	InitLcd1602();						//初始化LCD
	LcdShowStr(0,0,"GAS:");	//更新画面
	
	LcdShowStr(0,1,"Temp:");	//更新画面
	
}

unsigned int Gas_val=0;
unsigned int MAX6675_val=0;
unsigned char Ignition_State=0;		//0:未升到指定温度		1:已到达指定温度	
unsigned char Note_State=0;		
//显示
void Show()
{
	
		Gas_val=gx_Gas();//热偶
		 MAX6675_val=REDE_MAX6675();	//热偶
		DHT11_delay_ms(20);
		DHT11_receive();

	
		//空气
		sprintf(rec_dat_lcd0,"%d",	Gas_val);

		DHT11_delay_ms(13);
		LcdShowStr(6,0,"           ");
		LcdShowStr(6,0,rec_dat_lcd0);

		
	
		//温度
		sprintf(rec_dat_lcd2,"%d",rec_dat[0]);
		sprintf(rec_dat_lcd3,"%d",rec_dat[1]);
		DHT11_delay_ms(13);
	
		//热偶
		sprintf(rec_dat_lcd1,"%d",MAX6675_val);

		LcdShowStr(12,0,rec_dat_lcd1);
		
		LcdShowStr(6,1,rec_dat_lcd2);
		LcdShowStr(8,1,".");
		LcdShowStr(9,1,rec_dat_lcd3);
		LcdShowStr(10,1," %");

		
		if(	Gas_val>150 || rec_dat[0]>80)
		{
			
			BEEP=0;
			
		}else{
			
			BEEP=1;
		}
		
		if(MAX6675_val>80)
		{
			Ignition_State=1;
			if(Note_State==0)
//			sendMessage(phoneNumber,msg);		//发送短信
			
				Note_State=1;
			}
			
			
	
		
			if(Ignition_State==1)
		{
			
			if(MAX6675_val<35)
			{
			key_state=2;
			key_switch_f =2;
			Ignition_State=0;
			
			}
			
		}
	
}
	