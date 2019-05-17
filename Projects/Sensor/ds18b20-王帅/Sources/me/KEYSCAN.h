#ifndef __KEYSCAN__
#define __KEYSCAN__

#define keyO1  PORTA_PA1   	//
#define keyO2  PORTA_PA2   	//
#define keyO3  PORTA_PA3   	//
#define keyI1  PORTA_PA4   	//
#define keyI2  PORTA_PA5   	//
#define keyI3  PORTA_PA6   	//
#define keyI4  PORTA_PA7   	//
unsigned char key(void);
void keypro(void);
void keyswait(void);

#endif 