
#include <reg51.h>

volatile bit tx_done = 0;

void uart_init(void)
{
    TMOD = (TMOD & 0x0F) | 0x20;
    PCON = PCON & 0x7F;

    TH1 = 0xFD;
    TL1 = 0xFD;

    SCON = 0x50;

    TI = 0;
    RI = 0;

    ES = 1;
    EA = 1;
    TR1 = 1;
}

void serial_ISR(void) interrupt 4
{
    if(TI == 1)
    {
        TI = 0;
        tx_done = 1;
    }

    if(RI == 1)
    {
        RI = 0;
    }
}

void uart_send(char data_char)
{
    tx_done = 0;
    SBUF = data_char;

    while(tx_done == 0);
}

void uart_print(char *str)
{
    while(*str != '\0')
    {
        uart_send(*str);
        str++;
    }
}

void main(void)
{
    uart_init();

    while(1)
    {
        uart_print("Hello from 8051\r\n");
    }
}
