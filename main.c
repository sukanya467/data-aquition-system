#include<lpc21xx.h>
#include<string.h>
#include"header.h"
main()
{

  unsigned int temp=0,j,i=0,temp1,c=0,cel=0,per=0;//per1=0,temp1=0,cel2=0;
   char s[50],a[30],ch[10];
 unsigned  char sec,min,hour,date,day,month,year;
 float vtemp=0,cel1=0,vpot;
 uart_init(9600);
 i2c_init();
 adc_init();
 spi_init(); 
 lcd_init();
    i2c_write(0xD0,0x00,0x15);//sec
    i2c_write(0xD0,0x01,0x05);//min
    i2c_write(0xD0,0x02,0x67);//hour  in pm/am mode
	i2c_write(0xD0,0x03,0x06);//day
	i2c_write(0xD0,0x04,0x22); //date
	i2c_write(0xD0,0x05,0x03);//month
	i2c_write(0xD0,0x06,0x25);//year
  
 while(1)
 {
       i=0;
 	   lcd_cmd(0x01);
      sec=i2c_read(0xD1,0x00);
	  min=i2c_read(0xD1,0x01);
	 hour=i2c_read(0xD1,0x02);
	  day=i2c_read(0xD1,0x03);
	 date=i2c_read(0xD1,0x04);			
	month=i2c_read(0xD1,0x05);
	 year=i2c_read(0xD1,0x06);
  lcd_cmd(0xC0);
	  lcd_data(((hour&0x10)>>4)+48);
	  lcd_data((hour&0x0f)+48);
	  lcd_data(':');
	  lcd_data(((min&0xf0)>>4)+48);
	  lcd_data((min&0x0f)+48);
	  lcd_data(':');
	  lcd_data(((sec&0xf0)>>4)+48);
	  lcd_data((sec&0x0f)+48);
	  lcd_data(':');
	 
	  if(hour&(1<<5))
	  {
	  lcd_data('P');
	  lcd_data('M');
	  }
	  else
	  {
	  lcd_data('A');
	  lcd_data('M');
	  }
	  lcd_data(' ');
	 
	  s[6]=((sec&0xf0)>>4)+48;
	  s[7]=(sec&0x0f)+48;
	  s[2]=':';
	  s[3]=((min&0xf0)>>4)+48;
	  s[4]=(min&0x0f)+48;
	  s[5]=':';
	  s[0]=((hour&0x10)>>4)+48;
	  s[1]=(hour&0x0f)+48;
	  if(hour&(1<<5))
	  {
	  s[8]='P';
	  s[9]='M';
	  }
	  else
	  {
	  s[8]='A';
	  s[9]='M';
	  }
	  s[10]=' ';
	  s[11]=' ';
	  s[12]=' ';
	  s[13]=((date&0x30)>>4)+48;
	  s[14]=(date&0x0f)+48;
	  s[15]=':';
	  s[16]=((month&0x30)>>4)+48;
	  s[17]=(month&0x0f)+48;
	  s[18]=':';
	  s[19]='2';
	  s[20]='0';
      s[21]=((year&0xf0)>>4)+48;
   	  s[22]=(year&0x0f)+48;
	  s[23]=' ';
	  s[24]=' ';
	  switch(day&0XF)
	  {
	   case 1:
	   	{
	         s[25]='M';
			 lcd_data('M');
			 s[26]='O';
			 lcd_data('O');
			 s[27]='N';
			 lcd_data('N');
			 break;
		}
	   case 2:
	   {
	         s[25]='T';
			 lcd_data('T');
			 s[26]='U';
			 lcd_data('U');
			 s[27]='S';
			 lcd_data('S');
			 break;

		}
	   case 3:
	   {
	   		 s[25]='W';
			 lcd_data('W');
			 s[26]='E';
			 lcd_data('E');
			 s[27]='N';
			 lcd_data('N');
			 break;
		}
	   case 4:
	   {
	   		 s[25]='T';
			 lcd_data('T');
			 s[26]='H';
			 lcd_data('H');
			 s[27]='R';
			 lcd_data('R');break;
	   }
	   case 5:
	   {
	         s[25]='F';
			 lcd_data('F');
			 s[26]='R';
			 lcd_data('R');
			 s[27]='I';
			 lcd_data('I');		 break;
	   	}
	   case 6:
	   {
	         s[25]='S';
			 lcd_data('S');
			 s[26]='A';
			 lcd_data('A');
			 s[27]='T';
			 lcd_data('T');     
			 break;
	   }
	   case	7:
	   {  
			 s[25]='S';
			 lcd_data('S');
			 s[26]='U';
			 lcd_data('U');
			 s[27]='N';
			 lcd_data('N');
			 break;
	  	}
	}
	s[28]=' ';
	s[29]='\0';
  lcd_cmd(0x80);
  temp=adc_3204(2);
  uart_str("  ");
  per=100-((temp*100)/4095);
  a[i++]='L';
  lcd_data('L');
  a[i++]=':';
  lcd_data(':');
  
  j=1;
  while(per)
  {
  ch[j++]=per%10+48;
  per/=10;
  } 
  j--;
  while(j)
  {
   a[i]=ch[j];
   lcd_data(a[i]);
   i++;
   j--;
  }
  lcd_data('%');
  a[i++]='%';
  a[i++]=' ';
  a[i++]='T';
  lcd_data('T'); 
  lcd_data(':');
  temp=adc_read(1);
  vtemp=(temp*3.3)/1023;
  cel1=(vtemp-0.5)/0.01;
  cel=cel1;
   j=1;
  while(cel)
  {
   ch[j++]=cel%10+48;
   cel/=10;
  }
  j--;
  while(j)
  {
   a[i]=ch[j];
   lcd_data(a[i]);
   j--;
   i++;
  }
  a[i++]=' ';
  a[i++]='P';
  lcd_data(' ');
  lcd_data('P');
  lcd_data(':'); 
  temp=adc_read(2);
  vpot=(temp*3.3)/1023;
  temp1=vpot*10;
  c=0;
  j=1;	
  if(vpot<1)
  {
  a[i++]='0';
  lcd_data('0');
  }
  while(temp1)
  {
   ch[j++]=(temp1%10)+48;
   temp1/=10;
  }
  j--;
	while(j)
	{
	if(vpot<1)
	{
	lcd_data('.');
	a[i++]='.';
	}
	if(c==1)
	{
    lcd_data('.');
	a[i++]='.';
	}
	else
	{
	a[i]=ch[j];
	lcd_data(a[i]);
	i++;
	j--;
	}
	c++;
	}
	temp=0;
	cel=0;
	cel1=0;
 
	a[i++]=' ';
 a[i++]='\0';
 
strcat(s,a);
 //uart_str(s);
 //uart_str("\r\n");
 uart_str(s);
 uart_str("\r\n");  
 delay_ms(1000); 
 }  
 }

