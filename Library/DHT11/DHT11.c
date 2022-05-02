#include<reg51.h>
#include<intrins.h>
#include<stdio.h>
#include<lcd.h>
#include "DHT11.h"



//----------------DHT11���ݱ�����-------------------------------
unsigned int rec_dat[4];
unsigned char rec_dat_lcd0[6];
unsigned char rec_dat_lcd1[6];
unsigned char rec_dat_lcd2[6];
unsigned char rec_dat_lcd3[6];

//DHT11��ʼ�ź�

void DHT11_start()	
{
	Temp_data=1;
	
	DHT11_delay_us(2);
	
	Temp_data=0;
	
	DHT11_delay_ms(20);
	
	Temp_data=1;
	
	DHT11_delay_us(13);
	

}

//����һ���ֽ�


unsigned char DHT11_rec_byte()
{
	
	unsigned char i,dat;

	
	for(i=0;i<8;i++)
	{
			while(!Temp_data);
		  DHT11_delay_us(8);
			dat<<=1;
			if(Temp_data==1)
			{
				dat+=1;
			}
			while(Temp_data);
	}

	return dat;

	
}


//������ʪ������
void DHT11_receive()
{
	
	unsigned int R_H,R_L,T_H,T_L;
	unsigned char RH,RL,TH,TL,revise;

	DHT11_start();
	Temp_data=1;
	if(Temp_data==0)
	{
		while(Temp_data==0);   //�ȴ�����     
        DHT11_delay_us(40);  //���ߺ���ʱ80us
		
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
	
        } 
      
        rec_dat[0]=RH;
        rec_dat[1]=RL;
//        rec_dat[2]=TH;
//        rec_dat[3]=TL;

	}
	
}

//��ʱus   --2*n+5us
void DHT11_delay_us(unsigned char n)
{
    while(--n);
}

//��ʱms
void DHT11_delay_ms(unsigned int z)
{
   unsigned int i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}


//DHT11 ���ݸ���
void gx_date()
{
		DHT11_delay_ms(20);
		DHT11_receive();


		//�¶�
		sprintf(rec_dat_lcd0,"%d",rec_dat[0]);
		sprintf(rec_dat_lcd1,"%d",rec_dat[1]);
		DHT11_delay_ms(13);
		
		LcdShowStr(6,1,rec_dat_lcd0);
		LcdShowStr(8,1,".");
		LcdShowStr(9,1,rec_dat_lcd1);
		LcdShowStr(10,1," %");
		
	
}