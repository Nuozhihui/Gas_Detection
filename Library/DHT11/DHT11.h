

#ifndef __DHT11_H__
#define __HDT11_H__

#include<reg51.h>
//DHT11���Ŷ���
sbit Temp_data=P1^4;


void gx_date(void);

//����
void DHT11_delay_us(unsigned char n);
void DHT11_delay_ms(unsigned int z);
void DHT11_start(void);
unsigned char DHT11_rec_byte(void);
void DHT11_receive(void);

#endif