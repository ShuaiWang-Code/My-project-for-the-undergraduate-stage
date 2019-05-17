#include <reg52.h>
#include "intrins.h"
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library

#define uint unsigned int  
#define uchar unsigned char 
//#define FOSC    11059200L  //晶振11.0592M
//#define BAUD    9600

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef bit BOOL  ; 

/*Declare SFR associated with the ADC */
sfr AUXR1       =   0XA2;
sfr ADC_CONTR   =   0xBC;           //ADC control register
sfr ADC_RES     =   0xBD;           //ADC high 8-bit result register
sfr ADC_RESL    =   0xBE;
sfr ADC_LOW2    =   0xBE;           //ADC low 2-bit result register
sfr P1ASF       =   0x9D;           //P1 secondary function control register

/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks 

sbit io = P2^0 ; 
sbit rs = P2^6 ;  
sbit rw = P2^5 ; 
sbit ep = P2^7 ; 

void InitUart();
void InitADC();
int GetADCResult(BYTE ch);
void Delay2(WORD n);

uchar ge,shi,bai,qian,wan;           //显示变量

void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
}

int GetADCResult(BYTE ch)
{   int AD10bitResult; 
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //Must wait before inquiry
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    AD10bitResult=ADC_RES;
    AD10bitResult<<=8;
    AD10bitResult|=ADC_RESL;
    return AD10bitResult;                  //Return 10BIT ADC result
}

void InitADC()
{
    P1ASF = 0xff;                   //Open 8 channels ADC function

	AUXR1=AUXR1|0X04;              //ad值左对齐
    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay2(2);                       //ADC power-on and delay
}

void Delay2(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

void delay(uchar ms) 
{      	
		uchar i ; 
  	  	while(ms--) 
		{ 
    		for(i=0;i<250;i++); 
  		} 
} 

//void delay1()//10us 
//{ 
//		 uchar i; 
//		 i--; 		
//		 i--; 		
//		 i--; 		
//		 i--; 		
//		 i--; 		
//		 i--; 
//} 

void longdelay(uchar s) //长延时 
{ 
		  while(s--) 
		  { 
		    delay(90) ; 
		  }  
} 

BOOL lcd_bz()//测试LCD忙碌状态 
{       
		  BOOL result ; 
		  rs = 0 ; 
		  rw = 1 ; 
		  ep = 1 ; 
		  result = (BOOL)(P0 & 0x80) ; 
		  ep = 0 ; 
		  return result ;  
} 

 

void write_cmd(uchar cmd)// xie
{        
		 while(lcd_bz()) ; 		
		 rs = 0 ; 		
		 rw = 0 ; 		
		 ep = 0 ; 		
		 P0 = cmd ; 		
		 ep = 1 ; 		
		 ep = 0 ;   
}

void write_addr(uchar addr)//address 
{        
  		write_cmd(addr|0x80) ; 
} 

void write_byte(uchar dat)//dat
{       

  		while(lcd_bz()) ; 
   		rs = 1 ; 
   		rw = 0 ; 
   		ep = 0 ; 
   		P0 = dat ; 
   		ep = 1 ; 
   		ep = 0 ;  
} 


void lcd_init() 	 //2
{        
		  write_cmd(0x38) ;  
		  delay(3); 
		  write_cmd(0x08) ;   
		  delay(3); 
		  write_cmd(0x01) ;  
		  delay(3); 
		  write_cmd(0x06) ; 
		  delay(3); 
		  write_cmd(0x0c) ;  
		  delay(3);
} 

 

void display(uchar addr, uchar q) 
{    

		  delay(15) ; 					   //10		
		  write_addr(addr) ; 		
		  write_byte(q) ; 		
		  longdelay(2) ; 				   //2
} 

/******************************************************************************

******************************* 

************************************************ DHT11测试模块

***********************************************/ 

 


void display_lcd1602()
{
		  
			
			display(0x40,'L');
			display(0x41,'i');
			display(0x42,'g');
			display(0x43,'h');
			display(0x44,'t');
			display(0x45,':');
		    display(0x46,wan);
		    display(0x47,qian);
		    display(0x48,bai);
		    display(0x49,shi);
		    display(0x4a,ge);
		    display(0x4b,'l');
		    display(0x4c,'x');
}


/******************************************************************************

**************************** 

*************************************************主函数

***************************************************/ 

void main() 
{  
		int x;
  	lcd_init();
	InitADC(); 
 	delay(20); 
 	while(1) 
 	{ 
                    //Init UART, use to show ADC result
                         //Init ADC sfr
		x=GetADCResult(0);
		conversion(x);
		display_lcd1602();
 	} 

}
