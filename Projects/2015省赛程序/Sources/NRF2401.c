/*****************************************
创建：陈志强
时间：2010.6.12
功能：NRF24L01射频模块C文件(节点发射部分)
*****************************************/
#include "MC9S12XS128.h"

#include "NRF2401.h"
#define  CE    PORTA_PA0  //3      //RX/TX模式选择端
#define  SCLK  PORTA_PA2 	//5      //SPI时钟端
#define  MISO  PORTA_PA4 	//7      //SPI主机输出从机输出端

#define  CSN   PORTA_PA1  //4      //SPI片选端//就是SS
#define  MOSI  PORTA_PA3 	//6      //SPI主机输出从机输入端
#define  IRQ   PORTA_PA5  //8      //可屏蔽中断端

#define  CE_dir    DDRA_DDRA0       
#define  IRQ_dir   DDRA_DDRA1       
#define  CSN_dir   DDRA_DDRA2       
#define  MOSI_dir  DDRA_DDRA3  	      
#define  MISO_dir  DDRA_DDRA4 	      
#define  SCLK_dir  DDRA_DDRA5	     


unsigned char  TxAddr[]={0x34,0x43,0x10,0x10,0x01};//发送地址
/*****************状态标志*****************************************/
unsigned char  sta;   //状态标志

// #define   RX_DR     (( sta & 0x40 ) >>6 )
// #define   TX_DS     (( sta & 0x20 ) >>5 )
// #define   MAX_RT    (( sta & 0x10 ) >>4 )

/*********************    延时函数    *********************************/
void NRF_delay_5us(void)
{
   unsigned int  i;
   for(i=0;i<1080;i++);
}

/*****************SPI时序函数******************************************/
unsigned char NRFSPI(unsigned char date)
{
    unsigned char i;
     
    MOSI_dir=1;
    MISO_dir=0;
    SCLK_dir=1;
  //  SCLK=1; 
   	for(i=0;i<8;i++)          // 循环8次
   	{
	  if(date&0x80)
	    MOSI=1;
	  else
	    MOSI=0;                 // byte最高位输出到MOSI
   	  date<<=1;               // 低一位移位到最高位
   	  SCLK=1; 
	  if(MISO)                  // 拉高SCK，nRF24L01从MOSI读入1位数据，同时从MISO输出1位数据
   	    date|=0x01;       	  // 读MISO到byte最低位
   	  SCLK=0;            	    // SCK置低
   	}
    return(date);           	// 返回读出的一字节
}
/**********************NRF24L01初始化函数*******************************/
void NRF24L01Int(void)
{
  CE_dir=1;   
	CSN_dir=1;  
	SCLK_dir=1;
	IRQ_dir=1;
	
	NRF_delay_5us();        //让系统什么都不干
	CE=0;                   //待机模式1   
	CSN=1;  
	SCLK=0;
	IRQ=1;	 
}
/*****************SPI读寄存器一字节函数*********************************/
unsigned char NRFReadReg(unsigned char RegAddr)
{
   unsigned char BackDate;
   CSN_dir=1;
   CSN=0;                    //启动时序
   NRFSPI(RegAddr);          //写寄存器地址
   BackDate=NRFSPI(0x00);    //写入读寄存器指令  
   CSN=1;
   return(BackDate); //返回状态
}
/*****************SPI写寄存器一字节函数*********************************/
unsigned char NRFWriteReg(unsigned char RegAddr,unsigned char date)
{
   unsigned char BackDate;
   CSN_dir=1;
   CSN=0;                         //启动时序
   BackDate=NRFSPI(RegAddr);      //写入地址
   NRFSPI(date);                  //写入值
   CSN=1;
   return(BackDate);
}
/*****************SPI读取RXFIFO寄存器的值********************************/
unsigned char NRFReadRxDate(unsigned char RegAddr,unsigned char *RxDate,unsigned char DateLen)
{                           //寄存器地址//读取数据存放变量//读取数据长度//用于接收
    unsigned char BackDate,i;
    CSN_dir=1;
	   CSN=0;                    //启动时序
  	BackDate=NRFSPI(RegAddr);  //写入要读取的寄存器地址
	  for(i=0;i<DateLen;i++)     //读取数据
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPI写入TXFIFO寄存器的值**********************************/
unsigned char NRFWriteTxDate(unsigned char RegAddr,unsigned char *TxDate,unsigned char DateLen)
{                     //寄存器地址//写入数据存放变量//读取数据长度//用于发送
   unsigned char BackDate,i;
   CSN_dir=1;
   CSN=0;
   BackDate=NRFSPI(RegAddr);    //写入要写入寄存器的地址
   for(i=0;i<DateLen;i++)       //写入数据
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF设置为发送模式并发送数据******************************/
void NRFSetTxMode(unsigned char *TxDate)
{    //发送模式
    CSN_dir=1;
    CE=0; 
    NRFWriteReg(FLUSH_TX,0x00);      //*********
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//写寄存器指令+接收地址使能指令+接收地址+地址宽度
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//为了应答接收设备，接收通道0地址和发送地址相同
	  NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);   //写入数据 
	/******下面有关寄存器配置**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);                // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // 使能接收通道0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);         // 自动重发延时等待250us+86us，自动重发10次
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);              // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);                // CRC使能，16位CRC校验，上电  
	CE=1;
  NRF_delay_5us();//保持10us秒以上
  NRF_delay_5us();
}
/*****************NRF设置为接收模式并接收数据******************************/
//主要接收模式
void NRFSetRXMode(void)
{
	  CE=0;
	  CSN_dir=1;  
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // 接收设备接收通道0使用和发送设备相同的发送地址
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);                          // 使能接收通道0自动应答
    NRFWriteReg(FLUSH_RX,0x00);      //*********
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);                      // 使能接收通道0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                          // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);              // 接收通道0选择和发送通道相同有效数据宽度
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);                       // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益*/
  	NRFWriteReg(W_REGISTER+CONFIG,0x0f);                         // CRC使能，16位CRC校验，上电，接收模式
  	CE = 1;
    NRF_delay_5us();                                              //保持10us秒以上 
    NRF_delay_5us();
    NRF_delay_5us();
    NRF_delay_5us();
    NRF_delay_5us();     
}
/****************************检测应答信号******************************/
unsigned char CheckACK(void)
{                                                       //用于发射 
  CSN_dir=1;
	sta=NRFReadReg(R_REGISTER+STATUS);                    // 返回状态寄存器
	if((sta&0x20)||(sta&0x10))  //    TX_DS||MAX_RT                              //发送完毕中断
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);               // 清除TX_DS或MAX_RT中断标志
	   CSN=0;
	   //NRFSPI(FLUSH_TX);                                //用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！  
      NRFWriteReg(FLUSH_TX,0x00);      //*********
     //NRFSPI(0x00);                  //*******************
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}

/*************************接收数据*********************************************/
void GetDate(unsigned char *Rece)				 
{
    sta=NRFReadReg(R_REGISTER+STATUS);//发送数据后读取状态寄存器
    if(sta & 0x40)				// 判断是否接收到数据
     {
	   CE=0;//待机
	   NRFReadRxDate(R_RX_PAYLOAD,Rece,RX_DATA_WITDH);// 从RXFIFO读取数据 接收4位即可，后一位位结束位
	   //NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标
	   CSN=0;
	   //NRFSPI(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
	   NRFWriteReg(FLUSH_RX,0x00);      //*********
	   //NRFSPI(0x00);   //****************************
	   CSN=1;		 
     }
    NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标	  
}