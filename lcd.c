#include "lcd.h"
#include "delay.h"
#include "main.h"
#include "string.h"



//LCD写指令
void write_com(uchar com)
{
	u8 i=0;
	uchar data1=0;
//	for(i=0; i<8; i++)
//	{
//		data1<<=1;
//		if(0x01&com)data1|=1;
//		com>>=1;
//	}
	
	P0=com;
	rs=0;
	lcden=0;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
}

//LCD写数据
void write_date(uchar date)
{
	u8 i=0;
	uchar data1=0;
//	for(i=0; i<8; i++)
//	{
//		data1<<=1;
//		if(0x01&date)data1|=1;
//		date>>=1;
//	}
   
	P0=date;
	rs=1;
	lcden=0;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
	
}

//LCD初始化
void LCD_init()
{
	rw=0;
	write_com(0x38);   //显示模式设置：16×2显示，5×7点阵，8位数据接口
	delay(20);
	write_com(0x0C);   //显示模式设置
	delay(20);
	write_com(0x06);   //显示模式设置：光标右移，字符不移
	delay(20);
	write_com(0x01);   //清屏幕指令，将以前的显示内容清除
	delay(20);	
}

//LCD设置显示位置 x与y是位置
void LCD_SetPlace( u8 x, u8 y )
{
	if( x<=20 )
	{
		switch( y )
		{
			case 0:write_com(0x80+x);break;
			case 1:write_com(0xC0+x);break;
			case 2:write_com(0x94+x);break;
			case 3:write_com(0xD4+x);break;
		}
		delay(20);	
	}
}

//LCD显示ASCLL 
//x<20 y<4一行写满自动跳到下一行
void LCD_Show( u8 x, u8 y, u8 *Data )
{
	u8 temp,a=0;
	//设置开始位置
	LCD_SetPlace(x,y);
	for( temp=strlen(Data); temp>0; temp-- )
	{
		write_date(Data[a]);
		x++;a++;
		delay(20);	
		if( x>19 )
		{
			y++;x=0;
			if( y==4 )return;
			LCD_SetPlace(x,y);
		}
	}
}




//显示整数 Data数据 nmb数字的位数
void LCD_ShowNmber( u8 x, u8 y, u32 Data, u8 nmb )
{
	u8 i,I;
	u8 temp[20]={0};

	I=nmb;
	for( i=0; i<nmb; i++ )
	{	 
		I--;
		temp[I] = Data%10+'0';Data/=10;
	}
	LCD_Show( x,y,temp);
	delay1(3);
}






