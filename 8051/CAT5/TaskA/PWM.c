#include <reg51.h>

sbit LED = P1^0;

void Timer0_ISR(void) interrupt 1
{
    
    TH0 = 0xFC;
    TL0 = 0x66;
		LED = ~LED;w
   
}

void main(void)
{
		LED = 0;
   
    TMOD = 0x01;

   
    TH0 = 0xFC;
    TL0 = 0x66;

    
    ET0 = 1;

   
    EA = 1;

    
    TR0 = 1;
		
    while(1)
    {
      
    }
}