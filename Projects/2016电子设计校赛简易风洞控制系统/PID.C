#include "reg52.h"
#include "nokia_5110.h"
extern unsigned int b,intr;
struct _pid{
int set_distance;//定义设定距离
int actual_distance;//实际距离
int integral;
int error;
int error_next;
int error_last;
int kp,ki,kd;
int zengliang;
}pid;
void PID_init()
{
	pid.set_distance=0;
	pid.actual_distance=0;
	pid.error=0;
	pid.error_next=0;
	pid.error_last=0;
	pid.kp=2;
	pid.ki=0;
	pid.kd=0;	
	pid.zengliang=0;
	pid.integral=0;
}
void PID_realize(int distance,int pibo)
{
	pid.set_distance=distance;
	if(b>distance)
	{
	pid.error=pid.actual_distance-pid.set_distance;
	pid.zengliang=pid.kp*(pid.error);
	intr=pibo+pid.zengliang;
	}
	if(b<distance)
	{
	pid.error=pid.set_distance-pid.actual_distance;
	pid.zengliang=pid.kp*(pid.error);
	intr=pibo-pid.zengliang;
	}
	pid.integral+=pid.error;
	pid.actual_distance=b;
	pid.error_last=pid.error_next;
	pid.error_next=pid.error;
}