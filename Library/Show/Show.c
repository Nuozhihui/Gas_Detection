

#include "Show.h"
#include "lcd.h"


//初始化
void Show_iint()
{
	
	InitLcd1602();						//初始化LCD
	LcdShowStr(0,0,"GAS:");	//更新画面
	
	LcdShowStr(0,1,"Temp:");	//更新画面
	
}