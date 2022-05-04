

#include "MAX6675.h"
#define uchar unsigned char
#define uint  unsigned int

sbit  SO  = P2^4;  				//P3.6����SO����
sbit  SCK = P2^2; 				//P3.4����SCK����
sbit  CS  = P2^3;  				//P3.5����CS����


const unsigned char DevID = 1;		//�����豸ID
unsigned char buffer;			//���ڽ��ջ�����
unsigned char rcv_buffer[20];
unsigned char send_buffer[20];
unsigned char flag_ok = 0;		//������ϵı�ʶ
unsigned int MAX6675_Temp;
unsigned char Flag_connect;
unsigned char CRCH,CRCL;
unsigned char wd[2];	  		//wd[]��BCD����¶�
unsigned char flag_dis;			//��ʾˢ�µı�ʶ

unsigned int MAX6675_ReadReg(void)
{ 
	unsigned char i;   
	unsigned int dat;
	 
	i   = 0;   
	dat = 0;   
	
	CS  = 0; 
	SCK = 0;     
	
	for(i=0; i<16; i++)		//get D15-D0 from 6675  
	{      
		SCK = 1;     
		dat = dat<<1;    
		if( SO==1 )   
			dat = dat|0x01;   
		SCK = 0;    
	} 
	CS = 1;   
	  
	return dat;   
}  
/*
* ��  �ܣ���ʱ�����ɺ���
* ��  ����������
* ����ֵ����
*/
void DelayMs(unsigned int i)	//һ����ʱ���������������11.0592M�����µ���ʱʱ����Ϊ1ms
{
	unsigned int j,k;

	for(j=i; j>0; j--)
		for(k=114; k>0; k--);
}

int REDE_MAX6675()
{
	unsigned char cnt = 11;
	unsigned int t;


		t=MAX6675_ReadReg();

  		Flag_connect=t&0x04;		 	//�������ݵ�D2λ���ȵ�ż���߱�־λ����λΪ1��ʾ���ߣ���λΪ0��ʾ����
  		Flag_connect=Flag_connect>>2; 	//MAX6675�Ƿ�����

		t = t<<1;					   	//�����������ݵ�D3~D14���¶�ֵ
		t = t>>4;
		MAX6675_Temp = t/4;				//��õ��¶ȵ�λ��0.25������Ҫ����0.25��������4�����ܵõ��Զ�Ϊ��λ���¶�ֵ
		
//		for(t=0; t<200; t++)			//��ʾ�¶�
//		{  
//			Display(MAX6675_Temp);
//		}

	return MAX6675_Temp;
	
}
 