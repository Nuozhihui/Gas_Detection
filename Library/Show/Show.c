#include "Show.h"
#include "lcd.h"
#include "dht11.h"
#include<intrins.h>
#include<stdio.h>
#include "Gas.h"
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
//显示
void Show()
{
	
		Gas_val=gx_Gas();
	
		DHT11_delay_ms(20);
		DHT11_receive();

	
		//空气
		sprintf(rec_dat_lcd0,"%d",	Gas_val);

		DHT11_delay_ms(13);
		LcdShowStr(6,0,"        ");
		LcdShowStr(6,0,rec_dat_lcd0);


	
		//温度
		sprintf(rec_dat_lcd2,"%d",rec_dat[0]);
		sprintf(rec_dat_lcd3,"%d",rec_dat[1]);
		DHT11_delay_ms(13);
		


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
	
}