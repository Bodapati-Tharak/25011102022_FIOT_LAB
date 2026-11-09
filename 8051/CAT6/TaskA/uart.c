#include <reg51.h>

void main()
{
    char str[] = "gagan";
    int i = 0;

    TMOD = 0x20;
    TH1 = 0xFA;
    SCON = 0x50;
    TR1 = 1;

    while(1)
    {
        for(i = 0; str[i] != '\0'; i++)
        {
            SBUF = str[i];
            while(TI == 0);
            TI = 0;
        }
    }
}