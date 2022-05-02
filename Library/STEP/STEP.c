#include "STEP.h"

unsigned char  code table[]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9};
unsigned char  code table1[]={0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1};

int a;
unsigned char k,i;

void delay(unsigned char z)
{
	unsigned char x,y;
	for(x=z;x>0;x--)
		for(y=120;y>0;y--);
}

void Go_Step()
{

		for(a=0;a<520;a++)
	{
			for(i=0;i<8;i++)
			{
				P1=table[i];
				
				delay(1);
				
			}
			
	}
	P1=0xf1;
}		

void Break_Step()
{
	for(a=0;a<520;a++)
	{
		for(i=0;i<8;i++)
		{
			P1=table1[i];

			delay(1);
		}
	
		P1=0xf1;
	}		


}