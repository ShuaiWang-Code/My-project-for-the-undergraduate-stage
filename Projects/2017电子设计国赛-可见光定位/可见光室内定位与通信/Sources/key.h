#ifndef _KEY_H_
#define _KEY_H_
#include <hidef.h>     
#include "derivative.h"

#define F0 PORTK_PK0
#define F1 PORTK_PK1
#define F2 PORTK_PK2
#define F3 PORTK_PK3
#define F4 PORTK_PK4
#define F5 PORTK_PK5

extern unsigned int flag_model1,flag_model2,flag_model3,flag_model4,flag_model5,flag_model6;
extern unsigned int flag0,flag1,flag2,flag3,secP;
void key_independecce_init()
{
    DDRK=0X00; 
}

void key_independence_scan()
{
    if(F0==0)
    {
         delayms(50);
        while(!F0);
         delayms(50);
         if(F0==1) {
          
        flag_model1=1;
        flag_model2=0;
        flag_model3=0;
        flag_model4=0;
        flag_model5=0;
        flag_model6=0;
         }
    }
    
    if(F1==0)
    {   
         delayms(50);
        while(!F1);
         delayms(50);
         if(F1==1) {
        flag_model1=0;
        flag_model2=1;
        flag_model3=0;
        flag_model4=0; 
        flag_model5=0;
        flag_model6=0;
         }
    }
    
    if(F2==0)
    {    
         delayms(50);
        while(!F2);
         delayms(50);
         if(F2==1) {
        flag_model1=0;
        flag_model2=0;
        flag_model3=1;
        flag_model4=0;
        flag_model5=0;
        flag_model6=0;
         }
    }
    
    if(F3==0)
    {
         delayms(50);
        while(!F3);
         delayms(50);
         if(F3==1) {
        flag_model1=0;
        flag_model2=0;
        flag_model3=0;
        flag_model4=1;
        flag_model5=0;
        flag_model6=0;
         }
    } 
    
    if(F4==0)
    {
         delayms(50);
        while(!F4);
         delayms(50);
         if(F4==1) {
        flag_model1=0;
        flag_model2=0;
        flag_model3=0;
        flag_model4=0;
        flag_model5=1;
        flag_model6=0;
         }
    }
    
    if(F5==0)
    {
         delayms(50);
        while(!F5);
         delayms(50);
         if(F5==1) {
        flag_model1=0;
        flag_model2=0;
        flag_model3=0;
        flag_model4=0;
        flag_model5=0;
        flag_model6=1;
         }
    } 
}


#endif