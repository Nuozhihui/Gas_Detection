#include "lcd.h"
#include "STEP.h"
#include "KEY.h"
#include "Show.h"
#include "HDT11.h"
extern void KEY_Scanf(void);




//配置初始化
void Pio_Iint()
{
	KEY_Inint();
	Show_iint();		//1902
	
}




//主函数
void main()
{
	Pio_Iint();
	P1=0xf1;	
	
	while(1)
	{
		KEY_Scanf();		//按键扫描
		gx_date();
	}
	
	
}




