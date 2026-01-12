#include<lpc21xx.h>
#include"header.h"
void lcd_init(void)
{
 IODIR1|=0XFE<<16;
 lcd_cmd(0x03);
 lcd_cmd(0x02);
 lcd_cmd(0x28);
 lcd_cmd(0x0e);
 lcd_cmd(0x01);
}

void lcd_data(unsigned char data)
{
 IOCLR1=0XFE<<16;
 IOSET1=(0XF0&data)<<16;
 IOSET1=1<<17;
 IOCLR1=1<<18;
 IOSET1=1<<19;
 delay_ms(2);
 IOCLR1=1<<19;
  
 IOCLR1=0XFE<<16;
 IOSET1=(0X0F&data)<<20;
 IOSET1=1<<17;
 IOCLR1=1<<18;
 IOSET1=1<<19;
 delay_ms(2);
 IOCLR1=1<<19;
}

void lcd_cmd(unsigned char cmd)
{
 IOCLR1=0XFE<<16;
 IOSET1=(0XF0&cmd)<<16;
 IOCLR1=1<<17;
 IOCLR1=1<<18;
 IOSET1=1<<19;
 delay_ms(2);
 IOCLR1=1<<19;
  
 IOCLR1=0XFE<<16;
 IOSET1=(0X0F&cmd)<<20;
 IOCLR1=1<<17;
 IOCLR1=1<<18;
 IOSET1=1<<19;
 delay_ms(2);
 IOCLR1=1<<19;
}

void delay_ms(unsigned int ms)
{
 T0PC=0;
 T0PR=15000-1;
 T0TC=0;
 T0TCR=1;
 while(T0TC<ms);
 T0TCR=0;
}

void lcd_str(char *p)
{
while(*p)
{
 uart_tx(*p);
 p++;
 }
}




