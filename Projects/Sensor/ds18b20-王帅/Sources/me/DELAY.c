void delayus(unsigned int us)
{
    unsigned int i;
    for(i=0;i<us;i++);
      _asm(nop); 
} 
////////////////////////////һ���򵥵���ʱ����///////////////////////////////
void delay(unsigned int ms)
{
    unsigned int i,j;
    for(j=0;j<ms;j++)
       for(i=0;i<110;i++);     
}         