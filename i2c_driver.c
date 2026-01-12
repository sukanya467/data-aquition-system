#include<lpc21xx.h>
#include"header.h"
void i2c_init(void)
{
PINSEL0|=0X50;
I2CONSET=1<<6;//I2EN=1,AA=0;
I2SCLL=I2SCLH=75;//100KBPS SPEED 
}
#define SI ((I2CONSET>>3)&1)
void i2c_write(U8 sa,U8 mr,U8 data )
{
//*1st star condition
I2CONSET=1<<5;
I2CONCLR=1<<3;//SI=0;
while(SI==0);
I2CONCLR=1<<5;

//*SLAVE ADDR
I2DAT=sa;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0X20)
{
 uart_str("slave addr + write mode tx but aclk is not recive \r\n");
 goto exit;	  
}

//* memoery address 
I2DAT=mr;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==30)
{
 uart_str("memory tx but aclk is not recive \r\n");
 goto exit;
}

//* data tx
I2DAT=data;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==58)
{
uart_str("data tx but aclk is not recive \r\n");
goto exit;
}

 exit:
//stop condition
I2CONSET=1<<4;
I2CONCLR=1<<3;
}

U8 i2c_read(U8 sa,U8 mr)
{
 U8 temp;
 //star condition 
 I2CONSET=1<<5;
 I2CONCLR=1<<3;
 while(SI==0);
 I2CONCLR=1<<5;

 //SALVE ADDRESS 
 I2DAT=sa&0XFE;
 I2CONCLR=1<<3;
 while(SI==0);
 if(I2STAT==20)
 {
  uart_str("slave address tx but aclk is not recive \r\n");
  goto exit;
 }

 //memory address tx 
 I2DAT=mr;
 I2CONCLR=1<<3;
 while(SI==0);
 if(I2STAT==30)
 {
  uart_str("memory address is tx but aclk is not recive \r\n");
  goto exit ;
 }

 //restart 
 I2CONSET=1<<5;
 I2CONCLR=1<<3;
 while(SI==0);
 I2CONCLR=1<<5;

 //SLAVE ADDRESS                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
 I2DAT=sa;
 I2CONCLR=1<<3;
 while(SI==0);
 if(I2STAT==20)
 {
  uart_str("salve address tx but aclk is not recive \r\n");
  goto exit;
 }

 //read data
 I2CONCLR=1<<3;
 while(SI==0);
 temp=I2DAT;
  
 //STOP CONDITION 
 exit:
 I2CONSET=1<<4;
 I2CONCLR=1<<3;	  
 return temp;
}

