 #include "main.h"
 

 int data=0;

 extern int i,j; 
//���ͱ��� *****************************
unsigned char  SCI0_putchar(void)
{
  while(!SCI0SR1_TDRE);         
   SCI0DRL=data;                                    
                  
}

/*��������*****************************
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
//���ձ���*********************************       
unsigned char  SCI0_Receivechar(void)
{
  while(!SCI0SR1_RDRF);         
   data=SCI0DRL; 
                  
}



/*��������*********************************    
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
                      ���ڽ���У�麯�� 2                  
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
          while(!SCI0SR1_RDRF);          //�ȴ��������ݼĴ�����
          LCD_bianliang(15,8,6,BLACK,WHITE); 
          p[i][j]=SCI0DRL;               //���ؽ��ܵ�����
        }
     }   
   
      // flag++;
   
//   }
    }   
  */

 
 
 

 /***********************************************************
                     ���ַ���                         
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
/*                       ���ڷ��ͺ���                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);       //�ȴ��������ݼĴ�������������Ϊ��
  SCI0DRL = data;             //�����ݷ���SCI���ݴ洢��
}


/*************************************************************/
/*                  ���ڷ����ַ�������                       */
/*************************************************************/
void send_string(unsigned char *putchar) 
{
  while(*putchar!=0x00)       //�ж��ַ����Ƿ������
  {
   SCI_send(*putchar++);      //�����ַ���
  }
  delay_ms(1);
}
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 #pragma CODE_SEG __NEAR_SEG NON_BANKED