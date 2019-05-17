/*************	���س�������	**************/
#define MAIN_Fosc		22118400L	//������ʱ��
#define	RX1_Lenth		32			//���ڽ��ջ��峤��
//#define	BaudRate1		9600UL	//ѡ������
//#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 ��װֵ�� ��Ӧ300KHZ
//#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 ��װֵ�� ��Ӧ300KHZ
#include"STC15Fxxxx.H"
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
/*************	���ر�������	**************/
u8	idata RX1_Buffer[RX1_Lenth];	//���ջ���
u8	TX1_Cnt;	//���ͼ���
u8	RX1_Cnt;	//���ռ���
bit	B_TX1_Busy;	//����æ��־
/*************	�˿����Ŷ���	**************/
sbit LED1=P1^0;//LED1
sbit LED2=P1^1;//LED2
sbit LED3=P3^7;//LED3
sbit DK1=P3^3;//�̵���
sbit BEEP=P3^4;//������
sbit K1=P1^3;//����1
sbit K2=P1^2;//����2
sbit K3=P1^4;//����3
sbit DQ=P1^6;//18B20�¶ȴ�����
char led1bl,led2bl,led3bl;
#define jump_ROM 0xCC                   //����ROM����
#define start    0x44               //����ת������
#define read_EEROM 0xBE                 //���洢������
uchar TMPH,TMPL;                //�¶�ֵ
uchar HL;                      //��ǰ�¶�
unsigned char LYMS[13]="AT+CWMODE=2\r\n";
unsigned char SZLY[38]="AT+CWSAP='ESP8266','0123456789',11,0\r\n";
unsigned char RST[8]="AT+RST\r\n";
unsigned char SZDLJ[13]="AT+CIPMUX=1\r\n";
unsigned char KQFU[21]="AT+CIPSERVER=1,5000\r\n";
unsigned char FSSJ[13]="AT+CIPSEND=\r\n";//AT+CIPSEND= ��������
unsigned char WDSJ[4]={0x00,0x00,0x00,0x00};
void Delay1(unsigned long ms)
{
	unsigned char i, j,k;
	for(k=0;k<ms;k++)
	{
		_nop_();
		_nop_();
		i = 22;
		j = 128;
		do
		{
			while (--j);
		} while (--i);
	}
}
void Delay2(unsigned long cnt)
{
	long i;
 	for(i=0;i<cnt*100;i++);
}
void Delay3(unsigned int N) 
{
	int i;
	for(i=0;i<N*10;i++);
}
//--------------------
// �������ƣ� Reset
// ��ڲ����� ��
// ����deceive_ready
// �������ܣ���λ 
//--------------------
unsigned char Reset(void) 
{
	unsigned char deceive_ready;
	Delay3(10); 
	DQ=0;                               //����DQ�� 
	Delay3(29);                          //��ʱ����480us~960us
	DQ=1;                               //��DQ������λ�߼���    
	Delay3(3);                           //��ʱ�ȴ�deceive_ready��Ӧ 
	deceive_ready=DQ;                   //����deceive_ready�ź�
	Delay3(25);                          //�ȴ�ʱ�����
	return(deceive_ready);              //��deceive_ready�ź�ʱ����0�����򷵻�1
}


//---------------------------
// �������ƣ�read_bit
// ��ڲ����� ��
// ���ؽ��յ�����
// �������ܣ���һ��bit�ӳ��� 
//---------------------------
unsigned char read_bit(void)
{
	unsigned char i;
	DQ=0;                                 //����DQ�߿�ʼʱ��
	DQ=1;                                 //����DQ��                        
	for(i=0;i<3;i++);         //��ʱ��ʱ��ʼ15us
	return(DQ);                           //����DQֵ
}


//---------------------------
// �������ƣ� write_bit
// ��ڲ����� bitval
// �������ܣ�дһ��bit�ӳ��� 
//---------------------------
void write_bit(unsigned char bitval)
{
	DQ=0;                             //����DQ�߿�ʼʱ��
	if(bitval==1)
		DQ=1;                             //���д�߼�Ϊ��
	Delay3(5);                         //��ʱ 
	DQ=1;                             //����DQ�� 
}


//----------------------------
// �������ƣ� write_byte
// ��ڲ����� val
// �������ܣ�дһ��byte�ӳ��� 
//----------------------------
void write_byte(unsigned char val)
{
	unsigned char i,temp;
	for(i=0;i<8;i++)
	{
		temp=val>>i;                        //��valλ����iλ��ֵ����temp
		temp=temp&0x01;                     //ȡtemp���λ
		write_bit(temp);
		Delay3(5);                           //��ʱ��ʱ�����
	}
}


//----------------------------
// �������ƣ� read_byte
// ���ؽ��յ����� value
// �������ܣ���һ��byte�ӳ��� 
//----------------------------
unsigned char read_byte(void)
{
	unsigned char i,m,receive_data;
	m=1;receive_data=0;                          //��ʼ��
	for(i=0;i<8;i++)
	{
		if(read_bit()) 
		{
			receive_data=receive_data+(m<<i);
		}                                          //ÿ��һλ���ݾݣ�����һλ 
		Delay3(6);                                  //��ʱ��ʱ����� 
	} 
	return(receive_data);                        //����value
}


//---------------------------
// �������ƣ� Get_temp
// ���ؽ��յ����� TMPL, TMPH
// �������ܣ�ȡ���¶�ֵ
//---------------------------
uint Get_temp(void)
{
	unsigned int T;
	//EA = 0;
	Reset();
	write_byte(jump_ROM);       //������ROM����
	write_byte(start);          //������ת������
	Reset();
	write_byte(jump_ROM);       //������ROM����
	write_byte(read_EEROM);     //������ROM����
	TMPL=read_byte();           //����8λ�¶�ֵ
	TMPH=read_byte();           //����8λ�¶�ֵ
	
	//EA = 0;
	T=TMPL+TMPH*256;     
	if(T==0xFFFF) return 0xFFFF;
	if(T>0x8000)   //�¶�Ϊ��
	{
		T=~T+1;
		return(0x8000+T*5/8);
	}
	else     //�¶�λ��
	{
		return(T*5/8);
	}
}
void UARTSendByte(unsigned char byte)//?????????
{
	SBUF=byte;              //???????????
	while(TI==0);          //??????,TI?????1
	TI=0;                    //?????????
}
void DisplayTemp(unsigned int temp)
{
	uchar i=0;
	uchar TmpTable[3] = {0};
	TmpTable[ 0 ] = (temp%1000)/100;
	TmpTable[ 1 ] = (temp%100)/10;
	TmpTable[ 2 ] = (temp%10);

//	UARTSendByte(TmpTable[0] + 0x30);Delay3(9);
//	UARTSendByte(TmpTable[1] + 0x30);Delay3(9);
//	UARTSendByte('.');Delay3(9);
//	UARTSendByte(TmpTable[2] + 0x30);Delay3(9);	
//	UARTSendByte(0x0d);Delay3(9);	
//	UARTSendByte(0x0a);Delay3(9);
	WDSJ[0]=(TmpTable[0] + 0x30);
	WDSJ[1]=(TmpTable[1] + 0x30);
	WDSJ[2]=('.');
	WDSJ[3]=(TmpTable[2] + 0x30);	
}
void main(void)
{
	char i=0;
	B_TX1_Busy = 0;
	RX1_Cnt = 0;
	TX1_Cnt = 0;
	S1_8bit();				//8λ����
	S1_USE_P30P31();		//UART1 ʹ��P30 P31��	Ĭ��
	/*AUXR &= ~(1<<4);	//Timer stop		������ʹ��Timer2����
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = (u8)(Timer2_Reload >> 8);
	TL2 = (u8)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable
	REN = 1;	//�������
	ES  = 1;	//�����ж�
	EA = 1;		//����ȫ���ж�*/
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xD0;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	REN = 1;	//�������
	ES  = 1;	//�����ж�
	EA = 1;		//����ȫ���ж�*/
	P3M1 = 0x00;
    P3M0 = 0xFF;
	RX1_Cnt=0;
	DK1=0;
	BEEP=0;
	Delay2(2000);
	for(i=0;i<13;i++)//AT+CWMODE=2 ���ó�·��ģʽ
	{
		SBUF=LYMS[i];Delay1(5);
	}
	Delay2(1000);
	for(i=0;i<38;i++)//AT+CWSAP="ESP8266","0123456789",11,0 ����·��
	{
		SBUF=SZLY[i];Delay1(5);
	}
	Delay2(3000);
	for(i=0;i<8;i++)//AT+RST ����
	{
		SBUF=RST[i];Delay1(5);
	}
	Delay2(5000);
	for(i=0;i<13;i++)//AT+CIPMUX=1 ���óɶ�����
	{
		SBUF=SZDLJ[i];Delay1(5);
	}
	Delay2(2000);
	for(i=0;i<21;i++)//AT+CIPSERVER=1,5000 ����TCP����˿�
	{
		SBUF=KQFU[i];Delay1(5);
	}
	Delay2(2000);
	Get_temp();
	Delay3(50000);
	Get_temp();
	Delay3(50000);
	while (1)
	{
		DisplayTemp(Get_temp());//ˢ��18B20
		if(K1==0)
		{
			Delay1(5);
			if(K1==0)
			{
				LED1=!LED1;
			}
			while(K1==0);
		}
		if(K2==0)
		{
			Delay1(5);
			if(K2==0)
			{
				LED2=!LED2;
			}
			while(K2==0);
		}
		if(K3==0)
		{
			Delay1(5);
			if(K3==0)
			{
				LED3=!LED3;
			}
			while(K3==0);
		}
	}
}

/********************* UART1�жϺ���************************/
void UART1_int (void) interrupt UART1_VECTOR
{
	char i,a,b,c;
	if(RI)
	{
		RI = 0;
		RX1_Buffer[RX1_Cnt] = SBUF;		
		if(RX1_Buffer[0]==0x45)
		{
			RX1_Cnt++;
		}
		else
		{
			RX1_Cnt=0;
		}
		if(RX1_Cnt>=10)
		{
			if(RX1_Buffer[0]==0x45&&RX1_Buffer[1]==0x53&&RX1_Buffer[2]==0x50)
			{
				if(RX1_Buffer[4]==0x4C&&RX1_Buffer[5]==0x45&&RX1_Buffer[6]==0x44)//�ж�LED
				{
					if(RX1_Buffer[7]==0x31)//�ж�LED1
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							LED1=0;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							LED1=1;
						}
					}
					if(RX1_Buffer[7]==0x32)//�ж�LED2
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							LED2=0;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							LED2=1;
						}
					}
					if(RX1_Buffer[7]==0x33)//�ж�LED3
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							LED3=0;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							LED3=1;
						}
					}
				}
				if(RX1_Buffer[4]==0x4A&&RX1_Buffer[5]==0x44&&RX1_Buffer[6]==0x51)//�жϼ̵���
				{
					if(RX1_Buffer[7]==0x31)//�ж�LED1
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							DK1=1;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							DK1=0;
						}
					}
				}
				if(RX1_Buffer[3]==0x46&&RX1_Buffer[4]==0x4D&&RX1_Buffer[5]==0x51&&RX1_Buffer[6]==0x43&&RX1_Buffer[7]==0x53)//�жϷ�����
				{
					BEEP=1;Delay2(100);BEEP=0;Delay2(100);BEEP=1;Delay2(100);BEEP=0;Delay2(100);
				}
				if(RX1_Buffer[3]==0x43&&RX1_Buffer[4]==0x58&&RX1_Buffer[5]==0x53&&RX1_Buffer[6]==0x4A)//��ѯ����
				{
					if(LED1==0){a=0x4B;}else{a=0x47;}
					if(LED2==0){b=0x4B;}else{b=0x47;}
					if(LED3==0){c=0x4B;}else{c=0x47;}
					for(i=0;i<11;i++)//AT+CIPSEND= ��������
					{
						SBUF=FSSJ[i];Delay1(5);
					}
					SBUF=0x30;Delay1(5);
					SBUF=0x2C;Delay1(5);
					SBUF=0x32;Delay1(5);
					SBUF=0x36;Delay1(5);
					SBUF=0x0D;Delay1(5);
					SBUF=0x0A;Delay1(5);
					
					SBUF=0x45;Delay1(5);
					SBUF=0x53;Delay1(5);
					SBUF=0x50;Delay1(5);
					SBUF=0x4C;Delay1(5);
					SBUF=0x45;Delay1(5);
					SBUF=0x44;Delay1(5);
					SBUF=0x31;Delay1(5);
					SBUF=a;Delay1(5);
					SBUF=0x4C;Delay1(5);
					SBUF=0x45;Delay1(5);
					SBUF=0x44;Delay1(5);
					SBUF=0x32;Delay1(5);
					SBUF=b;Delay1(5);
					SBUF=0x4C;Delay1(5);
					SBUF=0x45;Delay1(5);
					SBUF=0x44;Delay1(5);
					SBUF=0x33;Delay1(5);
					SBUF=c;Delay1(5);
					SBUF=WDSJ[0];Delay1(5);
					SBUF=WDSJ[1];Delay1(5);
					SBUF=WDSJ[2];Delay1(5);
					SBUF=WDSJ[3];Delay1(5);
					SBUF=0x50;Delay1(5);
					SBUF=0x53;Delay1(5);
					SBUF=0x45;Delay1(5);
					SBUF=0x0A;Delay1(5);
					//SBUF=0x0A;Delay1(5);
					//45 53 50 4C 45 44 31 4B 4C 45 44 32 4B 4C 45 44 33 4B 50 53 45 
				}
				RX1_Cnt=0;
			}
			else
			{
				RX1_Cnt=0;
			}
			RX1_Cnt=0;
		}
	}
	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;		//�������æ��־
	}
}