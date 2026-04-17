#include "ds1302.h"


//初始时间定义
uchar time_buf[8] = {20,25,02,25,10,15,55,7};//初始时间2023 10月15日23点48分3秒 星期天


//DS1302初始化函数
void ds1302_init(void) 
{
	DS1302_RST=0;			//RST脚置低
	DS1302_SCK=0;			//SCK脚置低
}


//向DS1302写入一字节数据
void ds1302_write_byte(uchar addr, uchar d) 
{
	uchar i;
	DS1302_RST=1;//启动DS1302总线	
	//写入目标地址：addr
	addr = addr & 0xFE;   //最低位置零，寄存器0位为0时写，为1时读
	for (i = 0; i < 8; i ++)
	{
		if (addr & 0x01)DS1302_IO=1;else DS1302_IO=0;
		DS1302_SCK=1;      //产生时钟
		DS1302_SCK=0;
		addr = addr >> 1;
	}
	//写入数据：d
	for (i = 0; i < 8; i ++) 
	{
		if (d & 0x01)DS1302_IO=1;
		else DS1302_IO=0;
		DS1302_SCK=1;    //产生时钟
		DS1302_SCK=0;
		d = d >> 1;
	}
	DS1302_RST=0;//停止DS1302总线
}


//从DS1302读出一字节数据
uchar ds1302_read_byte(uchar addr) 
{
	uchar i,temp;	
	DS1302_RST=1;					//启动DS1302总线
	//写入目标地址：addr
	addr = addr | 0x01;    //最低位置高，寄存器0位为0时写，为1时读
	for (i = 0; i < 8; i ++) 
	{
		if (addr & 0x01)DS1302_IO=1;
		else DS1302_IO=0;
		DS1302_SCK=1;
		DS1302_SCK=0;
		addr = addr >> 1;
	}	
	//输出数据：temp
	for (i = 0; i < 8; i ++) 
	{
		temp = temp >> 1;
		if (DS1302_IO)temp |= 0x80;
		else temp &= 0x7F;
		DS1302_SCK=1;
		DS1302_SCK=0;
	}	
	DS1302_RST=0;					//停止DS1302总线
	return temp;
}


//向DS302写入时钟数据
void ds1302_write_time(void) 
{
	u8 data1;
	u8 i=0;
	
	for(i=0; i<8; i++)
	{
		data1 = time_buf[i]/10;
		data1 <<=4;
		data1 += time_buf[i]%10;
		time_buf[i] = data1;
	}
	
	ds1302_write_byte(ds1302_control_add,0x00);			//关闭写保护 
	ds1302_write_byte(ds1302_sec_add,0x80);				//暂停时钟 
	//ds1302_write_byte(ds1302_charger_add,0xa9);	    //涓流充电 
	ds1302_write_byte(ds1302_year_add,time_buf[1]);		//年 
	ds1302_write_byte(ds1302_month_add,time_buf[2]);	//月 
	ds1302_write_byte(ds1302_date_add,time_buf[3]);		//日 
	ds1302_write_byte(ds1302_hr_add,time_buf[4]);		//时 
	ds1302_write_byte(ds1302_min_add,time_buf[5]);		//分
	ds1302_write_byte(ds1302_sec_add,time_buf[6]);		//秒
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//周 
	ds1302_write_byte(ds1302_control_add,0x80);			//打开写保护     
}


//从DS302读出时钟数据
void ds1302_read_time(void)  
{
	u8 data1;
	u8 i=0;
	
	time_buf[1]=ds1302_read_byte(ds1302_year_add);		//年 
	time_buf[2]=ds1302_read_byte(ds1302_month_add);		//月 
	time_buf[3]=ds1302_read_byte(ds1302_date_add);		//日 
	time_buf[4]=ds1302_read_byte(ds1302_hr_add);		//时 
	time_buf[5]=ds1302_read_byte(ds1302_min_add);		//分 
	time_buf[6]=(ds1302_read_byte(ds1302_sec_add))&0x7f;//秒，屏蔽秒的第7位，避免超出59
	time_buf[7]=ds1302_read_byte(ds1302_day_add);		//周
	
	for( i=1; i<8; i++ )
	{
		data1 = time_buf[i]&0x0F;
		data1 += (((time_buf[i]&0xF0)>>4)*10);
		time_buf[i] = data1;
	}
}



