//#include "pid.h"
//#include "reg52.h"
//#include "main.h"
//
//////定时器0重装载值
////u16 TIM0_Data=30000;//每1ms中端一次
//
////void TIME_Init()
////{
////	TMOD=0x01;   //定时器0，工作模式2，8位定时模式
////	TL0=TIM0_Data;//重装值低位
////	TH0=TIM0_Data>>8;//重装值高位
////	TR0=1;//启动定时器
////	ET0=1;//允许定时器中断
////	EA=1;//打开总中断
////}
//
//
////定时器0中断模拟PWM
//u32 SYSTICK=0;
////timer0() interrupt 1  
////{
////	SYSTICK++;
////	TL0=TIM0_Data;//重装值低位
////	TH0=TIM0_Data>>8;//重装值高位
////}




