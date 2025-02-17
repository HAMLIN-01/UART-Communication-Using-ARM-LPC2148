#include<lpc213x.h>
#define Fpclk 15000000
#define BAUD_BPS 9600
void PLLConfig()
{
PLLCON=0X01;
PLLCFG=0X24;
PLLFEED=0XAA;
PLLFEED=0X55;
while(!(PLLSTAT&0X0400));
PLLCON=0X03;
PLLFEED=0XAA;
PLLFEED=0X55;
}
void UART_Init()
{
int baud16=Fpclk/(16*BAUD_BPS);
U0LCR=0X83;
U0DLL=baud16%256;
U0DLM=baud16/256;
U0LCR=0x03;
	
}
void UART_SendByte(unsigned char ch)
{
U0THR=ch;
	while(!(U0LSR&0x40));
	}
unsigned char UART0_getchar()
{
while(!(U0LSR&0x01));
	return U0RBR;	
}
void UART0_SendStr(unsigned char *str)
{
while(*str)
{
UART_SendByte(*str);
	str++;
}
}
int main()
{
PINSEL0=0x00000005;
	PLLConfig();
	UART_Init();
	UART0_SendStr("Hello World");
	while(1)
	{
	UART_SendByte(UART0_getchar());
	}
}


