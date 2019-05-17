void delayus(unsigned int us)
{
    unsigned int i;
    for(i=0;i<us;i++);
      _asm(nop); 
} 
////////////////////////////一个简单的延时函数///////////////////////////////
void delay(unsigned int ms)
{
    unsigned int i,j;
    for(j=0;j<ms;j++)
       for(i=0;i<110;i++);     
}         