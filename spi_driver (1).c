#include<lpc21xx.h>
#include"header.h"
  
void spi_init(void)
{
 PINSEL0|=0X1500;
 IODIR0|=1<<7;
 IOSET0=1<<7;
 S0SPCR=0X20;//MASTER MODE  MODE 0
 S0SPCCR=15;
}
unsigned char  spi_read(unsigned char data)
{
  S0SPDR=data;
  while(((S0SPSR>>7)&1)==0);
   return S0SPDR;
}

unsigned int adc_3204(unsigned int ch_num)
{
 int res;
 unsigned char bh,bl;
 ch_num<<=6;
 IOCLR0|=1<<7;
 spi_read(0x06);
 bh=spi_read(ch_num);
 bl=spi_read(0x00);
IOSET0|=1<<7;
 bh=bh&0x0f;
 res=(bh<<8)|bl;
 return res;
}

