#include<stdio.h>
#include<reg51.h>

sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;
sbit led4 = P1^4;

sbit in = P2^3;
sbit out = P2^7;

unsigned int mode;

void delay(){
	int i,j;
	for(i=0;i<50;i++){
		for(j=0;j<50;j++){}
	}
}
void mode1(){
	led1=1;led2=0;led3=0;led4=0;
	delay();
	led1=0;led2=1;led3=0;led4=0;
	delay();
	led1=0;led2=0;led3=1;led4=0;
	delay();
	led1=0;led2=0;led3=0;led4=1;
	delay();
}
void mode2(){
	led1=1;led2=0;led3=1;led4=0;
	delay();
	led1=0;led2=1;led3=0;led4=1;
	delay();
}
void mode3(){
	unsigned int i=0;
	for(i=0;i<16;i++){
		led1 = (i & 0x01) ? 1 : 0;
		led2 = (i & 0x02) ? 1 : 0;
		led3 = (i & 0x04) ? 1 : 0;
		led4 = (i & 0x08) ? 1 : 0;
	}
}
void mode4(){
	led1=1;led2=1;led3=1;led4=1;
	delay();
	led1=0;led2=0;led3=0;led4=0;
	delay();
}
void check(){
	if(in==0){
		delay();
		if(in==0){
			mode=(mode+1) % 5;
			while(in==0);
		}
	}
}
void switching(){
	switch(mode){
		case 0:
			led1=0;led2=0;led3=0;led4=0;
			delay();
			break;
		case 1:
			mode1();
			break;
		case 2:
			mode2();
			break;
		case 3:
			mode3();
			break;
		case 4:
			mode4();
			break;
	}
}
void main(void){
	mode=0;
	while(1){
		check();
		
		switching();
	}
}
