#include "lcd.h"
#include "STEP.h"
#include "KEY.h"
#include "Show.h"
#include "SIM800C.h"

extern void KEY_Scanf(void);




//���ó�ʼ��
void Pio_Iint()
{
	KEY_Inint();
	Show_iint();		//1902

	LcdShowStr(0,0,"SIM is loading..");     //��ʾ�ַ���
	SIM_Iint();
	
		Lcd1602_Write_Cmd(0x01);    //����  
	
	LcdShowStr(0,0,"GAS:");	//���»���
	
	LcdShowStr(0,1,"Temp:");	//���»���
}




//������
void main()
{
	Pio_Iint();
	P1=0xf1;	
	
	while(1)
	{
		KEY_Scanf();		//����ɨ��
		Show();
	}
	
	
}




