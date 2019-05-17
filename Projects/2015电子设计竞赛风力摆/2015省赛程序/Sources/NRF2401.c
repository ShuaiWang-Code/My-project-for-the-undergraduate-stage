/*****************************************
��������־ǿ
ʱ�䣺2010.6.12
���ܣ�NRF24L01��Ƶģ��C�ļ�(�ڵ㷢�䲿��)
*****************************************/
#include "MC9S12XS128.h"

#include "NRF2401.h"
#define  CE    PORTA_PA0  //3      //RX/TXģʽѡ���
#define  SCLK  PORTA_PA2 	//5      //SPIʱ�Ӷ�
#define  MISO  PORTA_PA4 	//7      //SPI��������ӻ������

#define  CSN   PORTA_PA1  //4      //SPIƬѡ��//����SS
#define  MOSI  PORTA_PA3 	//6      //SPI��������ӻ������
#define  IRQ   PORTA_PA5  //8      //�������ж϶�

#define  CE_dir    DDRA_DDRA0       
#define  IRQ_dir   DDRA_DDRA1       
#define  CSN_dir   DDRA_DDRA2       
#define  MOSI_dir  DDRA_DDRA3  	      
#define  MISO_dir  DDRA_DDRA4 	      
#define  SCLK_dir  DDRA_DDRA5	     


unsigned char  TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
/*****************״̬��־*****************************************/
unsigned char  sta;   //״̬��־

// #define   RX_DR     (( sta & 0x40 ) >>6 )
// #define   TX_DS     (( sta & 0x20 ) >>5 )
// #define   MAX_RT    (( sta & 0x10 ) >>4 )

/*********************    ��ʱ����    *********************************/
void NRF_delay_5us(void)
{
   unsigned int  i;
   for(i=0;i<1080;i++);
}

/*****************SPIʱ����******************************************/
unsigned char NRFSPI(unsigned char date)
{
    unsigned char i;
     
    MOSI_dir=1;
    MISO_dir=0;
    SCLK_dir=1;
  //  SCLK=1; 
   	for(i=0;i<8;i++)          // ѭ��8��
   	{
	  if(date&0x80)
	    MOSI=1;
	  else
	    MOSI=0;                 // byte���λ�����MOSI
   	  date<<=1;               // ��һλ��λ�����λ
   	  SCLK=1; 
	  if(MISO)                  // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   	    date|=0x01;       	  // ��MISO��byte���λ
   	  SCLK=0;            	    // SCK�õ�
   	}
    return(date);           	// ���ض�����һ�ֽ�
}
/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int(void)
{
  CE_dir=1;   
	CSN_dir=1;  
	SCLK_dir=1;
	IRQ_dir=1;
	
	NRF_delay_5us();        //��ϵͳʲô������
	CE=0;                   //����ģʽ1   
	CSN=1;  
	SCLK=0;
	IRQ=1;	 
}
/*****************SPI���Ĵ���һ�ֽں���*********************************/
unsigned char NRFReadReg(unsigned char RegAddr)
{
   unsigned char BackDate;
   CSN_dir=1;
   CSN=0;                    //����ʱ��
   NRFSPI(RegAddr);          //д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);    //д����Ĵ���ָ��  
   CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
unsigned char NRFWriteReg(unsigned char RegAddr,unsigned char date)
{
   unsigned char BackDate;
   CSN_dir=1;
   CSN=0;                         //����ʱ��
   BackDate=NRFSPI(RegAddr);      //д���ַ
   NRFSPI(date);                  //д��ֵ
   CSN=1;
   return(BackDate);
}
/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
unsigned char NRFReadRxDate(unsigned char RegAddr,unsigned char *RxDate,unsigned char DateLen)
{                           //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    unsigned char BackDate,i;
    CSN_dir=1;
	   CSN=0;                    //����ʱ��
  	BackDate=NRFSPI(RegAddr);  //д��Ҫ��ȡ�ļĴ�����ַ
	  for(i=0;i<DateLen;i++)     //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
unsigned char NRFWriteTxDate(unsigned char RegAddr,unsigned char *TxDate,unsigned char DateLen)
{                     //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   unsigned char BackDate,i;
   CSN_dir=1;
   CSN=0;
   BackDate=NRFSPI(RegAddr);    //д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)       //д������
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF����Ϊ����ģʽ����������******************************/
void NRFSetTxMode(unsigned char *TxDate)
{    //����ģʽ
    CSN_dir=1;
    CE=0; 
    NRFWriteReg(FLUSH_TX,0x00);      //*********
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//д�Ĵ���ָ��+���յ�ַʹ��ָ��+���յ�ַ+��ַ���
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
	  NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);   //д������ 
	/******�����йؼĴ�������**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);                // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);         // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);              // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);                // CRCʹ�ܣ�16λCRCУ�飬�ϵ�  
	CE=1;
  NRF_delay_5us();//����10us������
  NRF_delay_5us();
}
/*****************NRF����Ϊ����ģʽ����������******************************/
//��Ҫ����ģʽ
void NRFSetRXMode(void)
{
	  CE=0;
	  CSN_dir=1;  
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);                          // ʹ�ܽ���ͨ��0�Զ�Ӧ��
    NRFWriteReg(FLUSH_RX,0x00);      //*********
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);                      // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                          // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);              // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);                       // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������*/
  	NRFWriteReg(W_REGISTER+CONFIG,0x0f);                         // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
  	CE = 1;
    NRF_delay_5us();                                              //����10us������ 
    NRF_delay_5us();
    NRF_delay_5us();
    NRF_delay_5us();
    NRF_delay_5us();     
}
/****************************���Ӧ���ź�******************************/
unsigned char CheckACK(void)
{                                                       //���ڷ��� 
  CSN_dir=1;
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if((sta&0x20)||(sta&0x10))  //    TX_DS||MAX_RT                              //��������ж�
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);               // ���TX_DS��MAX_RT�жϱ�־
	   CSN=0;
	   //NRFSPI(FLUSH_TX);                                //�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
      NRFWriteReg(FLUSH_TX,0x00);      //*********
     //NRFSPI(0x00);                  //*******************
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}

/*************************��������*********************************************/
void GetDate(unsigned char *Rece)				 
{
    sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
    if(sta & 0x40)				// �ж��Ƿ���յ�����
     {
	   CE=0;//����
	   NRFReadRxDate(R_RX_PAYLOAD,Rece,RX_DATA_WITDH);// ��RXFIFO��ȡ���� ����4λ���ɣ���һλλ����λ
	   //NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	   CSN=0;
	   //NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	   NRFWriteReg(FLUSH_RX,0x00);      //*********
	   //NRFSPI(0x00);   //****************************
	   CSN=1;		 
     }
    NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�	  
}