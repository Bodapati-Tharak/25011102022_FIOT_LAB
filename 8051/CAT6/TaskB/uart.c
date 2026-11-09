
#include <reg51.h>

#define BUFFER_SIZE 16

volatile unsigned char rx_buffer[BUFFER_SIZE];
volatile unsigned char rx_head = 0;
volatile unsigned char rx_tail = 0;
volatile unsigned char tx_done = 0;

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
    unsigned char next_head;
    unsigned char data_char;

    if(RI == 1)
    {
        data_char = SBUF;
        RI = 0;

        next_head = (rx_head + 1) & 0x0F;

        if(next_head != rx_tail)
        {
            rx_buffer[rx_head] = data_char;
            rx_head = next_head;
        }
    }

    if(TI == 1)
    {
        TI = 0;
        tx_done = 1;
    }
}

unsigned char uart_receive(void)
{
    unsigned char data_char;

    while(rx_head == rx_tail);

    data_char = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) & 0x0F;

    return data_char;
}

void uart_send(unsigned char data_char)
{
    tx_done = 0;
    SBUF = data_char;

    while(tx_done == 0);
}

void main(void)
{
    unsigned char received;

    uart_init();

    while(1)
    {
        received = uart_receive();
        uart_send(received);
    }
}
