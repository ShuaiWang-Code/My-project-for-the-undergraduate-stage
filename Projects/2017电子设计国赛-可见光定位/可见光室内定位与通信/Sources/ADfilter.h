#ifndef _ADfilter_H_
#define _ADfilter_H_
#include <hidef.h>     
#include "derivative.h"


int ad_average1=0,ad_average2=0,ad_average3=0,ad_average4=0,ad_average5=0;

#define FILTER_N 100
#define FILTER1_N 100
#define FILTER2_N 100
#define FILTER3_N 100
#define FILTER4_N 100
int i1,i2,i3,i4,i5;

int i = 0,j=0,k=0,l=0,m=0;

long filter_sum = 0,filter_sum1 = 0,filter_sum2 = 0,filter_sum3 = 0,filter_sum4 = 0;

int filter_max, filter_min;
int filter_max1, filter_min1;
int filter_max2, filter_min2;
int filter_max3, filter_min3;
int filter_max4, filter_min4;

int filter_buf[FILTER_N];
int filter_buf1[FILTER1_N];
int filter_buf2[FILTER2_N];
int filter_buf3[FILTER3_N];
int filter_buf4[FILTER4_N];


void filter(int val)
{
        //a[i] = val;
        //i++;
        filter_buf[i] = val;
        i++;
        if (i == 10)
        {
                i = 0;
                //ad_average = (a[0]+a[1]+a[2]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9])/10;
                ad_average1 = Filter0();
        
        }
        
        
}
void filter1(int val1)
{
        //a[i] = val;
        //i++;
        filter_buf1[j] = val1;
        j++;
        if (j == 10)
        {
                j = 0;
                //ad_average = (a[0]+a[1]+a[2]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9])/10;
                ad_average2 = Filter1();
        
        }
        
        
}
void filter2(int val2)
{
        //a[i] = val;
        //i++;
        filter_buf2[k] = val2;
        k++;
        if (k == 10)
        {
                k = 0;
                //ad_average = (a[0]+a[1]+a[2]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9])/10;
                ad_average3 = Filter2();
        
        }
        
        
}
void filter3(int val3)
{
        //a[i] = val;
        //i++;
        filter_buf3[l] = val3;
        l++;
        if (l == 10)
        {
                l = 0;
                //ad_average = (a[0]+a[1]+a[2]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9])/10;
                ad_average4 = Filter3();
        
        }
        
        
}
void filter4(int val4)
{
        //a[i] = val;
        //i++;
        filter_buf4[m] = val4;
        m++;
        if (m == 10)
        {
                m = 0;
                //ad_average = (a[0]+a[1]+a[2]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9])/10;
                ad_average5 = Filter4();
        
        }
        
        
}



int Filter0() 
{



       // for(i1 = 0; i1 < FILTER_N; i1++) 
        //{

        //        filter_buf[i1] = ATD0DR0;       

        //}

        filter_max = filter_buf[0];

        filter_min = filter_buf[0];

        filter_sum = filter_buf[0];

        for(i1 = FILTER_N - 1; i1 > 0; i1--) 
        {

                if(filter_buf[i1] > filter_max)

                        filter_max=filter_buf[i1];

                else if(filter_buf[i1] < filter_min)

                        filter_min=filter_buf[i1];

                        filter_sum = filter_sum + filter_buf[i1];

                        filter_buf[i1] = filter_buf[i1 - 1];

        }

        i1 = FILTER_N - 2;

        filter_sum = filter_sum - filter_max - filter_min + i1 / 2; // +i/2 的目的是为了四舍五入

        filter_sum = filter_sum / i1;

        return filter_sum;

}


int Filter1() 
{



       // for(i1 = 0; i1 < FILTER_N; i1++) 
        //{

        //        filter_buf[i1] = ATD0DR0;       

        //}

        filter_max1 = filter_buf1[0];

        filter_min1 = filter_buf1[0];

        filter_sum1 = filter_buf1[0];

        for(i2 = FILTER1_N - 1; i2 > 0; i2--) 
        {

                if(filter_buf1[i2] > filter_max1)

                        filter_max1=filter_buf1[i2];

                else if(filter_buf1[i2] < filter_min1)

                        filter_min1=filter_buf1[i2];

                        filter_sum1 = filter_sum1 + filter_buf1[i2];

                        filter_buf1[i2] = filter_buf1[i2 - 1];

        }

        i2 = FILTER1_N - 2;

        filter_sum1 = filter_sum1 - filter_max1 - filter_min1 + i2 / 2; // +i/2 的目的是为了四舍五入

        filter_sum1 = filter_sum1 / i2;

        return filter_sum1;

}


int Filter2() 
{



       // for(i1 = 0; i1 < FILTER_N; i1++) 
        //{

        //        filter_buf[i1] = ATD0DR0;       

        //}

        filter_max2 = filter_buf2[0];

        filter_min2 = filter_buf2[0];

        filter_sum2 = filter_buf2[0];

        for(i3 = FILTER2_N - 1; i3 > 0; i3--) 
        {

                if(filter_buf2[i3] > filter_max2)

                        filter_max2=filter_buf2[i3];

                else if(filter_buf2[i3] < filter_min2)

                        filter_min2=filter_buf2[i3];

                        filter_sum2 = filter_sum2 + filter_buf2[i3];

                        filter_buf2[i3] = filter_buf2[i3 - 1];

        }

        i3 = FILTER2_N - 2;

        filter_sum2 = filter_sum2 - filter_max2 - filter_min2 + i3 / 2; // +i/2 的目的是为了四舍五入

        filter_sum2 = filter_sum2 / i3;

        return filter_sum2;

}


int Filter3() 
{



       // for(i1 = 0; i1 < FILTER_N; i1++) 
        //{

        //        filter_buf[i1] = ATD0DR0;       

        //}

        filter_max3 = filter_buf3[0];
                                
        filter_min3 = filter_buf3[0];

        filter_sum3 = filter_buf3[0];

        for(i4 = FILTER3_N - 1; i4 > 0; i4--) 
        {

                if(filter_buf3[i4] > filter_max3)

                        filter_max3=filter_buf3[i4];

                else if(filter_buf3[i4] < filter_min3)

                        filter_min3=filter_buf3[i4];

                        filter_sum3 = filter_sum3 + filter_buf3[i4];

                        filter_buf3[i4] = filter_buf3[i4 - 1];

        }

        i4 = FILTER3_N - 2;

        filter_sum3 = filter_sum3 - filter_max3 - filter_min3 + i4 / 2; // +i/2 的目的是为了四舍五入

        filter_sum3 = filter_sum3 / i4;

        return filter_sum3;

}


int Filter4() 
{



       // for(i1 = 0; i1 < FILTER_N; i1++) 
        //{

        //        filter_buf[i1] = ATD0DR0;       

        //}

        filter_max4 = filter_buf4[0];

        filter_min4 = filter_buf4[0];

        filter_sum4 = filter_buf4[0];

        for(i5 = FILTER4_N - 1; i5 > 0; i5--) 
        {

                if(filter_buf4[i5] > filter_max4)

                        filter_max4=filter_buf4[i5];

                else if(filter_buf4[i5] < filter_min4)

                        filter_min4=filter_buf4[i5];

                        filter_sum4 = filter_sum4 + filter_buf4[i5];

                        filter_buf4[i5] = filter_buf4[i5 - 1];

        }

        i5= FILTER4_N - 2;

        filter_sum4 = filter_sum4 - filter_max4 - filter_min4 + i5 / 2; // +i/2 的目的是为了四舍五入

        filter_sum4 = filter_sum4 / i5;

        return filter_sum4;

}

#endif
