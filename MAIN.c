
#include "lcd.h"
#include<intrins.h>
#include<stdio.h>
#include "DHT11.h"
#include "Gas.h"
#include "STEP.h"

#define AD_CH0 0x94
#define AD_CH1 0xd4
#define AD_CH2 0xa4
#define AD_CH3 0xe4 


sbit KEY1=P3^2;
sbit KEY2=P3^3;	
sbit LED1=P1^7;
sbit BEEP=P2^3;
sbit Relay=P2^2;
//----------------DHT11���ݱ�����-------------------------------
unsigned int rec_dat[4];
unsigned char rec_dat_lcd0[6];
unsigned char rec_dat_lcd1[6];
unsigned char rec_dat_lcd2[6];
unsigned char rec_dat_lcd3[6];

unsigned char switch_f=0;
unsigned char key_switch_f=0;

void gx_date(void);		//��������

void delay1(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=120;y>0;y--);
}





void KEY_CL()
{
	if(key_switch_f ==1)
	{
		if(switch_f==0)
	{
	//��
	LED1=1;
	

		Go_Step();
		
		 Relay=1;
			delay1(1000);
		delay1(1000);
		delay1(1000);
		delay1(1000);
		delay1(1000);
		 Relay=0;
		
		switch_f=1;
		
		key_switch_f=0;
		

	
	

		
	}
}
	
	if(key_switch_f ==2)
	{
		if(switch_f==1)
{
	//��
	LED1=0;
	
	
	//��
	LED1=0;
	
		Break_Step();
		switch_f=0;
		while(!KEY2);
	
	
	
}
		
	}
	
}




void IINT_INT()
{
	  IT1 = 1;                        //set INT1 int type (1:Falling only 0:Low level)
    EX1 = 1;                        //enable INT1 interrupt

	  IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
    EA = 1;                         //open global interrupt switch
	
	
}
uint voltage;//��ѹֵ
//������
void main()
{
	

	InitLcd1602();						//��ʼ��LCD
	LcdShowStr(0,0,"GAS:");	//���»���
	
	LcdShowStr(0,1,"Temp:");	//���»���
	
	P1=0xf1;

	KEY1=1;
	KEY2=1;
	Relay=0;
	IINT_INT();
	while(1)
	{
		gx_date();
		KEY_CL();
		
		

	}
	
	
}




//MQ �� DHT11 ���ݸ���
void gx_date()
{
		DHT11_delay_ms(20);
		DHT11_receive();

		voltage = ReadAD(AD_CH3);	//ͨ��0����cmd��0x94  ͨ��1����cmd��0xd4  ͨ��2��λ��cmd��0xa4 ͨ��3�ⲿ����AIN3 cmd��0xe4
		voltage = (voltage * 1.2207) /10; //  ��5/4096��
		
	
	
		//����
		sprintf(rec_dat_lcd0,"%d",voltage);

		DHT11_delay_ms(13);
		LcdShowStr(6,0,rec_dat_lcd0);


	
		//�¶�
		sprintf(rec_dat_lcd2,"%d",rec_dat[0]);
		sprintf(rec_dat_lcd3,"%d",rec_dat[1]);
		DHT11_delay_ms(13);
		


		LcdShowStr(6,1,rec_dat_lcd2);
		LcdShowStr(8,1,".");
		LcdShowStr(9,1,rec_dat_lcd3);
		LcdShowStr(10,1," %");

		
		if(voltage>150 || rec_dat[0]>80)
		{
			 key_switch_f=2;
			BEEP=0;
			
		}else{
			
			BEEP=1;
		}
		
	
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
