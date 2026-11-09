
#include <reg51.h>

sbit led = P1^0;

void delay()
{
    volatile int i, j;

    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 100; j++)
        {
        }
    }
}

void main()
{
    led = 0;

    while(1)
    {
        led = !led;
        delay();
    }
}
