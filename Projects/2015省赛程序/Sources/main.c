#include "main.h"
   unsigned   int i=0,j=0;
    unsigned int t1 ,j1,R=0,count=0,count2=0,count3=0,yuan_flag=1,yuan_flag1=1,shua_flag=0,shua_flag1=0,shua_flag2=0,shua_flag3=0,shua_flag4=0,shua_flag5=0,shua_flag6=0,shua_flag7=0;
    int jiaodu=0;  
 extern  unsigned int bee_flag;                          
    extern volatile unsigned int  result,result1;
extern volatile float GyrAccCraY ; //融合之后的角度 
extern volatile float GyrAccCraX ; //融合之后的角度 
extern volatile float Gyr_jiaoX;   //陀螺仪的角速度
extern volatile float Gyr_jiaoY;   //陀螺仪的角速度
  extern volatile char m; 
  
  extern int jisuan[3];
 float OUTX=0;  
 float P1X,D1X;  
 float OUTY=0;  
 float P1Y,D1Y;  
 float MID1=0;
  
  float rq=0,rh=0,rz=0,lq=0,lh=0,lz=0;
 extern volatile float ADValue1,ADValue2 ;
 float P2X,D2X;  
 float P2Y,D2Y;  
 float MID2=0;  
 float SDZ=0;  
 float JIAO=0,JIAOQ=0,JIAOH=0;    
   
  float SDZX=0;  
  float SDZY=0; 
 float JIAOX=0,JIAOQX=0,JIAOHX=0; 
  float JIAOY=0,JIAOQY=0,JIAOHY=0;    
  float rqX=0,rhX=0,rzX=0,lqX=0,lhX=0,lzX=0;
    float rqX1=0,rhX1=0,rzX1=0,lqX1=0,lhX1=0,lzX1=0;
    
   
   float rqY=0,rhY=0,rzY=0,lqY=0,lhY=0,lzY=0; 
    float rqY1=0,rhY1=0,rzY1=0,lqY1=0,lhY1=0,lzY1=0; 
   
 int ABS(int A) //求绝对值
 
 {
   if(A<0)
   A=-A;
   
   
   return A;
   
 }
 
 
 
   
    int delay11(int time) 
{
  for(t1=0;t1<time;t1++)
   for(j1=0;j1<64000;j1++) ;
}
   
 int delay111(int time) 
{
  for(t1=0;t1<time;t1++)
   for(j1=0;j1<6400;j1++) ;
}
 
   
   
   
void delay1(void) 
{
  for(t1=0;t1<140;t1++)
   for(j1=0;j1<64000;j1++) ;
}

 /********************************
函数名: delay_s
功能:   1 s  延时
*********************************/ 
void delay_s(int time)  
{
  for(i=0;i<time*1000;i++)
   for(j=0;j<64000;j++) ;
}
/********************************
函数名: delay_ms
功能:   1 ms  延时
*********************************/

void delay_ms(int time)                          
{
  for(i=0;i<time;i++)                         
   for(j=0;j<64000;j++) ;
}
void delay_1(int time)                          
{
  for(i=0;i<time;i++)                         
   for(j=0;j<64000;j++) ;
}
/********************************
函数名: delay_us
功能:   1 us  延时
*********************************/
void delay_us(int time) 
{
  for(i=0;i<time;i++)
   for(j=0;j<64;j++) ;
}

       
      
/***********************************************************************
** 函数名称: main
** 功能描述: 主函数             
** 说明: 
************************************************************************/  
void main(void)
{
     
  DisableInterrupts;
  
    ATD0_Init();
  Init_all();   //初始化所有函数
   Get_Gyr_OFFSET();
 	ILI9163B_display_full(BLACK);		//刷屏 
 	 LCD_bianliang(2,13, ADValue1,WHITE,BLACK) ;
 	 LCD_bianliang(2,14, ADValue2,WHITE,BLACK) ;
    
	      
	        
	       // delay_s(2);
	
  EnableInterrupts;
  
 
 
  for(;;)
  {  
       
	                   
    
	       P1X=10;//2;
	       D1X=40;//10;
	       P1Y=2;//2;
	       D1Y=10;//10;
                                             
 if(PTM_PTM0==0&&PTM_PTM1==0&&PTM_PTM2==0)     //模式0    直线  *******************

  {   
         int fm=0;
         if(shua_flag==0)
       	ILI9163B_display_full(BLACK);		//刷屏 
       	shua_flag=1;  
	    LCD_prints16(5,3,"Model 1",WHITE,BLACK);            
	     LCD_prints16(1,5," Straight line",WHITE,BLACK);        
	        // PWMDTY67=400;
	           
	     
	      
	           
	           
	                for(i=0;i<=5;i++)
	                
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                   
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                    delay1() ;
	                    
	                }
	                while(1)
	                
	                {
	              Get_ADresultY();
         DatehandleY();   
	        Get_ADresultX();
         DatehandleX();  
	             rq=GyrAccCraX;
	               rz= GyrAccCraX-rh;
	               rh=rq;
	               lq=GyrAccCraX;
	                 lz= GyrAccCraX-lh;
	                  lh=lq;
	               if(rz<=0&&lz<=0)
	               
	               {
	                   PWMDTY45=0;
	                   PWMDTY67=400;
	               }
	                  
	                  if(lz>=0&&rz>=0)
	                  
	                  {
	                    PWMDTY45=400;
	                    PWMDTY67=0;
	                    
	                  } 
	                  
	                  if( GyrAccCraX>50)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     delay1() ;
	                   
	                     
	                 }
	                  if( GyrAccCraX<-50)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     delay1() ;
	                    fm++; 
	                 }    
	               
	                if(fm==1)
	                bee_flag=0; //蜂鸣器  
	               
	                
	             }     
     
                   
	     
}  
  
  
    
 if(PTM_PTM0==0 && PTM_PTM1==0 && PTM_PTM2==1)  //模式1  线段 ******************

  {     int fm=0,fmb=0;
  
                 
	    
         set_data();
          if(shua_flag1==0)
       	ILI9163B_display_full(BLACK);		//刷屏 
       	shua_flag1=1; 
          LCD_prints16(5,2,"Model 2",WHITE,BLACK); 
       LCD_prints16(6,4,"Line",WHITE,BLACK);   
       LCD_prints16(3,6,"long:",WHITE,BLACK);  
       LCD_bianliang(9,13, result,WHITE,BLACK) ;
       LCD_prints16(11,6,"cm",WHITE,BLACK);
        
       SDZ=result/2; 
       
        
       if(m==13)
       
       {
            
              if(SDZ<22&&SDZ!=17)
              
              {
                
	                for(i=0;i<=(SDZ*2)/10-1;i++)
	               //  for(i=0;i<=SDZ/10-1;i++)
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                   
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                    delay1() ;
	                    
	                }  
              }
       
              if(SDZ==17) 
              {
              
              
              
              for(i=0;i<=(SDZ*2)/10;i++)
	               //  for(i=0;i<=SDZ/10-1;i++)
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                   
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                    delay1() ;
	                    
	                }  
              }
                
              
              if(SDZ>=22)
              
              {
                
	                for(i=0;i<=(SDZ*2)/10;i++)
	               //  for(i=0;i<=SDZ/10-1;i++)
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                   
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                    delay1() ;
	                    
	                }  
              }
	                while(1)
	                
	                {
	                    Get_ADresultY();
         DatehandleY();   
	        Get_ADresultX();
         DatehandleX();  
	             rq=GyrAccCraX;
	               rz= GyrAccCraX-rh;
	               rh=rq;
	               lq=GyrAccCraX;
	                 lz= GyrAccCraX-lh;
	                  lh=lq;
	                  
	       JIAO=atan(SDZ/90)*180/3.1415;
	       JIAOQ=atan((SDZ-1)/90)*180/3.1415;
	       JIAOH=atan((SDZ+1)/90)*180/3.1415;
	               if(rz<=0&&lz<=0)
	               
	               {
	                   PWMDTY45=0;
	                   PWMDTY67=400;
	               }
	                  
	                  if(lz>=0&&rz>=0)
	                  
	                  {
	                      PWMDTY45=400;
	                    PWMDTY67=0;
	                    
	                  } 
	                  
	                
                   
	                  if( GyrAccCraX>=JIAOQ-1+(float)(SDZ-15)/3) //(SDZ-15)/3
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     
	                  //    fm++;
	                     
	                    
	                     
	                 }
	                 
	                 if( GyrAccCraX<=-JIAOQ+1-(float)(SDZ-15)/3)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     fm++;
	                    
	                 }  
	               
	                   if(SDZ==22)
	                   
	                   {
	                        if(fm==19) 
	                  
	                    bee_flag=0; //蜂鸣器
	                   
	                   
	                   }
	                  if(SDZ!=22)
	                  
	                  {
	                    
	                  if(fm==13) 
	                  
	                    bee_flag=0; //蜂鸣器
	                 
	                  }
	              } 
	             
       }
	                
  } 

  
  
  if(PTM_PTM0==0&&PTM_PTM1==1&&PTM_PTM2==0)  //模式2  方向线段***************

{    
     set_data(); 
    
      if(shua_flag2==0)
       	ILI9163B_display_full(BLACK);		//刷屏 
       	shua_flag2=1;  
      LCD_prints16(5,2,"Model 3",WHITE,BLACK); 
     
     LCD_prints16(1,4,"direction:",WHITE,BLACK);
      
      if(jisuan[0]!=0)
     
     {
      jiaodu= result1;   
     LCD_bianliang(14, 9, result1 ,WHITE,BLACK) ;
     }
      if(jisuan[0]==0)
      
      {
        jiaodu= result; 
     LCD_bianliang(14, 9, result ,WHITE,BLACK) ;  
       
      }
      
    
    if(m==13)
    
    {   
          
           if(jiaodu==0)   // 225            
	                
	           {
               PWMDTY01=0;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=380;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=0;
	             PWMDTY45=380;
	             PWMDTY67=0;
	              delay1() ;
      
                count++ ;
                
                if(count>=2)
                bee_flag=0;
	           }
          
          
          
          if(jiaodu==10)   // 225            
	                
	           {
               PWMDTY01=300;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=375;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=300;
	             PWMDTY45=375;
	             PWMDTY67=0;
	              delay1() ;
      
                count++ ;
                
                if(count>=6)
                bee_flag=0;
	           }
            
          if(jiaodu==20)   // 225            
	                
	           {
                PWMDTY01=350;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=380;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=350;
	             PWMDTY45=380;
	             PWMDTY67=0;
	              delay1() ;
      
                count++ ;
                
                if(count>=7)
                bee_flag=0;
      
	           }
      
            if(jiaodu==30)   // 225            
	                
	           {
               PWMDTY01=359;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=370;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=359;
	             PWMDTY45=370;
	             PWMDTY67=0;
	              delay1() ;
	              
	              count++ ;
                
                if(count>=8)
                bee_flag=0;
      
      
	           }
      
             if(jiaodu==40)   // 225            
	                
	           {
               PWMDTY01=365;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=369;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=365;
	             PWMDTY45=369;
	             PWMDTY67=0;
	              delay1() ;
	              count++;
	              if(count>=10)
	              bee_flag=0;
      
	           }
      
             if(jiaodu==50)   // 225            
	                
	           {
               PWMDTY01=370;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=365;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=370;
	             PWMDTY45=365;
	             PWMDTY67=0;
	              delay1() ;
                 count++;
	              if(count>=7)
	              bee_flag=0;
      
	           }
      
       if(jiaodu==60)   // 225            
	                
	           {
               PWMDTY01=370;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=359;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=370;
	             PWMDTY45=359;
	             PWMDTY67=0;
	              delay1() ;
                  count++;
	              if(count>=9)
	              bee_flag=0;
	           }
	           
	         if(jiaodu==70)   // 225            
	                
	           {
               PWMDTY01=380;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=350;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=380;
	             PWMDTY45=350;
	             PWMDTY67=0;
	              delay1() ;
                 count++;
	              if(count>=9)
	              bee_flag=0;
	           }      
	           
	            if(jiaodu==80)   // 225            
	                
	           {
               PWMDTY01=375;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=300;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=375;
	             PWMDTY45=300;
	             PWMDTY67=0;
	              delay1() ;
                count++;
	              if(count>=3)
	              bee_flag=0;
	           }   
	           
	           
	             if(jiaodu==90)   // 225            
	                
	           {
               PWMDTY01=380;
	             PWMDTY23=0;
	             PWMDTY45=0;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=380;
	             PWMDTY45=0;
	             PWMDTY67=0;
	              delay1() ;
	              count++;
	              if(count>=2)
	              bee_flag=0;
	           }
	           
	           
	           
	           
	           
	           
	           
	      
	           
	           
	           if(jiaodu==170)   // 225            
	                
	           {
               PWMDTY01=340;
	             PWMDTY23=0;
	             PWMDTY45=370;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=340;
	             PWMDTY45=0;
	             PWMDTY67=370;
	              delay1() ;
	              count++;
	              if(count>=7)
	              bee_flag=0;
	           }
	           
	           if(jiaodu==160)   // 225            
	                
	           {
               PWMDTY01=360;
	             PWMDTY23=0;
	             PWMDTY45=370;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=360;
	             PWMDTY45=0;
	             PWMDTY67=370;
	              delay1() ;
	              count++;
	              if(count>=4)
	              bee_flag=0;
	           } 
	           
	            if(jiaodu==150)   // 225            
	                
	           {
               PWMDTY01=365;
	             PWMDTY23=0;
	             PWMDTY45=370;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=365;
	             PWMDTY45=0;
	             PWMDTY67=370;
	              delay1() ;
	              count++;
	              if(count>=4)
	              bee_flag=0;
	           } 
	           
	           if(jiaodu==140)   // 225            
	                
	           {
               PWMDTY01=375;
	             PWMDTY23=0;
	             PWMDTY45=370;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=375;
	             PWMDTY45=0;
	             PWMDTY67=370;
	              delay1() ;
	              count++;
	              if(count>=3)
	              bee_flag=0;
	           } 
	           
	            if(jiaodu==130)   // 225            
	                
	           {
               PWMDTY01=375;
	             PWMDTY23=0;
	             PWMDTY45=365;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=375;
	             PWMDTY45=0;
	             PWMDTY67=365;
	              delay1() ;
	              count++;
	              if(count>=4)
	              bee_flag=0;
	           } 
	             if(jiaodu==120)   // 225            
	                
	           {
               PWMDTY01=380;
	             PWMDTY23=0;
	             PWMDTY45=360;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=380;
	             PWMDTY45=0;
	             PWMDTY67=360;
	              delay1() ;
	              count++;
	              if(count>=4)
	              bee_flag=0;
	           }
	             if(jiaodu==110)   // 225            
	                
	           {
               PWMDTY01=380;
	             PWMDTY23=0;
	             PWMDTY45=355;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=380;
	             PWMDTY45=0;
	             PWMDTY67=355;
	              delay1() ;
	              count++;
	              if(count>=4)
	              bee_flag=0;
	           }
	           if(jiaodu==100)   // 225            
	                
	           {
               PWMDTY01=370;
	             PWMDTY23=0;
	             PWMDTY45=300;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=0;
	             PWMDTY23=370;
	             PWMDTY45=0;
	             PWMDTY67=300;
	              delay1() ;
	              count++;
	              if(count>=6)
	              bee_flag=0;
	           }
	         }  
	           
	           
	           
	           
	           
	           
	           
	           
	        /*   
	           
         if(jiaodu==220)   // 225            
	                
	           {
          
	             PWMDTY01=400;
	             PWMDTY23=0;
	             PWMDTY45=400;
	             PWMDTY67=0;
	              delay1() ;
	                     
	             PWMDTY01=100;
	             PWMDTY23=0;
	             PWMDTY45=300;
	             PWMDTY67=0;
	              delay1() ;
	                
	           }
	       if(jiaodu==210)             
	                
	           {          // 210
	                 
	                    
	                     PWMDTY01=400;
	                      PWMDTY23=0;
	                     PWMDTY45=380;
	                        PWMDTY67=0;
	                   delay1() ;
	                     
	                     PWMDTY01=50;
	                      PWMDTY23=0;
	                     PWMDTY45=50;
	                        PWMDTY67=0;
	                         delay1() ;  
	           }
	                       
	         if(jiaodu==250)             
	                
	           {             //250
	                    
	                     
	                     PWMDTY01=370;
	                      PWMDTY23=0;
	                     PWMDTY45=400;
	                        PWMDTY67=0;
	                   delay1() ;
	                     
	                     PWMDTY01=50;
	                      PWMDTY23=0;
	                     PWMDTY45=50;
	                        PWMDTY67=0;
	                         delay1() ;  
	           }
           if(jiaodu==130)             
	                
	           {        //135 
             
                       
	                     PWMDTY01=400;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=400;
	                   delay1() ;
	                     
	                     PWMDTY01=0;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=0;
	                         delay1() ;  
                         
	           }
                     
              if(jiaodu==155) //155            
	                
	           {         
                         
             
	                     PWMDTY01=400;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=380;
	                   delay1() ;
	                     
	                     PWMDTY01=0;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=0;
	                         delay1() ;  
	           }
                        
                if(jiaodu==115)             
	                
	           {         //115
                     
                       
	                     PWMDTY01=370;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=400;
	                   delay1() ;
	                     
	                     PWMDTY01=0;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=0;
	                         delay1() ;  
	           }
                        
               if(jiaodu==90) //90           
	                
	           {          
                   
                      PWMDTY01=0;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=400;
	                    delay1() ;
	                     
	                     PWMDTY01=0;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=0;
	                         delay1() ;     
                          
	           }
           if(jiaodu==0)             
	                
	           {  // 0
                      PWMDTY01=0;
	                      PWMDTY23=400;
	                     PWMDTY45=0;
	                        PWMDTY67=0;
	                   delay1() ;
	                     
	                     PWMDTY01=0;
	                      PWMDTY23=0;
	                     PWMDTY45=0;
	                        PWMDTY67=0;
	                         delay1() ;    
                   
	           }
	           
	            */
  //  }
}
       
   
 if(PTM_PTM0==0&&PTM_PTM1==1&&PTM_PTM2==1)  //模式3  制动***************

{

          if(shua_flag3==0)
       	ILI9163B_display_full(BLACK);		//刷屏 
       	shua_flag3=1; 
        LCD_prints16(5,2,"Model 4",WHITE,BLACK); 
          LCD_prints16(5,4,"STOP",WHITE,BLACK);
         
         Get_ADresultY();
         DatehandleY();   
	       Get_ADresultX();
         DatehandleX();  
	       rqX=GyrAccCraX;
	       rzX= GyrAccCraX-rhX;
	       rhX=rqX;
	                 
	           
	           
	            rqY=GyrAccCraY;
	               rzY= GyrAccCraY-rhY;
	               rhY=rqY;          
	            
	              if(rzX>0) 
	              {
                     PWMDTY45=0;
	                   PWMDTY67=400;
	              }
	              
	              if(rzX<=0) 
	              {
                     PWMDTY45=400;
	                   PWMDTY67=0;
	              }
	            
	                 
	             
	              
	              if(rzY>0) 
	              {
                    PWMDTY01=400;
	                   PWMDTY23=0;
	              }
	              
	              if(rzY<=0) 
	              {
                     PWMDTY01=0;
	                   PWMDTY23=400;
	              }
	             
	                
	            
	            
	            /*
	             
	                 if(rzX<=-0.11)
	                 
	                   {
	                    PWMDTY45=400;
	                   PWMDTY67=0;
	                   
	                   }
	                   
	                     if(rzX>=0.11)
	               
	               {
	                   PWMDTY45=0;
	                   PWMDTY67=400;
	                      
	               } 
	               
	                if(rzX<0.11&&rzX>-0.11)
	                  
	                  {
	                      PWMDTY45=0;
	                    PWMDTY67=0;
	                    
	                      
	                  }    
	                  
	                    
	                   
	                 
	                 if(rzY>=0.12)
	               
	               {
	                   
	                    PWMDTY01=400;
	                   PWMDTY23=0;
	                    
	               } else  if(rzY<0.12&&rzY>-0.12)
	                  
	                  {
	                      
	                       PWMDTY01=0;
	                   PWMDTY23=0;
	                      
	                  } else if(rzY<=-0.12)
	                 
	                 {
	                     PWMDTY01=0;
	                   PWMDTY23=400;
	                 
	                 }
	                  */
	                     
                 
          }
 
 
  if(PTM_PTM0==1&&PTM_PTM1==0&&PTM_PTM2==0)  //模式4    画圆 1 *********************

{
	       P1X=10;//2;
	       D1X=40;//10;
	       P1Y=2;//2;
	       D1Y=10;//10;
	        // PWMDTY67=400;
	        
	           set_data(); 
	           	if(shua_flag4==0)
       	ILI9163B_display_full(BLACK);		//刷屏 
       	shua_flag4=1; 
	      LCD_prints16(5,2,"Model 5",WHITE,BLACK);      
     LCD_prints16(5,4,"Circle",WHITE,BLACK);
     LCD_prints16(5,6,"R:",WHITE,BLACK);
     LCD_prints16(8,6,"20",WHITE,BLACK);
     LCD_prints16(11,6,"cm",WHITE,BLACK);
    // LCD_bianliang(7, 13, result ,WHITE,BLACK) ;
    
       R= result; //40
	        
	      if(m==13)
	      
	      {
	        
	                SDZX=27; 
	                  SDZY=48; 
	        
	                for(i=0;i<=1;i++)
	                
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                     PWMDTY01=400;
	                   PWMDTY23=0;
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                      PWMDTY01=0;
	                   PWMDTY23=400;
	                    delay1() ;
	                    
	                }
	                   yuan_flag=1;
	                    yuan_flag1=0;
	                while(1)
	                   
	                {  
	                if(yuan_flag==1)
	                
	                 count2++;
	                    if(count2>=5000) 
	                    {
	                    count2=0;  
	                    bee_flag=0;
	                    yuan_flag=0;
	                    }
	                   if(yuan_flag==0) 
	                   count3++;
	                   
	                   if(count3>=4300)
	                   {
	                    count3=0;  
	                    bee_flag=0;
	                    yuan_flag=10;
	                    }
	                   
	                    
	                    Get_ADresultY();
         DatehandleY();   
	        Get_ADresultX();
         DatehandleX();  
	             rqX=GyrAccCraX;
	               rzX= GyrAccCraX-rhX;
	               rhX=rqX;
	               lqX=GyrAccCraX;
	                 lzX= GyrAccCraX-lhX;
	                  lhX=lqX;
	                  
	                  
	                rqY=GyrAccCraY;
	               rzY= GyrAccCraY-rhY;
	               rhY=rqY;
	               lqY=GyrAccCraY;
	                 lzY= GyrAccCraY-lhY;
	                  lhY=lqY;
	                  
	                     
	       JIAOX=atan(SDZX/90)*180/3.1415;
	       JIAOQX=atan((SDZX-1)/90)*180/3.1415;
	       JIAOHX=atan((SDZX+1)/90)*180/3.1415;
	         JIAOY=atan(SDZY/90)*180/3.1415;
	       JIAOQY=atan((SDZY-1)/90)*180/3.1415;
	       JIAOHY=atan((SDZY+1)/90)*180/3.1415;
	               
	               if(rzX<=0&&lzX<=0)
	               
	               {
	                   PWMDTY45=0;
	                   PWMDTY67=400;
	               }
	                  
	                  if(lzX>=0&&rzX>=0)
	                  
	                  {
	                      PWMDTY45=400;
	                    PWMDTY67=0;
	                    
	                  } 
	                  
	                
                   
                   
                   
                   
                    if(lzY<=0&&rzY<=0)
	               
	               {
	                   PWMDTY23=0;
	                   PWMDTY01=400;
	               }
	                  
	                  if(lzY>=0&&rzY>=0)
	                  
	                  {
	                      PWMDTY23=400;
	                    PWMDTY01=0;
	                    
	                  } 
	                  
	                  
	                  
	                  
                   
	                  if( GyrAccCraX>=JIAOQX-1)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     
	                 }
	                  if( GyrAccCraX<=-JIAOQX+1)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                    
	                 }           
	               
	               
	               
	                  if( GyrAccCraY>=JIAOQY-1)
	                 
	                 {
	                    PWMDTY23=0;
	                    PWMDTY01=0;
	                     
	                 }
	                  if( GyrAccCraY<=-JIAOQY+1)
	                 
	                 {
	                    PWMDTY23=0;
	                    PWMDTY01=0;
	                    
	                 }     
	               
	               } 
	               
	      }
	                 
  }  


 
 
  if(PTM_PTM0==1&&PTM_PTM1==0&&PTM_PTM2==1)  //模式5   画圆 2  ************************8

{
	        
	                SDZX=27; 
	                  SDZY=48; 
	        
	                for(i=0;i<=1;i++)
	                
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                     PWMDTY01=400;
	                   PWMDTY23=0;
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                      PWMDTY01=0;
	                   PWMDTY23=400;
	                    delay1() ;
	                    
	                }
	                   yuan_flag=1;
	                 
	                while(1)
	                   
	                {  
	                if(yuan_flag==1)
	                
	                 count2++;
	                    if(count2>=5000) 
	                    {
	                    count2=0;  
	                    bee_flag=0;
	                    yuan_flag=0;
	                    }
	                    
	                    
	                    Get_ADresultY();
         DatehandleY();   
	        Get_ADresultX();
         DatehandleX();  
	             rqX=GyrAccCraX;
	               rzX= GyrAccCraX-rhX;
	               rhX=rqX;
	               lqX=GyrAccCraX;
	                 lzX= GyrAccCraX-lhX;
	                  lhX=lqX;
	                  
	                  
	                rqY=GyrAccCraY;
	               rzY= GyrAccCraY-rhY;
	               rhY=rqY;
	               lqY=GyrAccCraY;
	                 lzY= GyrAccCraY-lhY;
	                  lhY=lqY;
	                  
	                     
	       JIAOX=atan(SDZX/90)*180/3.1415;
	       JIAOQX=atan((SDZX-1)/90)*180/3.1415;
	       JIAOHX=atan((SDZX+1)/90)*180/3.1415;
	         JIAOY=atan(SDZY/90)*180/3.1415;
	       JIAOQY=atan((SDZY-1)/90)*180/3.1415;
	       JIAOHY=atan((SDZY+1)/90)*180/3.1415;
	               
	               if(rzX<=0&&lzX<=0)
	               
	               {
	                   PWMDTY45=0;
	                   PWMDTY67=400;
	               }
	                  
	                  if(lzX>=0&&rzX>=0)
	                  
	                  {
	                      PWMDTY45=400;
	                    PWMDTY67=0;
	                    
	                  } 
	                  
	                
                   
                   
                   
                   
                    if(lzY<=0&&rzY<=0)
	               
	               {
	                   PWMDTY23=0;
	                   PWMDTY01=400;
	               }
	                  
	                  if(lzY>=0&&rzY>=0)
	                  
	                  {
	                      PWMDTY23=400;
	                    PWMDTY01=0;
	                    
	                  } 
	                  
	                  
	                  
	                  
                   
	                  if( GyrAccCraX>=JIAOQX-1)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     
	                 }
	                  if( GyrAccCraX<=-JIAOQX+1)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                    
	                 }           
	               
	               
	               
	                  if( GyrAccCraY>=JIAOQY-1)
	                 
	                 {
	                    PWMDTY23=0;
	                    PWMDTY01=0;
	                     
	                 }
	                  if( GyrAccCraY<=-JIAOQY+1)
	                 
	                 {
	                    PWMDTY23=0;
	                    PWMDTY01=0;
	                    
	                 }     
	               
	               } 
	               
	      }
 
 
  if(PTM_PTM0==1&&PTM_PTM1==1&&PTM_PTM2==0)  //模式6    自定义  *****************

{
        P1X=10;//2;
	       D1X=40;//10;
	       P1Y=2;//2;
	       D1Y=10;//10;
	        // PWMDTY67=400;
	        
	           set_data(); 
	           	if(shua_flag4==0)
       	ILI9163B_display_full(BLACK);		//刷屏 
       	shua_flag4=1; 
	      LCD_prints16(5,2,"Model 5",WHITE,BLACK);      
     LCD_prints16(5,4,"Circle",WHITE,BLACK);
     LCD_prints16(5,6,"R:",WHITE,BLACK);
     LCD_prints16(8,6,"20",WHITE,BLACK);
     LCD_prints16(11,6,"cm",WHITE,BLACK);
    // LCD_bianliang(7, 13, result ,WHITE,BLACK) ;
    
       R= result; //40
	        
	      if(m==13)
	      
	      {
	        
	                SDZX=25; 
	                  SDZY=50; 
	        
	                for(i=0;i<=2;i++)
	                
	                {
	                  
	    
	               
	                   PWMDTY67=400;
	                   PWMDTY45=0;
	                     PWMDTY01=400;
	                   PWMDTY23=0;
	                   delay1() ;
	                     PWMDTY67=0;
	                   PWMDTY45=400;
	                      PWMDTY01=0;
	                   PWMDTY23=400;
	                    delay1() ;
	                    
	                }
	                
	                 
	                while(1)
	                
	                {   count2++;
	                    if(count2>=5000) 
	                    {
	                    count2=0;  
	                    bee_flag=0;
	                    }
	                    Get_ADresultY();
         DatehandleY();   
	        Get_ADresultX();
         DatehandleX();  
	             rqX=GyrAccCraX;
	               rzX= GyrAccCraX-rhX;
	               rhX=rqX;
	               lqX=GyrAccCraX;
	                 lzX= GyrAccCraX-lhX;
	                  lhX=lqX;
	                  
	                  
	                rqY=GyrAccCraY;
	               rzY= GyrAccCraY-rhY;
	               rhY=rqY;
	               lqY=GyrAccCraY;
	                 lzY= GyrAccCraY-lhY;
	                  lhY=lqY;
	                  
	                     
	       JIAOX=atan(SDZX/90)*180/3.1415;
	       JIAOQX=atan((SDZX-1)/90)*180/3.1415;
	       JIAOHX=atan((SDZX+1)/90)*180/3.1415;
	         JIAOY=atan(SDZY/90)*180/3.1415;
	       JIAOQY=atan((SDZY-1)/90)*180/3.1415;
	       JIAOHY=atan((SDZY+1)/90)*180/3.1415;
	               
	               if(rzX<=0&&lzX<=0)
	               
	               {
	                   PWMDTY45=0;
	                   PWMDTY67=400;
	               }
	                  
	                  if(lzX>=0&&rzX>=0)
	                  
	                  {
	                      PWMDTY45=400;
	                    PWMDTY67=0;
	                    
	                  } 
	                  
	                
                   
                   
                   
                   
                    if(lzY<=0&&rzY<=0)
	               
	               {
	                   PWMDTY23=0;
	                   PWMDTY01=400;
	               }
	                  
	                  if(lzY>=0&&rzY>=0)
	                  
	                  {
	                      PWMDTY23=400;
	                    PWMDTY01=0;
	                    
	                  } 
	                  
	                  
	                  
	                  
                   
	                  if( GyrAccCraX>=JIAOQX-1)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                     
	                 }
	                  if( GyrAccCraX<=-JIAOQX+1)
	                 
	                 {
	                    PWMDTY45=0;
	                    PWMDTY67=0;
	                    
	                 }           
	               
	               
	               
	                  if( GyrAccCraY>=JIAOQY-1)
	                 
	                 {
	                    PWMDTY23=0;
	                    PWMDTY01=0;
	                     
	                 }
	                  if( GyrAccCraY<=-JIAOQY+1)
	                 
	                 {
	                    PWMDTY23=0;
	                    PWMDTY01=0;
	                    
	                 }     
	               
	               } 
	               
	      }
     

}
 

 
    
       


  }
 
}

