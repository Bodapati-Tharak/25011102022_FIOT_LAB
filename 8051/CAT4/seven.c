#include <reg51.h>

/* Keypad rows */
sbit row1 = P2^7;
sbit row2 = P2^6;
sbit row3 = P2^5;
sbit row4 = P2^4;

/* Keypad columns */
sbit col1 = P2^3;
sbit col2 = P2^2;
sbit col3 = P2^1;
sbit col4 = P2^0;

/* LEDs */
sbit led1 = P1^0;
sbit led2 = P1^1;
sbit led3 = P1^2;
sbit led4 = P1^3;

/* Seven segment */
sbit segA = P0^0;
sbit segB = P0^1;
sbit segC = P0^2;
sbit segD = P0^3;
sbit segE = P0^4;
sbit segF = P0^5;
sbit segG = P0^6;


void delay_small()
{
    int i,j;

    for(i=0;i<100;i++)
        for(j=0;j<100;j++);
}


unsigned char keypad_scan()
{
    row1=0; row2=1; row3=1; row4=1;

    if(col1==0){
			
			return 1;
		}
		
    if(col2==0) return 2;
    if(col3==0) return 3;
    if(col4==0) return 10;       /* A */


    row1=1; row2=0; row3=1; row4=1;

    if(col1==0) return 4;
    if(col2==0) return 5;
    if(col3==0) return 6;
    if(col4==0) return 11;       /* B */


    row1=1; row2=1; row3=0; row4=1;

    if(col1==0) return 7;
    if(col2==0) return 8;
    if(col3==0) return 9;
    if(col4==0) return 12;       /* C */


    row1=1; row2=1; row3=1; row4=0;

    if(col1==0) return 13;       
    if(col2==0) return 0;
    if(col3==0) return 14;       
    if(col4==0) return 15;       

    return 255;
}


void display_digit(unsigned char value)
{
    switch(value)
    {
        case 0:
            segA=1; segB=1; segC=1; segD=1;
            segE=1; segF=1; segG=0;
            break;

        case 1:
            segA=0; segB=1; segC=1; segD=0;
            segE=0; segF=0; segG=0;
            break;

        case 2:
            segA=1; segB=1; segC=0; segD=1;
            segE=1; segF=0; segG=1;
            break;

        case 3:
            segA=1; segB=1; segC=1; segD=1;
            segE=0; segF=0; segG=1;
            break;

        case 4:
            segA=0; segB=1; segC=1; segD=0;
            segE=0; segF=1; segG=1;
            break;

        case 5:
            segA=1; segB=0; segC=1; segD=1;
            segE=0; segF=1; segG=1;
            break;

        case 6:
            segA=1; segB=0; segC=1; segD=1;
            segE=1; segF=1; segG=1;
            break;

        case 7:
            segA=1; segB=1; segC=1; segD=0;
            segE=0; segF=0; segG=0;
            break;

        case 8:
            segA=1; segB=1; segC=1; segD=1;
            segE=1; segF=1; segG=1;
            break;

        case 9:
            segA=1; segB=1; segC=1; segD=1;
            segE=0; segF=1; segG=1;
            break;
    }
}


void running_led()
{
    led1=1; led2=0; led3=0; led4=0;
    delay_small();

    led1=0; led2=1; led3=0; led4=0;
    delay_small();

    led1=0; led2=0; led3=1; led4=0;
    delay_small();

    led1=0; led2=0; led3=0; led4=1;
    delay_small();
}


void alternate_led()
{
    led1=1; led2=0; led3=1; led4=0;
    delay_small();

    led1=0; led2=1; led3=0; led4=1;
    delay_small();
}


void binary_counter()
{
    int count;

    for(count=0;count<16;count++)
    {
        led1=(count & 1) ? 1 : 0;
        led2=(count & 2) ? 1 : 0;
        led3=(count & 4) ? 1 : 0;
        led4=(count & 8) ? 1 : 0;

        delay_small();
    }
}


void blink_all()
{
    led1=1; led2=1; led3=1; led4=1;
    delay_small();

    led1=0; led2=0; led3=0; led4=0;
    delay_small();
}


void led_control(unsigned char key)
{
    switch(key)
    {
        case 1:
            led1=1; led2=0; led3=0; led4=0;
            break;

        case 2:
            led1=0; led2=1; led3=0; led4=0;
            break;

        case 3:
            led1=0; led2=0; led3=1; led4=0;
            break;

        case 4:
            led1=0; led2=0; led3=0; led4=1;
            break;

        case 5:
            running_led();
            break;

        case 6:
            alternate_led();
            break;

        case 7:
            binary_counter();
            break;

        case 8:
            blink_all();
            break;

        case 9:
            led1=0; led2=0; led3=0; led4=0;
            break;

        case 0:
            led1=0; led2=0; led3=0; led4=0;
            break;
    }
}


void main()
{
    unsigned char key;

    row1=1; row2=1; row3=1; row4=1;

    col1=1; col2=1; col3=1; col4=1;

    led1=0; led2=0; led3=0; led4=0;

    while(1)
    {
        key=keypad_scan();

        if(key!=255)
        {
            display_digit(key);
            led_control(key);

            delay_small();

            while(col1==0 || col2==0 || col3==0 || col4==0);
        }
    }
}