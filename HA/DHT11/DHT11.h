

#ifndef __DHT11_H__
#define __HDT11_H__

#include<reg51.h>
//DHT11���Ŷ���
sbit Temp_data=P3^5;


extern unsigned int rec_dat[4];
//unsigned char data_byte;
//unsigned char rec_dat_lcd=[4];
extern unsigned char rec_dat_lcd0[6];
extern unsigned char rec_dat_lcd1[6];
extern unsigned char rec_dat_lcd2[6];
extern unsigned char rec_dat_lcd3[6];


//����
void DHT11_delay_us(unsigned char n);
void DHT11_delay_ms(unsigned int z);
void DHT11_start(void);
unsigned char DHT11_rec_byte(void);
void DHT11_receive(void);

#endif