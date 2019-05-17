#include "main.h"


/*************************************************************************
//功    能：完成SCI0模块初始化
//入口参数：无
//出口参数：无
*************************************************************************/
void SCI0_Init(void)
{
    SCI0BD = 52;					//设置波特率为9 600 bps 
    SCI0CR1 = 0x00;      		//LOOPS=0,SCISWAI=0,RSRC=0,M=0,
	                   	 		//WAKE=0,ILT=0,PE=0,PT=0 	
    SCI0CR2 = 0x0C;				//TIE=0,TCIE=0,RIE=0,ILIE=0,
	                   	 		//TE=1,RE=1,RWU=0,SBK=0
}

/*************************************************************************
//功    能：完成短时间延时
//入口参数：无
//出口参数：无
*************************************************************************/
void delay(void)
{
    unsigned int loop_i, loop_j;    
    for (loop_i=0; loop_i< 500; loop_i++) 
    {
        for (loop_j=0; loop_j<500;loop_j++) 
        {
            ;
        }
    }
}

/*************************************************************************
//功    能：通过SCI0模块连续发送0～99
//入口参数：无
//出口参数：无
*************************************************************************/
void main(void) 
{
    unsigned char loop_index;				//定义循环变量
    
    SCI0_Init();

for(loop_index=0; loop_index<100; loop_index++)
{
    while(!SCI0SR1_TDRE);            			//等待发送缓冲区空        
	   SCI0DRL = loop_index;				//发送数据
    delay();
}
    while(1)
    {
        ;
    } 
}
