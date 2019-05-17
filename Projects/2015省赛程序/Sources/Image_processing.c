#include "main.h"
#define ROW     39          //定义图像采集行数：40行
#define COLUMN  120         //定义图像采集列数：120列
#define  THRESHOLD 100 //黑白二值化图像阈值(经验值，随环境光变换而变化)
#define  mid 59 //图像中心列


 extern  unsigned char left_line[ROW];    //左边界
extern unsigned char right_line[ROW];    //右边界
extern unsigned char center_line[ROW];//赛道中心数组

//unsigned char zhongxin_line[ROW];

int zhongxin_dian=0,danxian_flag=0 ,danxian_flag1=0, za;

extern int  zw_row,error_duoj,error1_duoj,error2_duoj,xlv_error;//舵机偏差变量
extern int left_point,right_point,center_point,left_point1,right_point1,center_point1,left_flag,right_flag; //采集的一行中提取的左右两条黑线

 //  unsigned char leftqipaoxiancout,LightDifferentia;
extern unsigned char Image_Data[39][120];    //图像数组
//float yuzhi=100; 
   volatile unsigned char biaozhicount=0,biaozhiflag=0,biaozhiflag1=0,biaozhiline=0;
 //   unsigned char leftcount=0,rightcount=0;
//extern volatile  float OutData[4];//全局变量输出数据
//extern int zhizou_falg1,zhizou_falg2;

unsigned char zhonxin_line1[ROW];    //中心线

unsigned char left_line1[ROW];    //左边界
unsigned char right_line1[ROW];    //右边界
unsigned char center_line1[ROW];   //赛道中心数组

   volatile unsigned char left_edge=0,right_edge=0,zhangaiflag=0;    //障碍
 
 
 
 
 //延时**********************************************
  void delay(int d)


{    int b,c;
    for(b=0;b<6400;b++)
      for(c=0;c<d;c++) ;
      


}

//s延时**********************************************
 /*
void delay_s(int c)

{
   int e=0,f=0;
   
   
   
   for(e=0;e<6500;e++)
      for(c=0;c<1000;f++);
      
   



}


    */

 //直角标志********************************************************
void get_zhijiao_flag(void)

{
  int b=8,lie=0;
 
 
// if(error_duoj>-10&&error_duoj<10) 
// {
     
   if(Image_Data[b][50]>=THRESHOLD&&Image_Data[b][60]>=THRESHOLD&&Image_Data[b][70]>=THRESHOLD&&
      Image_Data[b+3][50]<=THRESHOLD&&Image_Data[b+3][60]<=THRESHOLD&&Image_Data[b+3][70]<=THRESHOLD&&
      Image_Data[b+5][50]<=THRESHOLD&&Image_Data[b+5][60]<=THRESHOLD&&Image_Data[b+5][70]<=THRESHOLD&&
      Image_Data[b+9][50]>=THRESHOLD&&Image_Data[b+9][60]>=THRESHOLD&&Image_Data[b+9][70]>=THRESHOLD) 
       
     {
     
       biaozhiflag=1;
       // PTM_PTM0=1;
     }
// } 
// else if(error_duoj<=-10) 
 
// {
  
  
   if(Image_Data[b][10]>=THRESHOLD&&Image_Data[b-4][20]>=THRESHOLD&&Image_Data[b-8][30]>=THRESHOLD&&
      Image_Data[b+3][10]<=THRESHOLD&&Image_Data[b-1][20]<=THRESHOLD&&Image_Data[b-5][30]<=THRESHOLD&&
      Image_Data[b+5][10]<=THRESHOLD&&Image_Data[b+1][20]<=THRESHOLD&&Image_Data[b-3][30]<=THRESHOLD&&
      Image_Data[b+9][10]>=THRESHOLD&&Image_Data[b+5][20]>=THRESHOLD&&Image_Data[b+1][30]>=THRESHOLD) 
       
     {
     
       biaozhiflag=1;
       // PTM_PTM0=1;
     }
    if(Image_Data[b][110]>=THRESHOLD&&Image_Data[b-4][100]>=THRESHOLD&&Image_Data[b-8][90]>=THRESHOLD&&
      Image_Data[b+3][110]<=THRESHOLD&&Image_Data[b-1][100]<=THRESHOLD&&Image_Data[b-5][90]<=THRESHOLD&&
      Image_Data[b+5][110]<=THRESHOLD&&Image_Data[b+1][100]<=THRESHOLD&&Image_Data[b-3][90]<=THRESHOLD&&
      Image_Data[b+9][110]>=THRESHOLD&&Image_Data[b+5][100]>=THRESHOLD&&Image_Data[b+1][90]>=THRESHOLD) 
       
     {
     
       biaozhiflag=1;
       // PTM_PTM0=1;
     }
 
 
 //} 
// else if(error_duoj>=10) 
 
// {
   if(Image_Data[b][10]>=THRESHOLD&&Image_Data[b+4][20]>=THRESHOLD&&Image_Data[b+8][30]>=THRESHOLD&&
      Image_Data[b+3][10]<=THRESHOLD&&Image_Data[b+7][20]<=THRESHOLD&&Image_Data[b+11][30]<=THRESHOLD&&
      Image_Data[b+5][10]<=THRESHOLD&&Image_Data[b+9][20]<=THRESHOLD&&Image_Data[b+13][30]<=THRESHOLD&&
      Image_Data[b+9][10]>=THRESHOLD&&Image_Data[b+13][20]>=THRESHOLD&&Image_Data[b+17][30]>=THRESHOLD) 
       
     {
     
       biaozhiflag=1;
      
     }  
 
     if(Image_Data[b][110]>=THRESHOLD&&Image_Data[b+4][100]>=THRESHOLD&&Image_Data[b+8][90]>=THRESHOLD&&
      Image_Data[b+3][110]<=THRESHOLD&&Image_Data[b+7][100]<=THRESHOLD&&Image_Data[b+11][90]<=THRESHOLD&&
      Image_Data[b+5][110]<=THRESHOLD&&Image_Data[b+9][100]<=THRESHOLD&&Image_Data[b+13][90]<=THRESHOLD&&
      Image_Data[b+9][110]>=THRESHOLD&&Image_Data[b+13][100]>=THRESHOLD&&Image_Data[b+17][90]>=THRESHOLD) 
       
     {
     
       biaozhiflag=1;
      
     }  
 
// }  
      
  
 /* 
     for(lie = right_line[20]+2;lie > left_line[20]-2;lie--)
    {   
            for(hang=20;hang>1;hang--) 
            {
                if((Image_Data[hang][lie]==1&&Image_Data[hang-1][lie]==0)||(Image_Data[hang][lie]==0&&Image_Data[hang+1][lie]==1))
                   biaozhicount++;
            }
    }
    if(biaozhicount>=30) 
    {
        biaozhiline++;   
        biaozhicount = 0;
//        black_cnt = 0;
    } 
    else 
    {
        biaozhicount = 0;
//        black_cnt = 0;
    }
    if(biaozhiline>=1) 
    {
        biaozhiflag = 1;
        biaozhiline = 0;
    }
     
      */
     
     
 else
      
       {
       
          if(biaozhiflag==1&&biaozhiflag1==0)
    {
    
       // PTM_PTM0=1;
        biaozhiflag=0; 
        biaozhiflag1=1;
        
    } 
    
     if(biaozhiflag==1&&biaozhiflag1==1)
    {
    
        biaozhiflag1=0;
        biaozhiflag=0; 
        
      //  PTM_PTM0=0;
    } 
       
       }
      
      PTM_PTM0=biaozhiflag1;


}

      
  //直角，一行循迹********************************************************
 void zhijiao_xunji(void) 

{
    int hang=15,lie=0;
    int b=0,c=0;

for(lie=0;lie<60;lie++)//左点提取

  {
  
     if(Image_Data[hang][lie]<THRESHOLD&&Image_Data[hang][lie+1]<THRESHOLD&&Image_Data[hang][lie+2]<THRESHOLD&&
     Image_Data[hang][lie+3]>THRESHOLD&&Image_Data[hang][lie+5]>THRESHOLD&&Image_Data[hang][lie+7]>THRESHOLD) 
        {
           left_flag=0;
           left_point=lie+2;
           break;
        }
        
        
        
     else 
        { c=0;
          for(b=0;b<60;b++)
          
          {
            
            if(Image_Data[14][b]<THRESHOLD) c++;
        
          
          
           if(c<5)
           
           {
            
           left_flag=1;
           left_point=0;
           
           }
            else left_flag=0;
           
           
          }
          
          
          
          
          
          
        }
  }
  
  


for(lie=119;lie>59;lie--) //右点提取

  {
     if(Image_Data[hang][lie]<THRESHOLD&&Image_Data[hang][lie-1]<THRESHOLD&&Image_Data[hang][lie-2]<THRESHOLD&&
        Image_Data[hang][lie-3]>THRESHOLD&&Image_Data[hang][lie-5]>THRESHOLD&&Image_Data[hang][lie-7]>THRESHOLD) 
        {
           right_flag=0;
           right_point=lie-2;
            break;
        }
     else 
    {
           c=0;
          for(b=119;b>59;b--)
          
          {
             
            if(Image_Data[14][b]<THRESHOLD) c++;
        
          
          
           if(c<5)
           
           {
          right_point=119;  
          right_flag=1;
           } 
          
           else right_flag=0;
           
           
          }
    }
       
  
  }



      center_point=(left_point+right_point)/2;  //中点



} 





//障碍检测*******************************************************
 void zhangai_jiance(void)
 
 {
   int hang=24,lie=0,count=0;
     count=0;
    zhangaiflag=0;
   
   
   
   for(lie=0;lie<118;lie++)
   {
     if(ABS(Image_Data[hang][lie]-Image_Data[hang][lie+1])>80)  count++;
        
     if(count==2)      left_edge=lie+1;
     
     if(count==3)      right_edge=lie+1;
      
     if(count==4)      zhangaiflag=1;
        
   } 
   
   
   
   
  PTM_PTM2=zhangaiflag; 
   
   
   
   
   
   
           
 }

 //障碍***一行求中心点*******************************************************

 void zhangai(void)

{    uchar hang=24,lie=0;
  for(lie=59;lie>0;lie--)//左点提取
  
  {
      if(Image_Data[hang][lie]>THRESHOLD&&Image_Data[hang][lie-1]>THRESHOLD&&Image_Data[hang][lie-2]>THRESHOLD&&
        Image_Data[hang][lie-3]<THRESHOLD&&Image_Data[hang][lie-5]<THRESHOLD&&Image_Data[hang][lie-7]<THRESHOLD) 
        {
          
           right_point1=lie-2;
            break;
        }
  
  
  }

 for(lie=60;lie<120;lie++)//左点提取
  
  {
      if(Image_Data[hang][lie]>THRESHOLD&&Image_Data[hang][lie+1]>THRESHOLD&&Image_Data[hang][lie+2]>THRESHOLD&&
        Image_Data[hang][lie+3]<THRESHOLD&&Image_Data[hang][lie+5]<THRESHOLD&&Image_Data[hang][lie+7]<THRESHOLD) 
        {
          
           left_point1=lie+2;
            break;
        }
   
  
  }
  
   center_point1=(left_point1+right_point1)/2;  //中点

}






 /***************************************************************************************************
** 函数名称: zhongxinxian
** 功能描述:寻单线
** 说明:
        
***************************************************************************************************/
 
void zhongxinxian(void) 

{

   //     danxian_flag
   
   
   int hang=6,lie=0,hang1=8,b=0,c=0;
  
  
   
   for(lie=0;lie<120;lie++)   //寻单线
   
   {
   
   
   
       if((Image_Data[hang][lie-3]>=THRESHOLD)&&(Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie+1]<THRESHOLD)&&(Image_Data[hang][lie+2]<THRESHOLD)&&(Image_Data[hang][lie+3]<THRESHOLD)&&(Image_Data[hang][lie+6]>THRESHOLD)&&(Image_Data[hang][lie+7]>THRESHOLD)) 
       
       
               
                {
        
                     //zhongxin_dian = lie;
                   // danxian_flag=1;
                   b=1;
                     break;
                     
                     
                }
   
  
         else   b=0;         
   }
   
   for(lie=0;lie<120;lie++)
   
   {
   
   
   
       if((Image_Data[hang1][lie-3]>=THRESHOLD)&&(Image_Data[hang1][lie]>=THRESHOLD)&&(Image_Data[hang1][lie+1]<THRESHOLD)&&(Image_Data[hang1][lie+2]<THRESHOLD)&&(Image_Data[hang1][lie+3]<THRESHOLD)&&(Image_Data[hang1][lie+6]>THRESHOLD)&&(Image_Data[hang1][lie+7]>THRESHOLD)) 
       
       
               
                {
        
                     //zhongxin_dian = lie;
                     c=1;
                     break;
                     
                     
                }
   
  
         else   c=0;         
   }
        
      if(b==1&&c==1)
      
      {
         danxian_flag=1;
        
        
      } 
      else  danxian_flag=0;
      
      
       PTM_PTM1=danxian_flag;
      
      
      
   
   for(hang=0;hang<39;hang++)   //单线提取
   
   {
      for(lie=10;lie<109;lie++) 
      
      {
      
         if((Image_Data[hang][lie-3]>=THRESHOLD)&&(Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie+1]<THRESHOLD)&&(Image_Data[hang][lie+2]<THRESHOLD)&&(Image_Data[hang][lie+3]<THRESHOLD)&&(Image_Data[hang][lie+6]>THRESHOLD)&&(Image_Data[hang][lie+7]>THRESHOLD))
      
          zhonxin_line1[hang]=lie+2;
      }
   
   
   }
   
    for(hang=0;hang<38;hang++)   //单线滤波
   
   {
      for(lie=0;lie<119;lie++) 
      
      {
      
         if(zhonxin_line1[hang]>zhonxin_line1[hang+1]&&zhonxin_line1[hang]>zhonxin_line1[hang-1])
      
         zhonxin_line1[hang]=(zhonxin_line1[hang-1]+zhonxin_line1[hang+1])/2;
         
         if(zhonxin_line1[hang]<zhonxin_line1[hang+1]&&zhonxin_line1[hang]<zhonxin_line1[hang-1])
      
         zhonxin_line1[hang]=(zhonxin_line1[hang-1]+zhonxin_line1[hang+1])/2;
         
          
      }
   
   
   }
  
}
 
 
 
 /***************************************************************************************************
** 函数名称: Get_flag
** 功能描述:寻找左线 右线 中线
** 说明:  不补线
***************************************************************************************************/

 void Get_flag(void)     
 
 {
  
      uchar hang=0,lie=0;
    

     for(hang =0;hang<ROW;hang++ )
     {
       
            for(lie=60;lie<=COLUMN-3;lie++) 
            {
                if((Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie+1]<THRESHOLD)&&(Image_Data[hang][lie+2]<THRESHOLD)) 
                {
                      left_line[hang] = lie;
                      break;
                }                        
            }
            if(lie > COLUMN-3) left_line[hang] = COLUMN-1;
            for(lie=60;lie>=2;lie--) 
            {
                if((Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie-1]<THRESHOLD)&&(Image_Data[hang][lie-2]<THRESHOLD)) 
                {
                      right_line[hang] = lie;
                      break;
                }
            }
            if(lie < 2) right_line[hang] = 0;
         
            center_line[hang] = (left_line[hang]+right_line[hang])/2;
       
     }
  
  
 }


 
 
 /***************************************************************************************************
** 函数名称: Get_Flag
** 功能描述:寻找左线 右线 
** 说明:带补线
        
***************************************************************************************************/

 void Get_Flag(void)     
 
 
 {
     uchar hang=0,lie=0;
     uchar temp1=0,temp2=0;

     for(hang = 0;hang<ROW-1;hang++ )
     {
        if(hang<7)                                        //前四行边界扫描                              
        {
            for(lie=60;lie<=COLUMN-4;lie++) 
            {
                if((Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie+1]<THRESHOLD)&&(Image_Data[hang][lie+2]<THRESHOLD)&&(Image_Data[hang][lie+3]<THRESHOLD)) 
                {
                      left_line[hang] = lie;
                      break;
                }                        
            }
            if(lie > COLUMN-4) {left_line[hang] = COLUMN-1;}
            for(lie=60;lie>=3;lie--) 
            {
                if((Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie-1]<THRESHOLD)&&(Image_Data[hang][lie-2]<THRESHOLD)&&(Image_Data[hang][lie-3]<THRESHOLD)) 
                {
                      right_line[hang] = lie;
                      break;
                }
            }
            if(lie < 3) {right_line[hang] = 0;}
        } 
        else
        {
            if(left_line[hang-1]<112)      temp1 = left_line[hang-1] + 7;        
            else     temp1 = 119;
            if((left_line[hang-1] - 7)>0)     temp2 = left_line[hang-1] - 7;
            else     temp2 = 0;
            for(lie = temp2;lie <= temp1-3;lie++)                     
            {
                if((Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie+1]<THRESHOLD)&&(Image_Data[hang][lie+2]<THRESHOLD)&&(Image_Data[hang][lie+3]<THRESHOLD))
                {
                     left_line[hang] = lie;
                     break;
                }
            }
          if(lie > temp1-3) {left_line[hang] = left_line[hang-1];}
            
            // if(lie > temp1-3) {left_line[hang] = left_line[hang-1]-(left_line[hang-9]+left_line[hang-8]+left_line[hang-7]+left_line[hang-6]-left_line[hang-5]-left_line[hang-4]-left_line[hang-3]-left_line[hang-2])/10;}
            
            
            
            if(right_line[hang-1]>7)      temp1 = right_line[hang-1] - 7;
            else     temp1 = 0;
            if(right_line[hang-1]+7<119)      temp2 = right_line[hang-1] + 7;
            else     temp2 = 119;            
            for(lie = temp2;lie >= temp1+3;lie--)
            {
                if((Image_Data[hang][lie]>=THRESHOLD)&&(Image_Data[hang][lie-1]<THRESHOLD)&&(Image_Data[hang][lie-2]<THRESHOLD)&&(Image_Data[hang][lie-3]<THRESHOLD))
                {
                     right_line[hang] = lie;
                     break;
                }
            }
           if(lie < temp1+3) {right_line[hang] = right_line[hang-1];}
            
            
            // if(lie < temp1+3) {right_line[hang] = right_line[hang-1]-(right_line[hang-9]+right_line[hang-8]+right_line[hang-7]+right_line[hang-6]-right_line[hang-5]-right_line[hang-4]-right_line[hang-3]-right_line[hang-2])/10;}
            
            
        }
       
     }
  
  
  
  
 }
 
  /***************************************************************************************************
** 函数名称: bj_lvbo1
** 功能描述:边界线滤波
** 说明:
         
***************************************************************************************************/

 
 void bj_lvbo1(void)
{
    uchar line=0,left_0=0,right_0=0;
    for(line = 0;line<ROW-1;line++) 
    {
        if(left_line[line] == 119)    left_0++;
        if(right_line[line] == 0)    right_0++;
    }
    if(left_0>=38)
    {
        for(line = 1;line<ROW-1;line++)
        {
            if(right_line[line] - right_line[line-1] < 0)
                right_line[line] = right_line[line-1];
        }
    }
    if(right_0>=38)
    {
        for(line = 1;line<ROW-1;line++)
        {
            if(left_line[line] - left_line[line-1] > 0)
                left_line[line] = left_line[line-1];
        }
    }
    for(line=2;line<ROW-1;line++)
    {
          	 if(((left_line[line]-left_line[line-1])>=2)&&((left_line[line]-left_line[line+1])>=2))
          	 {
          	  	 left_line[line]=(uchar)((left_line[line-1]+left_line[line+1])>>1);
          	 }
              else if(((left_line[line-1]-left_line[line])>=2)&&((left_line[line+1]-left_line[line])>=2))
          	 {
          		 left_line[line]=(uchar)((left_line[line-1]+left_line[line+1])>>1);
          	 }
      	
          	  if(((right_line[line]-right_line[line-1])>=2)&&((right_line[line]-right_line[line+1])>=2))
          	  {
          		   right_line[line]=(uchar)((right_line[line-1]+right_line[line+1])>>1);
          	  }
              else  if(((right_line[line-1]-right_line[line])>=2)&&((right_line[line+1]-right_line[line])>=2))
          	 {
          		  right_line[line]=(uchar)((right_line[line-1]+right_line[line+1])>>1);
          	 }
    }
}


 /***************************************************************************************************
** 函数名称: zx_extract_1
** 功能描述:中心线提取
** 说明:
           可补线
***************************************************************************************************/

 void zx_extract_1(void) 
{
    unsigned char flag_fg=0,line,i=0;
    for(line=0;line<ROW-1;line++) 
    {
        if(left_line[line]<119&&right_line[line]>0) 
        {
            center_line[line] = (uchar)((left_line[line] + right_line[line])>>1);
            flag_fg++;
            continue;
        }
        if(flag_fg>3)                                                    //若丢线较少变补上边界线
        {
            i++;
            if(i>=3) 
            {
                 if(left_line[line]<119&&right_line[line]==0) 
                 {
                    center_line[line] = left_line[line]>>1;
                    continue;
                 }
                 if(left_line[line]==119&&right_line[line]>0)
                 {
                    center_line[line] = (uchar)((right_line[line]+COLUMN-1)>>1);
                    continue;
                 }
                 if(left_line[line]==119&&right_line[line]==0)                                         
                 {
                    center_line[line] = (uchar)((left_line[line] + right_line[line])>>1);
                    continue;
                 }
            }
            center_line[line] = (uchar)((left_line[line] + right_line[line])>>1);                    
            continue;
        }
        if(left_line[line]<119&&right_line[line]==0) 
        {
               center_line[line] = left_line[line]>>1;
               continue;
        } 
        if(left_line[line]==119&&right_line[line]>0)
        {
              center_line[line] = (uchar)((right_line[line]+COLUMN-1)>>1);
              continue;
        }
        if(left_line[line]==119&&right_line[line]==0)
        {
              center_line[line] = (uchar)((left_line[line]+right_line[line])>>1);
              continue;
        }
        
      
      
      
        if(left_line[line]<=65&&right_line[line]<15)
        {
              center_line[line] = left_line[line];
              continue;
        }
        
        if(left_line[line]>95&&right_line[line]>55)
        {
              center_line[line] = right_line[line];
              continue;
        }
    }
}
 
  /***************************************************************************************************
** 函数名称: zx_lvbo1
** 功能描述:中心线滤波1
** 说明:
           
***************************************************************************************************/
 void zx_lvbo1(void)
{
    uchar line=0;
    for(line=1;line<ROW-1;line++)
    {
      	if((center_line[line]>center_line[line-1])&&(center_line[line]>center_line[line+1]))
      	{
      		center_line[line]=(uchar)((center_line[line-1]+center_line[line+1])/2);
      	}
      	else if((center_line[line]<center_line[line-1])&&(center_line[line]<center_line[line+1]))
      	{
      		center_line[line]=(uchar)((center_line[line-1]+center_line[line+1])/2); 
      	}
    }
}
/***************************************************************************************************
** 函数名称: zx_lvbo2
** 功能描述:中心线滤波2
** 说明:
           
***************************************************************************************************/
 void zx_lvbo2(void)
{
    uchar line,temp3,temp4;
    for(line=2;line<ROW-1;line++)
    {
        	if((center_line[line]>center_line[line-1])&&(center_line[line]>center_line[line+1]))
        	{
        		temp3=(uchar)((center_line[line-1]+center_line[line-2])/2);
        	  	temp4=(uchar)((center_line[line+1]+center_line[line+2])/2);
        	  	center_line[line]=(uchar)((temp3+temp4)/2);
        	}
        	else if((center_line[line]<center_line[line-1])&&(center_line[line]<center_line[line+1]))
        	{
        			temp3=(uchar)((center_line[line-1]+center_line[line-2])/2);
        	  		temp4=(uchar)((center_line[line+1]+center_line[line+2])/2);
        	  		center_line[line]=(uchar)((temp3+temp4)/2);
        	}
    }
}
/***************************************************************************************************
** 函数名称: zw_yx_tq1
** 功能描述:转弯有效行提取
** 说明:
           
***************************************************************************************************/
void zw_yx_tq1() 
{
    uchar hang=0;
    for(hang =0;hang<ROW-1;hang++)
    {
        if((left_line[hang]<=7)||(right_line[hang]>=93)||(left_line[hang]<=right_line[hang])) 
        {
            zw_row = hang;                                                     //有待改进
            break;
        }
    }
    
    if(hang>=ROW-1) {zw_row = ROW-1;}
}

/***************************************************************************************************
** 函数名称: give_direction_1
** 功能描述: 根据中线求平均偏差  用于P参数
** 说明:
           
***************************************************************************************************/
 int give_direction_1()
{
    int line=0,b=0;
    int diff=0;
   
 //  for(line=10;line<=30;line+=2)
//    {
 //		diff=diff+(center_line[line]-mid);               //*Q_num_1(line)
 // }
   
   // for(line=3;line<=32;line++)                             
    //{
     //  if(line<=12&&line>=3)  b=1;
       
      // else if(line>12&&line<=22)  b=1 ;
       
      // else if(line>22&&line<=27)  b=12 ;
       
      // else if(line>27&&line<=32)  b=2 ;
    
      //	diff=center_line[25]*4+center_line[33]*3+center_line[18]*3-10*mid;//*b;   
        	diff=center_line[10]*3+center_line[17]*2+center_line[23]*3+center_line[28]*5+center_line[32]*5+center_line[35]*2-20*mid;//*b;
    
 //		diff=diff+(center_line[line]-mid)//*b;               //*Q_num_1(line)
//  } 
   
   
   
    diff=diff/20 ;
    return diff;
}

/***************************************************************************************************
** 函数名称: td_hang
** 功能描述: 根据中线求偏差的偏差，用于积分D参数
** 说明:
           
***************************************************************************************************/
int td_hang(uchar hang) 
{
    
        return ((center_line[hang-1]+center_line[hang+1]+center_line[hang]+center_line[hang+2]+center_line[hang-2])/5-mid);
    
}

/***************************************************************************************************
** 函数名称:give_xielv2
** 功能描述: 根据中线求弯道斜率
** 说明:
           
***************************************************************************************************/
int give_xielv2()
{           
  int xl_piancha;
  if(zw_row==39)
  xl_piancha=(int)(10*(center_line[34]+center_line[32]+center_line[30]+center_line[28]+center_line[26]+center_line[24]-center_line[5]-center_line[7]-center_line[9]-center_line[11]-center_line[13]-center_line[15])/27);    
   else if(zw_row>=15) 
        xl_piancha=(int)(10*(center_line[30]+center_line[29]+center_line[28]+center_line[27]+center_line[26]+center_line[25]-center_line[4]-center_line[5]-center_line[6]-center_line[7]-center_line[8]-center_line[9])/21);
    else
        xl_piancha=(int)(10*(center_line[16]+center_line[15]+center_line[14]+center_line[13]+center_line[12]+center_line[11]-center_line[1]-center_line[2]-center_line[3]-center_line[4]-center_line[5]-center_line[6])/11);
  return xl_piancha;
}








                        




