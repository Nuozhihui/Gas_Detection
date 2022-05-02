
#ifndef __SIM_H__
#define __SIM_H__


//函数或者变量声明
extern void delay_ms(unsigned int n);
extern unsigned int sendCommand(char *Command, char *Response, unsigned long Timeout, unsigned char Retry);
extern void errorLog();
extern void soft_reset(void);
extern void phone(char *number);
extern void sendMessage(char *number,char *msg);
void SIM_Iint(void);
#endif