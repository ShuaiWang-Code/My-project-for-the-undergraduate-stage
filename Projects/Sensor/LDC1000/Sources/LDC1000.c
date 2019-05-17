#include "LDC1000.H"
#define NN  20
unsigned char orgVal[12]={0};
unsigned char RPMAX =0x07; 
unsigned char RPMIN =0x2f;
unsigned char RFREQ =0xA9;
unsigned char rpi_max=10;
unsigned char proximtyData[2]={0};
unsigned long proximtyDataTEMP=0,proximtyDataMAX,proximtyDataMIN,proximtyDataSUM,proximtyDataAVE,proximtyDataAVE_LAS;

int LDC_val=0;

unsigned long value_buf[NN],new_value_buf[NN];

void FLOAT_delay_us(int ms)//为防止time_delay_ms();与lpt冲突编写的延时
{
  int j1,k_1;int i1;
  i1=ms;
  for(j1=0;j1<i1;j1++)   
    for(k_1=0;k_1<8;k_1++);
}
void FLOAT_LDC_init()
{
      while(orgVal[1]!=RPMAX||orgVal[2]!=RPMIN||orgVal[3]!=RFREQ)//一旦在此循环说明初始化不成功
      {  
         FLOAT_SPI_init();   
         FLOAT_delay_us(3000);
         FLOAT_Singal_SPI_Write(LDC1000_CMD_RPMAX, RPMAX);
         FLOAT_Singal_SPI_Write(LDC1000_CMD_RPMIN, RPMIN);//0x14
         FLOAT_Singal_SPI_Write(LDC1000_CMD_SENSORFREQ,  RFREQ);  //谐振频率计算方法见《浮点科技电轨传感器调试手册》
         FLOAT_Singal_SPI_Write(LDC1000_CMD_LDCCONFIG,   0x17);  /********/
         FLOAT_Singal_SPI_Write(LDC1000_CMD_CLKCONFIG,   0x00);  //L配置LDC1000的输出速率
         FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESHILSB,  0x50);  /********/
      	 FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESHIMSB,  0x14);
      	 FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESLOLSB,  0xC0);
      	 FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESLOMSB,  0x12);
         FLOAT_Singal_SPI_Write(LDC1000_CMD_INTCONFIG,   0x02);
         FLOAT_Singal_SPI_Write(LDC1000_CMD_PWRCONFIG,   0x01);
         
         FLOAT_SPI_Read_Buf(LDC1000_CMD_REVID,&orgVal[0],12);//orgVal[]对应上面写入的值说明初始化正常
       
      }
} 

int ldc_read_avr()
{

    char rpi=0;  //取rpi次平均值    
    for (rpi=0;rpi<rpi_max;rpi++)
    {

      FLOAT_SPI_Read_Buf(LDC1000_CMD_PROXLSB,&proximtyData[0],2);  
      proximtyDataTEMP = ((unsigned char)proximtyData[1]<<8) + proximtyData [0]; 
      proximtyDataSUM += proximtyDataTEMP;
      if (proximtyDataTEMP < proximtyDataMIN)   //在100个proximtyDataTEMP中取最大，最小
        proximtyDataMIN = proximtyDataTEMP;
      if (proximtyDataTEMP > proximtyDataMAX)
        proximtyDataMAX = proximtyDataTEMP;
    }
     proximtyDataAVE = proximtyDataSUM /rpi_max;
     proximtyDataSUM=0;
     proximtyDataAVE_LAS=proximtyDataAVE;
  
    return   proximtyDataAVE; 

}
long int filter()
{
   char count,i,j,count1;
   char count2=0;
 
   long int temp;
   long int sum=0;
   for(count=0;count<NN;count++)
   {
      value_buf[count] = ldc_read_avr();
   }
   
   for(count1=0;count1<NN;count1++)
   {  
   if(value_buf[count1]<32768)
   {
   new_value_buf[count2]=value_buf[count1];
   count2++;
   }  
   }
   
   
   for (j=0;j<count2-1;j++)
   {
      for (i=0;i<count2-j;i++)
      {
        if ( new_value_buf[i]>new_value_buf[i+1] )
         {
            temp = new_value_buf[i];
            new_value_buf[i] = new_value_buf[i+1];
            new_value_buf[i+1] = temp;
         }
      }
   }

   for(count=1;count<count2-1;count++)
   {
      sum += new_value_buf[count];
   }
  
     
   return (long int)(sum/(count2-2));


}

void FLOAT_SPI_init()
{  
       
        DDRA=0x0E;//MISO
        // gpio_init (PTD1 ,GPO,1);//MOSI
       //  gpio_init (PTD2, GPO,1);// CSN
       //  gpio_init (PTD3, GPO,0);//SCK
         
         CSN_H;
         SCK_L;
         MOSI_H;
         
  
}

unsigned char FLOAT_SPI_RW(unsigned char rwdata)
{  
    
	unsigned char spi_rw_i=0;	
        unsigned char temp=0;
        for(spi_rw_i=0;spi_rw_i<8;spi_rw_i++)   	// output 8-bit
   	{
   	        /*** prepare the write data of read before the coming of rising up******/
	          if(rwdata & 0x80)
                    MOSI_H;
   		  else 
                    MOSI_L;
   		  rwdata<<=1;           		// shift next bit to MSB
                  temp<<=1;
		SCK_H;             //Set SCK high    Rising up 
               
   		if(MISO) 
                  temp|=1;
   		SCK_L;            //set  SCK low     Falling down
                
   	}
    return(temp);           		  		// return read byte
    
 
}

unsigned char FLOAT_Singal_SPI_Read(unsigned char reg)
{
	unsigned char rdata;
	
	CSN_L;                        // CSN low, initialize SPI communication...
       
        FLOAT_delay_us(2);
         
         reg=reg|0x80;         //read com
	FLOAT_SPI_RW(reg);            // Select register to read from..
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         
	rdata = FLOAT_SPI_RW(0);    // then read registervalue
       
        FLOAT_delay_us(1700);
	CSN_H;                 // CSN high, terminate SPI communication
	
	return rdata;         // return register value
}

void FLOAT_Singal_SPI_Write(unsigned char reg,unsigned char wdata)
{
	
	CSN_L;                // CSN low, initialize SPI communication...
      
        FLOAT_delay_us(2);//2us
        reg=reg&~0x80;
	    FLOAT_SPI_RW(reg);            // Select register to read from..
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
         asm("nop");
        
	FLOAT_SPI_RW(wdata);    // ..then read registervalue
        FLOAT_delay_us(1700);//875us
	CSN_H;              // CSN high, terminate SPI communication
       
	
}


void FLOAT_SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char len)
{
	unsigned char spi_rw_i;
	
	CSN_L;                   		// Set CSN low, init SPI tranaction
       
        reg=reg|0x80;                            //read
	FLOAT_SPI_RW(reg);       		// Select register to write to and read status unsigned char
	
	for(spi_rw_i=0;spi_rw_i<len;spi_rw_i++)
        {  
	pBuf[spi_rw_i] = FLOAT_SPI_RW(0);    
	 }
	CSN_H;     
       

}