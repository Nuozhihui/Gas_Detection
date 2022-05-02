#include "KEY.h"
#include "STEP.h"


//变量
unsigned char key_switch_f=0;

//中断
void IINT_INT()
{
	  IT1 = 1;                        //set INT1 int type (1:Falling only 0:Low level)
    EX1 = 1;                        //enable INT1 interrupt

	  IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
    EA = 1;                         //open global interrupt switch
	
	
}
//初始化KEY

void KEY_Inint()
{
	
	IINT_INT();	//按键初始化
	
	
}


void exint0() interrupt 0           //(location at 0003H)
{
    key_switch_f=1;
}

//External interrupt1 service routine
void exint1() interrupt 2           //(location at 0013H)
{
    key_switch_f=2;
}
void KEY_Scanf()
{
	
	if( key_switch_f ==1)
	{
		Go_Step();
		 key_switch_f=0;
	}
		if( key_switch_f ==2)
	{
		Break_Step();
		 key_switch_f=0;
	}
	
}