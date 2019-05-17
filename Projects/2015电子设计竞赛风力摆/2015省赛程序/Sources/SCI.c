 #include "main.h"
 

 int data=0;

 extern int i,j; 
//发送变量 *****************************
unsigned char  SCI0_putchar(void)
{
  while(!SCI0SR1_TDRE);         
   SCI0DRL=data;                                    
                  
}

/*发送数组*****************************
unsigned char  SCI0_putshuzu(void)
{ 

int k=0;

for(k=0;k<6;k++)

  {
  
  while(!SCI0SR1_TDRE);         
   SCI0DRL=m[k]; 
   
  }
}    
     */
//接收变量*********************************       
unsigned char  SCI0_Receivechar(void)
{
  while(!SCI0SR1_RDRF);         
   data=SCI0DRL; 
                  
}



/*接收数组*********************************    
unsigned char  SCI0_Receiveshuzu(void)
{
   int k=0;
  for(k=0;k<6;k++) 
  {
    
  while(!SCI0SR1_RDRF);         
   m[k]=SCI0DRL; 
  }
}    
 
 
     */
 
 
 
 
/***********************************************************
                      串口接收校验函数 2                  
************************************************************
void SCI_receive_jiaoyan2(void) 
{
  uchar i,j;
  LCD_bianliang(15,2,0,BLACK,WHITE);  //0


       
// if(q[0]==255&&q[1]==255&&q[2]==255)
 

//   { 
    
     
     for(i=0;i<3;i++)
  
     {       LCD_bianliang(15,6,4,BLACK,WHITE); 
        for(j=0;j<3;j++)
        {
              LCD_bianliang(15,7,5,BLACK,WHITE); 
          while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
          LCD_bianliang(15,8,6,BLACK,WHITE); 
          p[i][j]=SCI0DRL;               //返回接受的数据
        }
     }   
   
      // flag++;
   
//   }
    }   
  */

 
 
 

 /***********************************************************
                     发字符串                         
************************************************************
 
void SendData(uchar dat) //interrupt 4 using 1
{
	
	ACC=dat;
	//TB8=~P;
	SBUF=dat; 
	while(!TI);
	TI=0;
}

void SendString(char *s)
{
	while(*s)
	{
	SendData(*s++);
	}
	Delay1ms(10);
}
     */
 
 
/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);       //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;             //把数据放入SCI数据存储器
}


/*************************************************************/
/*                  串口发送字符串函数                       */
/*************************************************************/
void send_string(unsigned char *putchar) 
{
  while(*putchar!=0x00)       //判断字符串是否发送完毕
  {
   SCI_send(*putchar++);      //发送字符串
  }
  delay_ms(1);
}
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 #pragma CODE_SEG __NEAR_SEG NON_BANKED