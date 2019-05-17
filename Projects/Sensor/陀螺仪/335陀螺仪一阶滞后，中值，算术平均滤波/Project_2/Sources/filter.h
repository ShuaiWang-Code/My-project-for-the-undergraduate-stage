#ifndef _FILTER_H_
#define _FILTER_H_
#include <hidef.h>     
#include "derivative.h"
//¾²Ì¬Ò»½×ÖÍºóÂË²¨
struct _filter_1st{
    float xin;
    float old;
    float result;
    float filter_k;
    
}filter_1st;

float filter_1(float lvbo) 
{    
     filter_1st.filter_k = 0.5;
     
     filter_1st.xin = lvbo;
     
     if(filter_1st.xin>filter_1st.old) 
     {
         filter_1st.result = filter_1st.old+(filter_1st.xin-filter_1st.old)*filter_1st.filter_k;
     }
     
     if(filter_1st.xin<filter_1st.old) 
     {
         filter_1st.result = filter_1st.old-(filter_1st.old-filter_1st.xin)*filter_1st.filter_k;
     }
     
     if(filter_1st.xin==filter_1st.old) 
     {
         filter_1st.result = filter_1st.old;
     }
     
     filter_1st.old = filter_1st.result;
     
     return filter_1st.result;

}

//ÅÅĞòÂË²¨
float paixu[4];
void pai_xu()
  {  
    float t;
    
           
    
    if(paixu[0]>paixu[1])
    {
        t=paixu[0];
        paixu[0]=paixu[1];
        paixu[1]=t;
    } 
    if(paixu[0]>paixu[2])
    {
        t=paixu[2];
        paixu[2]=paixu[0];
        paixu[0]=t;
    } 
    if(paixu[1]>paixu[2])
    {
        t=paixu[1];
        paixu[1]=paixu[2];
        paixu[2]=t;
    } 
    
    
}
//
/*
    paixu[i]=lvbo;
    
    i++;
    
  	if(i==3)
  	{
  	//ËãÊõÆ½¾ùÂË²¨
	    distance_data=(paixu[0]+paixu[1]+paixu[2]+paixu[3])/4;   
	//ÖĞÎ»ÖµÂË²¨
        pai_xu();
        distance_data=distance[1];
        i=0;
    }
*/

#endif