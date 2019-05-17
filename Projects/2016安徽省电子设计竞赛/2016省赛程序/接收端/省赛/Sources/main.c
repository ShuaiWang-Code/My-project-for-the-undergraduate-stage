#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "PLL.H"
#include "PIT.H"
#include "PAC.H"
#include "tim.h"
#include "port.h"
#include "key.h"
#include "interface.h"
#include "NBCTFT.H"
#include "ad.h"
//#include "picture.h"



/*******************************************************/
unsigned int flag_model1,flag_model2,flag_model3,flag_model4,flag_pw;
unsigned int flag_maikuan,flag_model5,flag_model6;
unsigned int intr,sec,n,sine_hz,square_hz;
unsigned int flag0,flag1,flag2,flag3;

unsigned int intr1,sec1;                                   //time变量
unsigned int intr2,sec2;
unsigned int intrM,secM;
unsigned int intrP,secP; 
unsigned int picture_sum;
unsigned int n,cn0,cn1;
unsigned int i,x;
unsigned int n1,cn01,cn11,square_pw;                                 //pw
float kong,shicha,shicha1;


unsigned char table[]={0,0,1,0,1,0,1,1,1,0,1,0,1,1,0,1};
unsigned int k=0;

unsigned int Device_code;

//extern unsigned char gImage1[506];
/********************子函数****************************/
void  time_generate()
{
        intr++;
        if(intr==1000)
        {
            intr=0;
            sec++;
            
            /*if(flag_model3==1)
            {
                    picture_sum=PACNT;
                    PACNT=0;
            }*/
            
            if(sec==999)
            {
                sec=0;
            }
            LCD_PutChar(94,300,0x30+sec/100, Black, Yellow);
            LCD_PutChar(102,300,0x30+sec%100/10, Black, Yellow);
            LCD_PutChar(110,300,0x30+sec%10, Black, Yellow);
            LCD_PutString(118,300,"s", Black,Yellow);   
        }
        
}

void time_m()
{
        intrM++;
        if(flag_model4==1)
        {
        intrP++;
        }
        if(intrM==1000)
        {
            intrM=0;
            secM++;
            if(flag_model3==1)
            {
                    picture_sum=PACNT;
                    PACNT=0;  
            }
            
        }
        if(intrP==1000)
        {
                intrP=0;
                //secP++;
                if(flag_model4==1)
                {
                    if(x<1000)
                    {
                    secP++;
                    if(secP==1)
                    {
                    Put_picture1(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==2)
                    {
                    Put_picture2(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==3)
                    {
                    Put_picture3(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==4)
                    {
                    Put_picture4(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==5)
                    {
                    Put_picture5(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==6)
                    {
                    Put_picture6(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==7)
                    {
                    Put_picture7(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    if(secP==8)
                    {
                    Put_picture8(60,120,Black,White);
                    //gImage[i]=gImage1[i];
                    //i++;
                    }
                    }
                    //if(secP>)
                    
                }
        }
        
}

/**********************interface_show****************************/
void interface_show()
{
        while(flag0)
        {
                flag0=0;
                Show_RGB(0,240,0,320,Yellow);
                LCD_PutString(64,10,"可见光通信装置",Blue,Yellow);
                Put_zhengxianbo(Blue);
                LCD_PutString(64,230,"SINE-HZ:",Blue,Yellow);
                      
        }
        
        while(flag1)
        {
                flag1=0;
                Show_RGB(0,240,0,320,Yellow);
                LCD_PutString(64,10,"可见光通信装置",Blue,Yellow);
                Put_fangbo(5,Blue);
                LCD_PutString(48,220,"SQUARE-HZ:",Blue,Yellow);
                LCD_PutString(48,240,"SQUARE-PW:",Blue,Yellow);      
        }
        while(flag2)
        {       
                flag2=0;
                Show_RGB(0,240,0,320,Yellow);
                LCD_PutString(64,10,"可见光通信装置",Blue,Yellow);
        }
        while(flag3)
        {
                flag3=0;
                Show_RGB(0,240,0,320,White);
                LCD_PutString(64,10,"图片传输",Blue,White);
                LCD_PutString(20,120,"接收:",Blue,White);
                //LCD_PutString(20,220,"原图:",Blue,White);
                //Put_picture8(60,220,Black,White);       
        }
        
}

/*********************model_select***************************/
void model_select()
{
        if(flag_model1==1 && flag_model2==0 && flag_model3==0 && flag_model4==0)
        {
                
                intr1++;
                
                if(intr1==1000)
                {
                    intr1=0;
                    sec1++;
            
                    sine_hz=PACNT;
                    PACNT=0;
                    
                    LCD_PutChar(128,230,0x30+sine_hz/1000, Black, Yellow);
                    LCD_PutChar(136,230,0x30+sine_hz%1000/100, Black, Yellow);
                    LCD_PutChar(144,230,0x30+sine_hz%100/10, Black, Yellow);
                    LCD_PutChar(152,230,0x30+sine_hz%10, Black, Yellow);
                    LCD_PutString(160,230,"hz",Blue,Yellow);     
                }
        }
        
        if(flag_model1==0 && flag_model2==1 && flag_model3==0 && flag_model4==0)
        {
                
                intr2++;
                
                if(intr2==1000)
                {
                    intr2=0;
                    sec2++;
            
                    square_hz=PACNT;
                    PACNT=0;
                    LCD_PutChar(128,220,0x30+square_hz/1000, Black, Yellow);
                    LCD_PutChar(136,220,0x30+square_hz%1000/100, Black, Yellow);
                    LCD_PutChar(144,220,0x30+square_hz%100/10, Black, Yellow);
                    LCD_PutChar(152,220,0x30+square_hz%10, Black, Yellow);
                    LCD_PutString(160,220,"hz",Blue,Yellow); 
                    if(flag_maikuan==1)
                    {
                            TIE_C0I=1;      
                            TIE_C2I=1;
                            if(flag_pw==0)
                            {
                            kong=shicha/shicha1;
                            square_pw=1000*kong;
                            }
                            if(flag_pw==1)
                            {
                            kong=1-shicha/shicha1;
                            square_pw=1000*kong;   
                            }
                    }
                    if(flag_maikuan==0)
                    {       
                            TIE_C0I=0;      
                            TIE_C2I=0;
                            square_pw=500000/square_hz;
                            LCD_PutChar(128,240,0x30+square_pw/1000, Black, Yellow);
                            LCD_PutChar(136,240,0x30+square_pw%1000/100, Black, Yellow);
                            LCD_PutChar(144,240,0x30+square_pw%100/10, Black, Yellow);
                            LCD_PutChar(152,240,0x30+square_pw%10, Black, Yellow);
                            //LCD_PutChar(160,240,0x30+square_pw%10, Black, Yellow);
                            LCD_PutString(160,240,"us",Blue,Yellow); 
                            
                    }
                         
                }
        }
}



void main(void)
{
            /* put your own code here */
  
            PLL_init();
            PIT_Init();
            Init_PAC();
            Init_ECT0();
            ATD_Init(); 
            Init_PORT();
            io_init();
            Device_code=0x9328;
            TFT_Initial();
            key_independecce_init();
            interface_init();
        	EnableInterrupts;


            for(;;) 
            {
    
                    key_independence_scan();
                    interface_show();
                    //Put_picture(20,20,Black,White);
                    //delayms(30000);
    
    
                    _FEED_COP(); /* feeds the dog */
             }                   /* loop forever */
                                 /* please make sure that you never leave main */
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 22 AD(void) 
{   
        x=ATD0DR0;
        ATD0STAT0_SCF=1;   
}

void interrupt 66 PIT0(void)//定时器0 中断服务函数
{
        
        if(flag_model3==0 && flag_model4==0)
        {
                time_generate();
                model_select();
        }
        
        if(flag_model3==1 || flag_model4==1)
        {
                  k+=1;
                  PORTA_PA0=table[k];
                  if(k>20)
                  {
                    k=0;
                  }
                  time_m();
              
        }
        

        PITTF_PTF0=1;//清中断标志位
}

void interrupt 67 PIT1(void)//定时器1 中断服务函数
{
        if(flag_model3==1)
        {
                PORTA_PA1=~PORTA_PA1;
        }
        
        PITTF_PTF1=1;//清中断标志位
}

void interrupt 8 Timer0_Onput(void)
{
        EnableInterrupts;        
       
     
        n++;
     
        if(!(n%2)==0)
        {
                cn1=TCNT;
        }
         
        if(n%2==0)
        {
                cn0=TCNT;   
        }
        
        if(n==3)
        {  
                n=1;
        }
        
        if(cn0>cn1)
        {
                shicha=(cn0-cn1);
        }
         TFLG1_C0F=1;     
}

void interrupt 10 Timer2_Onput(void)
{
        EnableInterrupts;        
        
     
        n1++;
     
        if(!(n1%2)==0)
        {
                cn11=TCNT;
        } 
        
        if(n1%2==0)
        {
                cn01=TCNT;
        }
        
        if(n1==3)
        {  
                n1=1;
        }
        
        if(cn01>cn11)
        {
                shicha1=cn01-cn11;
        }
        
        TFLG1_C2F=1;    
} 


