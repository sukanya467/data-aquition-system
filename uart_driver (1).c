#include<lpc21xx.h>
#include"header.h"
void uart_init(unsigned int rate)
{
unsigned int res=15000000/(16*rate);
PINSEL0|=0X5;
U0LCR=0X83;
U0DLL=res&0XFF;
U0DLM=res>>8;
U0LCR=0X03;
}
unsigned char uart_rx(void)
{
 while((U0LSR&1)==0);
 return U0RBR;
}
 
void uart_tx(unsigned char data)
{
 U0THR=data;
 while(((U0LSR>>5)&1)==0);
}
void uart_str(char *p)
{
 while(*p)
 {
  uart_tx(*p);
  p++;
 }
}

 

void uart_integer(unsigned int p)
{
 char s[10];
 int i=0;
 while(p)
 {
  s[i++]=p%10+48;
  p/=10;
 }
 i--;
 while(i>=0)
 {
  uart_tx(s[i--]);
 }
 }


void uart_float( float p)
{
 int n=p*1000;
 int i=0;
 char s[10];
 while(n)
 {
 if(i==3)
 {
  s[i]='.';
 }
 else
 {
  s[i]=n%10+48;
  n/=10;
 }
  i++;
 }
 i--;
 while(i>=0)
 {
  uart_tx(s[i]);
  i--;
 }
}
	   