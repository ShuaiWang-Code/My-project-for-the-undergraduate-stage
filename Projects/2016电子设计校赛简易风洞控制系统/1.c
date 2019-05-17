//******************************************************************************
//头文件
#include <reg52.h>     //包括一个52标准内核的头文件
#include "nokia_5110.h"
#include "bmp_pixel.h"
//******************************************************************************
//宏定义
#define uchar unsigned char //定义一下方便使用
#define uint  unsigned int
#define ulong unsigned long
#define delay_time	25767
//*******************************************************************************************
//special IO_sfr
sfr   P0M1   = 0X93;
sfr   P0M0   = 0X94;
sfr   P1M1   = 0X91;
sfr   P1M0   = 0X92;
sfr	  P2M1   = 0X95;
sfr	  P2M0   = 0X96;
//********************************************************************************
//定义引脚
sbit Trig  = P1^0; //产生脉冲引脚
sbit Echo  = P3^2; //回波引脚
sbit PWM=P1^1;
sbit IN1=P1^3;
sbit IN2=P1^4;		  //电机
sbit D1=P3^3;
sbit D2=P3^4;
sbit D3=P3^5;
sbit D4=P3^6;
//*******************************************************************************************
//标志位
bit succeed_flag;  //测量成功标志
bit flag_model1=0,flag_sheding=0,flag_model2=0,flag_model3=0,flag_warning;  //model flag
//*******************************************************************************************
//计数时间变量
unsigned int timer1,intr=130,intr1=170,intr2=115;		//定时器计数标志、PWM波大小
unsigned int timer2,shijian=0;							//时间
unsigned int distance_data,a,b,tt,height=24;						//超生波变量
unsigned char ge,shi,bai,temp,flag,outcomeH,outcomeL,i,ge_data;
unsigned char shi_data,bai_data,CONT_1,gaodu,sheding=0;          //自定义寄存器
int set,error,error_last,juli=25,juli1=24,cishu=0;		  //feedback 变量
float k=1;												  //feedback 参数
//***************************************************************************************
//函数声明
void LCD_display(unsigned int num);				 //display_distance
void LCD_display_pwm(unsigned int nu);			 //display_time
void Delay10ms(unsigned int c);					 //
void delay_20us();								 //delay
void KeyDown(void);								 //keyscan
void pwm_generate(unsigned int changdu);		 //pwm_generate
void time_generate(unsigned int tg);             //time_generate
void model_select();							 //model_select
void model_display();
void ultrasonic_wave_generate();				 //ultrasonic wave
void interface();                                //interface
void io_init();									 //io_init
void motor_init();								 //motor
void timer_init();								 //timer_init
//********************************************************************************
void main(void)   // 主程序
{   
    LCD_init(); 								//初始化液晶 
	interface();  								//界面
	io_init();    								//io设为推挽
	motor_init();  								//电机初始化
	timer_init(); 								//定时器初始化
	PID_init();	   								//PID初始化
	while(1)         							//程序循环
	{	
		model_display();					 	//model显示
		ultrasonic_wave_generate();			 	//超声波产生
	}
}

//****************************************************************
timer0() interrupt 1  // 定时器0中断是1号
  { 
	TL0 = 0x23;		                            //设置定时初值
	TH0 = 0xFF;		         					//设置定时初值  
	timer1++;			     					//PWM计数标志
	timer2++;			    					//时间计数标志
	pwm_generate(intr);		 					//PWM产生	 
	KeyDown();			     					//键盘扫描	
	time_generate(5000);  	 					//time产生
	model_select();			 					//model选择	  （PID）
					     
} 
//******************************************************************
//DISPLAY子函数
void LCD_display(unsigned int num)							//显示距离
{
 	unsigned char str[2];
	if(num>=22)
	{
		num=num-22;
		LCD_write_english_string(52,0,"+"); 
	}
	else
	{	
		num=22-num;
		LCD_write_english_string(52,0,"-"); 
	}
  	str[0]=(num%100)/10 + 0x30;  
  	str[1]=num%10 + 0x30;
 	LCD_write_english_string(58,0,(char *)str); 
	LCD_write_english_string(70,0,"cm");
}
void LCD_display_pwm(unsigned int nu)						 //显示时间
{
 	unsigned char str1[2];
    str1[0]=(nu%100)/10 + 0x30;  
    str1[1]=nu%10 + 0x30;
 	LCD_write_english_string(54,2,(char *)str1);
	LCD_write_english_string(66,2,"sec"); 
}
//******************************************************************
//延时函数
void Delay10ms(unsigned int c)   //误差 0us
{
    unsigned char aa, bb;
	//--c已经在传递过来的时候已经赋值了，所以在for语句第一句就不用赋值了--//
    for (;c>0;c--)
	{
		for (bb=38;bb>0;bb--)
		{
			for (aa=130;aa>0;aa--);
		}          
	}       
}
void delay_20us()
{  uchar bt ;
    for(bt=0;bt<100;bt++);
}
//******************************************************************
//PWM产生
void pwm_generate(unsigned int changdu)
{
	 if(timer1>500)  //PWM周期
	 {
		timer1=0;
	 }	
	 if(timer1 < changdu)	//改变这个值可以改变直流电机的速度
	 {
		PWM=1;
     }
	 else
	 {
		PWM=0;
	 }
}
//******************************************************************
//time_generate
void time_generate(unsigned int tg)
{
	 if(timer2>tg)
	 {
	 	timer2=0;
		shijian=shijian+1;
//		flag_warning=~flag_warning;
	 }
	 if(timer2>(tg/2))
	 {
	 	 flag_warning=~flag_warning;
	 }
}
//******************************************************************
//model select
void model_select()
{
	 if(flag_model1==0 && flag_model2==0 &&flag_model3==0)
	 {	
	 	if(shijian<1)
		{
	 		intr=intr1;
		}

	 	if(shijian>2)	   //12
	 	{
        	PID_realize(juli1,intr2);	   
	 	}

	 }

	 if(flag_model2==1)									  //flag_model2
	 {
		if(shijian>2)
		{
			PID_realize(12,119);
		}
		
		if(shijian>10)
		{
			PID_realize(34,115);
		}

		if(shijian>18)
	 	{
	 		shijian=0;
			cishu++;
				
			if(cishu==2)
			{
				intr=480;
				cishu=0;
			}
	 	}

	 }	
}
//******************************************************************
//model_show
void model_display()
{
	 if(b<51)
	 {
	  	LCD_display(50-b);							 //显示距离
	 
		if(50-b<20)									 //显示区域
		{
			LCD_write_english_string(56,4,"CD"); 
			if(b>35)
			{
			 D1=0;
			 D2=0;
			 D3=0;
			 D4=1;
			}
		}

		if(50-b>=20 && 50-b<=30)
		{
			LCD_write_english_string(56,4,"BC");
			D1=0; 
			D2=0;
			D3=1;
			D4=0;
		}

		if(50-b>30)
		{
			 LCD_write_english_string(56,4,"AB"); 
			 if(flag_warning==1)
			 {
			 	D1=1;
			 }
			 else
			 {
			 	D1=0;
			 }
			 D2=1;
			 D3=0;
			 D4=0;
		}
	 }
	 if(flag_model1==0 && flag_model2==0 &&flag_model3==0)	 //model 0
	 {	 
	 	if(shijian>7)
		{
		LCD_display_pwm(shijian-7);
		}
	 }
		
	 if(flag_model1==1)										  //model1
	 {	 	
		if(shijian>3)
		{
			LCD_display_pwm(shijian-3);
		}
	 }

     if(flag_model3==1)										  //model3
	 {	 
		if(b<6)
		{
			IN2=0;
			flag_model3=0;
			shijian=0;
		}			
	 }

	 if(flag_model2==1)									     //model2
	 {
		if(shijian>5)
			LCD_display_pwm(shijian-5);
	    
		if(shijian>12)
			LCD_display_pwm(shijian-12);
	 }
}
//******************************************************************
//超声波
void ultrasonic_wave_generate()
{
		Trig=1;
        delay_20us();
        Trig=0;         //产生一个20us的脉冲，在Trig引脚  
      	while(Echo==0); //等待Echo回波引脚变高电平
		succeed_flag=0; //清测量成功标志
	 	TH1=0;          //定时器1清零
        TL1=0;          //定时器1清零
	    TF1=0;          //
        TR1=1;          //启动定时器1
      	while(!Echo==0);//等待测量的结果，周期65.535毫秒（可用中断实现）  
		{
			TR1=0;          //关闭定时器1
			outcomeH =TH1;    //取出定时器的值
        	outcomeL =TL1;    //取出定时器的值
        	succeed_flag=1;   //至成功测量的标志
		}
        if(succeed_flag==1)
	    { 	
		   distance_data=outcomeH;                //测量结果的高8位
           distance_data<<=8;                   //放入16位的高8位
		   distance_data=distance_data|outcomeL;//与低8位合并成为16位结果数据
           distance_data/=58;                   //微秒的单位除以58等于厘米
        }                                      //为什么除以58等于厘米，  Y米=（X秒*344）/2
			                                       // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58 
	   a=distance_data;

       if(b==a) CONT_1=0;

       if(b!=a) CONT_1++;

       if(CONT_1>=3)
	   {   
	       CONT_1=0;
		   b=a;	
		   		   
	   } 
}
//******************************************************************
//interface
void interface()
{
	LCD_write_chinese_string(12,0,12,3,0,5);  	 //显示界面汉子
	LCD_write_chinese_string(12,2,12,3,3,5);  
	LCD_write_chinese_string(12,4,12,3,8,5);
}
//******************************************************************
//IO_INIT
void io_init()
{
	P0M1 = 0;   //将io口设置为推挽输出
    P1M1 = 0;
    P2M1 = 0;
    P0M0 = 0XFF;
    P1M0 = 0XFF;
    P2M0 = 0XFF;
	D1=0;
	D2=0;
	D3=0;
	D4=0;
}
//******************************************************************
//motor_init
void motor_init()
{
	IN1=1;		 //电机
	IN2=0;
    i=0;
    flag=0;
	Trig=0;       //首先拉低脉冲输入引脚
}
//******************************************************************
//timer_init
void timer_init()
{
	TMOD=0x11;    //定时器0，定时器1，16位工作方式
	TR0=1;	     //启动定时器0
    IT0=0;        //由高电平变低电平，触发外部中断
	ET0=1;        //打开定时器0中
	EX0=0;        //关闭外部中断
	EA=1;         //打开总中断0	
}
//******************************************************************
void KeyDown(void)											 //键盘扫描
{
	uchar temp;
    P0=0xf7;
    temp=P0;
    temp=temp&0xF0;

    if(temp!=0xF0)
	{
        Delay10ms(1);
        temp=P0;
 		temp=temp&0xF0;
 		
		if(temp!=0xF0)
 		{
 			temp=P0;
 			switch(temp)
 			{
 			case 0Xe7:								   //model1
 					flag_model2=0;
					flag_model1=1;
					flag_model3=0;
					PID_realize(7,150);
					shijian=0;
 			break;

			case 0Xd7:								  //model2
 		 			flag_model1=0;
					flag_model2=1;
					flag_model3=0;
					PID_realize(10,125);
					shijian=0;
 			break;

 			case 0xb7:									//model3
 		 			flag_model1=0;
					flag_model2=0;
					flag_model3=1;
					shijian=0;
					intr1=400;
					IN2=1;
 			break;
//
 			case 0x77:									//model1
 					flag_model2=0;
					flag_model1=1;
					flag_model3=0;
					PID_realize(7,150);
					shijian=0;
 			break;

 			}
 			while(temp!=0xf0)
 			{			
 			temp=P0;
  			temp=temp&0xf0;
 			}
 		}
 	}

		P0=0xFB;
		temp=P0;
		temp=temp&0xF0;
		
        if(temp!=0xF0)
		{
 			Delay10ms(1);
 			temp=P0;
 			temp=temp&0xF0;
 			
			if(temp!=0xF0)
 			{
 				temp=P0;
 				switch(temp)
 				{
 					case 0XEB:
			  					juli1=22;
								intr2=116; //7
 								shijian=0;

								break;

 					case 0xDB:
								juli1=20;
								intr2=116; 		   //8
 								shijian=0;
 								
								break;
											   //9
 					case 0xBB:
								juli1=17;
								intr2=116; 
								shijian=0;
 								
								break;

 					case 0x7B:
								juli1=20;
								intr2=125; 
								shijian=0;
								
								break;

 				}
 				while(temp!=0xf0)
 				{
 						temp=P0;
  					temp=temp&0xf0;
 				}
 			}
 		}

		P0=0xfd;
		temp=P0;
		temp=temp&0xF0;
		
        if(temp!=0xF0)
      {
	 		Delay10ms(1);
 			temp=P0;
 			temp=temp&0xF0;
 
			if(temp!=0xF0)
 			{
 				temp=P0;
 				switch(temp)
 				{
 					case 0XED:
								juli1=24;
								intr2=114; 				//4
 								shijian=0;
 								
								break;

 					case 0xDD:						 //5
 								juli1=21;
								intr2=114; 
								shijian=0;
 								
								break;

					case 0xBD:
								juli1=22;
								intr2=115; 					 //6
								shijian=0;
 							
								break;

 					case 0x7D:
						flag_model1=1;
 					shijian=0;
 					break;

 					}
 					while(temp!=0xf0)
 					{
 						temp=P0;
  					temp=temp&0xf0;
 					}
 				}
 			}

		P0=0xFE;
		temp=P0;
		temp=temp&0xF0;
		
		if(temp!=0xF0)
		{
 			Delay10ms(1);
 			temp=P0;
 			temp=temp&0xF0;
 			
			if(temp!=0xF0)
 			{
 				temp=P0;
 				switch(temp)
 				{
 					case 0XEE:					//1
					  			juli1=27;
								intr2=113;
								shijian=0;

 								break;

 					case 0xDE:
								juli1=25;
								intr2=113;
								shijian=0;		 //2
					
								break;

 					case 0xBE:
								juli1=25;
								intr2=114;
								shijian=0;				//3
 					
 								break;

 					case 0x7E:
								flag_model1=1;
 								shijian=0;
					break;

 				}
 					while(temp!=0xf0)
 					{
 						temp=P0;
  					temp=temp&0xf0;
 					}
 				}


		  }

}
