//用52单片机配置DS18传感器时数据口要上拉4.7K电阻
//
#include "ds18.h"
#include "main.h"
#include "reg52.h"
#include "delay.h"

sbit ds  = P3^7;  //DS18B20单总线



u8 ds_nmb=0;


//DS18初始化
void dsInit()
{   
	unsigned int i;
	if( ds_nmb==0 )ds = 0;
	
	i = 100;  
	while(i>0) i--;
	if( ds_nmb==0 )ds = 1;
	i = 4;
	while(i>0) i--;
}
 
void dsWait()
{
	unsigned int i;
	if( ds_nmb==0 )while(ds);  

	if( ds_nmb==0 )while(~ds);  
	i = 4;
	while(i > 0) i--;
}


bit readBit()
{
	unsigned int i;
	bit b;
	if( ds_nmb==0 )ds = 0;
	
	i++;   
	if( ds_nmb==0 )ds = 1;
	
	i++; i++;
	if( ds_nmb==0 )b = ds;

	i = 8; 
	while(i>0) i--;
	return b;
}

unsigned char readByte()
{
	unsigned int i;
	unsigned char j, dat;
	dat = 0;
	for(i=0; i<8; i++)
	{
	  j = readBit();
	
	  dat = (j << 7) | (dat >> 1);
	}
	return dat;
}


void writeByte(unsigned char dat)
{
	unsigned int i;
	unsigned char j;
	bit b;
	for(j = 0; j < 8; j++)
	{
	  b = dat & 0x01;
	  dat >>= 1;
	
	  if(b)   
	  {
			if( ds_nmb==0 )ds = 0;
			
			i++; i++;  
			if( ds_nmb==0 )ds = 1;
			
			i = 8; while(i>0) i--;  
	  }
	  else  
	  {
			if( ds_nmb==0 )ds = 0;
			
			i = 8; while(i>0) i--;  
			if( ds_nmb==0 )ds = 1;
			
			i++; i++;
	  }
	}
}


void sendChangeCmd()
{
	dsInit();    
	dsWait();   
	delay1(1);    
	writeByte(0xcc);
	writeByte(0x44);
}

void sendReadCmd()
{
	dsInit();
	dsWait();
	delay1(1);
	writeByte(0xcc); 
	writeByte(0xbe); 
}


u16 getTmpValue()
{
	u16 tmpvalue;
	int value; 
	float t;
	u8 low, high;
	sendReadCmd();
	
	low = readByte(); 
	high = readByte();
	
	tmpvalue = high;
	tmpvalue <<= 8;
	tmpvalue |= low;
	value = tmpvalue;
	t = value * 0.0625;
	value = t * 100 + (value > 0 ? 0.5 : -0.5); //大于0加0.5, 小于0减0.5
	value/=10;
	sendChangeCmd();
	if( value<0 )value=0;
	return value;
}

