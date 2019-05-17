#include "reg52.h"
#define uchar unsigned char 
#define uint unsigned int

uint cnt;
sbit men=P0^0;
sbit io2=P1^2;
sbit io4=P1^3;
sbit ena=P1^4;
sbit io15=P1^1;
bit rflag=0;

uchar RX1_Buffer[32];
uchar RX1_Cnt=0;
void SerialInti()//��ʼ�����򣨱���ʹ�ã������޷��շ���
{
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFF;
    TL1 = TH1;

    PCON = 0x80;

    EA = 1;
    ES = 1;
    TR1 = 1;
}

/*����ͨѶ�жϣ��շ���ɽ�������ж�*/
void Serial_interrupt() interrupt 4 
{
//	a=SBUF;
	if(RI)
	{
		RI=0;
		
	  RX1_Buffer[RX1_Cnt] = SBUF;	
		if(RX1_Buffer[0]=='0')
		{
			RX1_Cnt++;
		}
		else
		{
			RX1_Cnt=0;
		}
		if(RX1_Cnt>4)
		{
		if((RX1_Buffer[1]==',')&&(RX1_Buffer[2]=='C')&&(RX1_Buffer[3]=='O'))	
		rflag=1;
		RX1_Cnt=0;
		}
		if(RX1_Cnt>4)
		{
		if((RX1_Buffer[1]==',')&&(RX1_Buffer[2]=='C')&&(RX1_Buffer[3]=='L'))
		{
			rflag=0;
		RX1_Cnt=0;
		}			
	
		}
	}
	//�����ж��ź����㣬��ʾ����������
//	flag=1;//�����жϵı�־����
}



void Uart1Send(uchar c)
{
	SBUF=c;
	while(!TI);//�ȴ���������źţ�TI=1������
	TI=0;	
}

//���п���������char�����飬������ֹ��/0��ֹͣ
void Uart1Sends(uchar *str)
{
	unsigned char *p;
    
    p = str;
    while(*p != '\0')
    {
        SBUF = *p;
		while(TI == 0); 
		TI = 0;
        p++;
    }
}
void delay(uint ms)
{
 uint i;
	while(ms--)
	{
	for(i=0;i<=500;i++);
	}
}
void main()
{	men=0;
	io15=0;
	io2=1;
	io4=1;
	ena=1;
	  delay(2500);	
		

	SerialInti();
	delay(500);
Uart1Sends("AT+RST\r\n");	
delay(1500);	
Uart1Sends("AT+CWMODE=2\r\n");	
delay(500);
Uart1Sends("AT+CIPMUX=1\r\n");
delay(500);
Uart1Sends("AT+CIPSERVER=1,8888\r\n");
delay(500);
while(1)
{

				while(rflag==1)
{
	if(men==1)
	{
delay(2500);
Uart1Sends("AT+RST\r\n");	
delay(1500);	
Uart1Sends("AT+CWMODE=2\r\n");	
delay(500);
Uart1Sends("AT+CIPMUX=1\r\n");
delay(500);
Uart1Sends("AT+CIPSERVER=1,8888\r\n");
delay(500);
	
		while(men==1)
		{	

Uart1Sends("AT+CIPSEND=0,8\r\n");
delay(500);
Uart1Sends("waiting\n");	
delay(1500);
			if(men==0)
			{break;}
		}
}
	if(men==0)
	{
	delay(2500);
Uart1Sends("AT+RST\r\n");	
delay(1500);	
Uart1Sends("AT+CWMODE=2\r\n");	
delay(500);
Uart1Sends("AT+CIPMUX=1\r\n");
delay(500);
Uart1Sends("AT+CIPSERVER=1,8888\r\n");
delay(500);
		while(men==0)
		{	
	
Uart1Sends("AT+CIPSEND=0,8\r\n");
delay(500);
Uart1Sends("working\r\n");	
delay(1500);
	if(men==1)
	{break;}		
}
}
}


	}
}
