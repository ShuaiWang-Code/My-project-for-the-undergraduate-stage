#include <hidef.h>      
#include "derivative.h"      
#include "PLL.h"
#include "NBCTFT.h"
#include "interface.h"
#include "pit.h"
#include "port.h"
#include "ad.h"
#include "ADfilter.h"
#include "pac.h"
#include "key.h"


unsigned int m_shang;
unsigned int m_xia;
unsigned int m_zuo;
unsigned int m_you;


unsigned int shuzi=0,shuzi1=0,shuzi2=0;

unsigned int n,jiexian = 45,aikesi,wayi;

unsigned int dw[290][4] = 0;
unsigned int shu=0,chus=0;

unsigned int sec,intr;
unsigned int Device_code;
int flag_ad,flag_shang,flag_xia,flag_zuo,flag_you;

unsigned int flag_model1,flag_model2,flag_model3,flag_model4,flag_model5,flag_model6;
unsigned int sum;
unsigned int qiedeng=0;

void caijidian()
{
       // if (sum == 0)
       // {
      //                     dw[0][0] = m_shang = ad_average1;
      //                      dw[0][1] = m_xia   = ad_average2;
      //                      dw[0][2] = m_zuo   = ad_average3;
      //                      dw[0][3] = m_you   = ad_average4; 
 
       // } 
       // else
      //  {
                            dw[sum][0] = ad_average1;
                            dw[sum][1] = ad_average2;
                            dw[sum][2] = ad_average3;
                            dw[sum][3] = ad_average4;    
   //     }
        
        
}

void maichong()
{
                n=PACNT;
  
                PACNT=0;
       
        
                if (50<n && n<1100)
                {
                        if (50<n && n<150)
                        {
                                shuzi = 1;
                                
                        }
                        
                        if (150<n && n<250)
                        {
                                shuzi = 2;
                                
                        }
                        
                        if (250<n && n<350)
                        {
                                shuzi = 3;
                                
                        }
                        
                        if (350<n && n<450)
                        {
                                shuzi = 4;
                                
                        }
                        if (450<n && n<550)
                        {
                                shuzi = 5;
                                
                        }
                        if (550<n && n<650)
                        {
                                shuzi = 6;
                                
                        }
                        if (650<n && n<750)
                        {
                                shuzi = 7;
                                
                        }
                        if (750<n && n<850)
                        {
                                shuzi = 8;
                                
                        }
                        if (850<n && n<950)
                        {
                                shuzi = 9;
                                
                        }
                        if (950<n && n<1050)
                        {
                                shuzi = 0;
                                
                        }
                }
               
       
          if(shuzi!=chus) {
           shu++;
          chus=shuzi; 
          if(shu>3) shu=1;
           
         
         if(shu==1) {
          
         LCD_PutString(0,304,"LED1:   ",Black,Green);
          LCD_PutChar(40, 304, 0x30+shuzi%10, Black, Green);
         }
         
         if(shu==2) {
          
         LCD_PutString(72,304,"LED2:   ",Black,Green);
          LCD_PutChar(112, 304, 0x30+shuzi%10, Black, Green);
         }
         if(shu==3) {
          LCD_PutString(144,304,"LED3:   ",Black,Green);
          LCD_PutChar(184, 304, 0x30+shuzi%10, Black, Green);
         }
         }
                
                
                
}
 int ju_x=0,ju_y=0;
 char ju_xg=0,ju_xs=0,ju_yg=0,ju_ys=0;
void dingwei()
{
     uint i=0;     
          
          if (sum>=81)
          {
             
             for(i=0;i<81;i++) {
              
                if (ad_average1 < dw[i][0]+jiexian && ad_average1 > dw[i][0]-jiexian)
                        
                if (ad_average2 < dw[i][1]+jiexian && ad_average2 > dw[i][1]-jiexian)
                                
                if (ad_average3 < dw[i][2]+jiexian && ad_average3 > dw[i][2]-jiexian)
                                        
                if (ad_average4 < dw[i][3]+jiexian && ad_average4 > dw[i][3]-jiexian)
                {                                    
                            
                            aikesi = 216-4-(24*(i%9));
                            wayi =   248-8-(24*(i/9));
                            ju_x=40-(10*(i%9));
                            ju_y=-40+(10*(i/9));
                            if(ju_x<0)
                            {
                            ju_x=-ju_x;
                            ju_xg=ju_x%10+0x30;
                            ju_xs=ju_x/10+0x30;
                            LCD_PutChar(16,272,'-',Black,Green);
                            LCD_PutChar(24,272,ju_xs,Black,Green);
                            LCD_PutChar(32,272,ju_xg,Black,Green);
                            
                            } else {
                            ju_xg=ju_x%10+0x30;
                            ju_xs=ju_x/10+0x30;
                            LCD_PutChar(16,272,'+',Black,Green);
                            LCD_PutChar(24,272,ju_xs,Black,Green);
                            LCD_PutChar(32,272,ju_xg,Black,Green);
                            }
                             if(ju_y<0)
                            {
                            ju_y=-ju_y;
                            ju_yg=ju_y%10+0x30;
                            ju_ys=ju_y/10+0x30;
                            LCD_PutChar(16,288,'-',Black,Green);
                            LCD_PutChar(24,288,ju_ys,Black,Green);
                            LCD_PutChar(32,288,ju_yg,Black,Green);
                            
                            } else {
                            ju_yg=ju_y%10+0x30;
                            ju_ys=ju_y/10+0x30;
                            LCD_PutChar(16,288,'+',Black,Green);
                            LCD_PutChar(24,288,ju_ys,Black,Green);
                            LCD_PutChar(32,288,ju_yg,Black,Green);
                            }
                            
                     
                     

                }
                                               
                            
                                               
             }
                
      m_shang=dw[40][0]; 
      m_xia=dw[40][1];
      m_zuo=dw[40][2];
      m_you=dw[40][3]; 
                        
          }
}

void quyu()
{
                 if (ad_average1<m_shang)
                {
                      flag_shang = 1;
                }
                  
                if (ad_average1>m_shang && ad_average2<m_xia)
                {
                      flag_xia = 1;
                }
                
                if (flag_shang == 1)
                {
                        flag_shang = 0;
                        LCD_PutString(96,272,"横坐标区域:上",Black,Green);
                }
                if (flag_xia == 1)
                {
                        flag_xia = 0;
                        LCD_PutString(96,272,"横坐标区域:下",Black,Green);
                }
                 
                 if (ad_average3<m_zuo && ad_average4>m_you)
                {
                      flag_zuo = 1;
                }
                
                if (ad_average4<m_you && ad_average3>m_zuo )
                {
                      flag_you = 1;
                }
                  
                
                
                if (flag_zuo == 1)
                {
                        flag_zuo = 0;
                        LCD_PutString(96,288,"纵坐标区域:左",Black,Green);
                }
                if (flag_you == 1)
                {
                        flag_you = 0;
                        LCD_PutString(96,288,"纵坐标区域:右",Black,Green);
                }
}



void main(void) 
{

  
        PLL_init();
        PIT_Init();
        io_init();
        ATD_Init();
        Init_PAC();
        
        Device_code=0x9320;
        TFT_Initial();
        interface_init();
        key_independecce_init();
        LCD_PutString(0,272,"x:-20.0cm",Black,Green);//64
	      LCD_PutString(0,288,"y:-20.0cm",Black,Green);
	       LCD_PutString(0,304,"LED1:0  ",Black,Green);
	       LCD_PutString(72,304,"LED2:0  ",Black,Green);
         LCD_PutString(144,304,"LED3:0  ",Black,Green);
    	  EnableInterrupts;

        for(;;) 
        {
      
                  if (flag_ad == 1)
                  {
                        flag_ad = 0;
                        filter(ad_value1);
                        filter1(ad_value2);
                        filter2(ad_value3);
                        filter3(ad_value4);
                        //filter4(ad_value5);
                        caijidian();
                  }
                  key_independence_scan();
                  
                  if (flag_model1 == 1)
                  {
                        sum++;
                        flag_model1 = 0;
                       
                        //if (sum >= 5)
                        //{
                        //  sum = 5;     
                        //}
                  }
                  
                  if (flag_model2 == 1)
                  {
                        flag_model2 = 0;
                        sum--;
                  }
                  
                  if(flag_model3 == 1)
                 
                  {
                        flag_model3 = 0;
                        jiexian+=2;
                  }
                  if(flag_model4 == 1)
                 
                  {
                        flag_model4 = 0;
                        jiexian-=2;
                  }
                  if(flag_model5 == 1)
                 
                  {
                        flag_model5 = 0;
                        LCD_PutString(0,304,"LED1:0  ",Black,Green);
	       LCD_PutString(72,304,"LED2:0  ",Black,Green);
         LCD_PutString(144,304,"LED3:0  ",Black,Green);
                  shu=0;
                        
                  }
                
                  
                  
                                  
                _FEED_COP(); 
        } 
 
}
unsigned char last=0; unsigned int last_x,last_y;
#pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 66 PIT0(void)//定时器0 中断服务函数
{
        intr++;
        if(intr==1000)
        {        
                sec++;
                intr=0;

                
                quyu();
                maichong();
                LCD_PutChar(224, 272, 0x30+sum/10, Black, Green);
                LCD_PutChar(232, 272, 0x30+sum%10, Black, Green);
                LCD_PutChar(224, 288, 0x30+jiexian/10, Black, Green);
                LCD_PutChar(232, 288, 0x30+jiexian%10, Black, Green);
                
                LCD_PutChar(0, 256, 0x30+ad_average1/1000%10, Black, Green);
                LCD_PutChar(8, 256, 0x30+ad_average1/100%10, Black, Green);
                LCD_PutChar(16, 256, 0x30+ad_average1/10%10, Black, Green);
                LCD_PutChar(24, 256, 0x30+ad_average1%10, Black, Green);
                
                LCD_PutChar(64, 256, 0x30+ad_average2/1000%10, Black, Green);
                LCD_PutChar(72, 256, 0x30+ad_average2/100%10, Black, Green);
                LCD_PutChar(80, 256, 0x30+ad_average2/10%10, Black, Green);
                LCD_PutChar(88, 256, 0x30+ad_average2%10, Black, Green);
                
                LCD_PutChar(128, 256, 0x30+ad_average3/1000%10, Black, Green);
                LCD_PutChar(136, 256, 0x30+ad_average3/100%10, Black, Green);
                LCD_PutChar(144, 256, 0x30+ad_average3/10%10, Black, Green);
                LCD_PutChar(152, 256, 0x30+ad_average3%10, Black, Green);
                
                LCD_PutChar(192, 256, 0x30+ad_average4/1000%10, Black, Green);
                LCD_PutChar(200, 256, 0x30+ad_average4/100%10, Black, Green);
                LCD_PutChar(208, 256, 0x30+ad_average4/10%10, Black, Green);
                LCD_PutChar(216, 256, 0x30+ad_average4%10, Black, Green);
                
                
                
             
                
                dingwei();
                
                if(last_x!=aikesi || last_y!=wayi)  
                {     
                        LCD_PutString(last_x,last_y,"*",Green,Green);
                        LCD_PutString(aikesi,wayi,"*",Blue,Green); 
                        last_x=aikesi;
                        last_y=wayi;
                } 
                else
                {
                        LCD_PutString(aikesi,wayi,"*",Blue,Green); 
                }
                
                
                
                
             
                xiaodian();                
        }
        PITTF_PTF0=1;//清中断标志位
}

void interrupt 22 AD(void) 
{   
       ad_interrupt();
       flag_ad = 1;       
}
