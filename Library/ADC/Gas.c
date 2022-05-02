
#include "REG52.h"
#include <intrins.h>

#define AD_CH0 0x94
#define AD_CH1 0xd4
#define AD_CH2 0xa4
#define AD_CH3 0xe4 
//ͨ��0����cmd��0x94  ͨ��1����cmd��0xd4  ͨ��2��λ��cmd��0xa4 ͨ��3�ⲿ����AIN3 cmd��0xe4

sbit CS = P3^7;
sbit DCLK = P2^1;
sbit DIN = 	P2^0;
sbit DOUT = P2^5;

/*====================================
ʹ��typedef��������������ȡ����
====================================*/
typedef unsigned char INT8U;
typedef unsigned char uchar;
typedef unsigned char u8;

typedef unsigned int INT16U;
typedef unsigned int uint;
typedef unsigned int u16;

/*====================================
����	��SPI_Write(uchar DAT)
����	��DAT��Ҫ���͵�����
����ֵ	����
����	������һ���ֽ�����
====================================*/
void SPI_Write(uchar DAT)
{
	uchar i; 
	for(i=0; i<8; i++) //�ֱ�д8�Σ�ÿ��д1λ
	{
		DCLK = 0;//����ʱ�����ߣ�����DIN�仯
		if(DAT & 0x80)//��д�������λ
			DIN = 1;  //д1
		else
			DIN = 0;  //д0
		DCLK = 1;	  //����ʱ�ӣ��ôӻ���DIN
		DAT <<= 1;	  //Ϊ������һλ����1λ
	}
}
/*====================================
����	��ReadByte()
����	����
����ֵ	�����ض���������
����	��
====================================*/
uint SPI_Read()
{
	uchar i; 
	uint DAT;
	for(i=0; i<12; i++)//�ֱ��12�Σ�ÿ�ζ�һλ
	{
		DAT <<= 1; //��������1λ��׼������һλ
		DCLK = 1;   //����ʱ�����ߣ���ȡSDA�ϵ�����
		DCLK = 0;   //����ʱ�����ߣ�����ӻ�����SDA�仯
		if(DOUT)
			DAT |= 0X01;//Ϊ1��д1��������ִ��д1��ͨ�����Ʋ�0
	}
	return(DAT); //���ض���������
}

/*====================================
����	��PCF8591Read(uchar cmd)
����	��cmd XPT2046�����ֽ�
����ֵ	��ADת����������
����	����ָ��ͨ���������ģ����רΪ������
====================================*/
uint ReadAD(uchar cmd)
{
	uint DAT;
	CS = 0;
	SPI_Write(cmd);
	DCLK = 0;   //����ʱ������
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DAT = SPI_Read();
	CS = 1;
	return(DAT);//���ض�������
			
}