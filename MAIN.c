#include "lcd.h"
#include "STEP.h"
#include "KEY.h"
#include "Show.h"
#include "SIM800C.h"

extern void KEY_Scanf(void);




//配置初始化
void Pio_Iint()
{
	KEY_Inint();
	Show_iint();		//1902

	LcdShowStr(0,0,"SIM is loading..");     //显示字符串
	SIM_Iint();
	
		Lcd1602_Write_Cmd(0x01);    //清屏  
	
	LcdShowStr(0,0,"GAS:");	//更新画面
	
	LcdShowStr(0,1,"Temp:");	//更新画面
}




//主函数
void main()
{
	Pio_Iint();
	P1=0xf1;	
	
	while(1)
	{
		KEY_Scanf();		//按键扫描
		Show();
	}
	
	
}




