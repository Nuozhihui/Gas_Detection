

#include "Show.h"
#include "lcd.h"


//��ʼ��
void Show_iint()
{
	
	InitLcd1602();						//��ʼ��LCD
	LcdShowStr(0,0,"GAS:");	//���»���
	
	LcdShowStr(0,1,"Temp:");	//���»���
	
}