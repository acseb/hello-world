#ifndef __UART_H_
#define __UART_H_

/**
* @file:uart.h
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:定义串口通信的头文件
* @detail:包含各类串口通信函数
* @author:郭轩铭
* @date:2020-12-07
* @version:v1.0
* @record:修改记录
*/
#include "reg52.h"


#ifndef u8
#define u8 unsigned char
#endif 
#ifndef u16
#define u16 unsigned int
#endif


extern u8 ReadBuff[10];   //设置接收字符串缓存


void InitConfig(void);

void UartSendByte(unsigned char dat);

void UartSendStr(unsigned char *s);

void UartInterrupt(void);


#endif