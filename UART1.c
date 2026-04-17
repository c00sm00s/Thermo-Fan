#include "reg52.h"
#include "delay.h"
#include "uart1.h"


bit busy;

#define FOSC 11059200L      //System frequency
#define BAUD 9600       //UART baudrate

                                                                                                         

//串口初始化	
void UartInit()
{
	SCON = 0x50;            //8-bit variable UART
	TL2 = RCAP2L = (65536-(FOSC/32/BAUD)); //Set auto-reload vaule
	TH2 = RCAP2H = (65536-(FOSC/32/BAUD)) >> 8;
	T2CON = 0x34;           //Timer2 start run
	ES = 1;                 //Enable UART interrupt
	EA = 1;                 //Open master interrupt switch
}


//发送一个字节
void U1_TX(char DATA)
{
	while (busy);
	SBUF=DATA;
	busy=1;
}


//发送多个字节
void U1_TXDATA(u16 nmb, char * DATA )
{
	u16 i=0;
	for( i=0; i<nmb; i++ )
	{
		U1_TX(DATA[i]);
	}
}






