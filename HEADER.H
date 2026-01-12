typedef unsigned char U8 ; 
typedef unsigned int U32;

extern void spi_init(void); 
extern unsigned char  spi_read(unsigned char data);
extern unsigned int adc_3204(unsigned int ch_num);
extern void uart_init(unsigned int rate);
extern void uart_tx(unsigned char p);
extern unsigned char uart_rx(void);
extern void uart_str(char*p);
extern void uart_integer(unsigned int p);
extern void uart_float(  float p);
extern void lcd_init(void);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_data(unsigned char data);
extern void delay_ms(unsigned int ms);
extern void adc_init(void);
extern unsigned int adc_read(unsigned int ch_num);
extern void i2c_init(void);
extern void i2c_write(unsigned char sa,unsigned char mr, unsigned char data);
extern unsigned char i2c_read(unsigned char sa,unsigned char mr);
extern void lcd_str(char *p);
extern void time_date(void);



