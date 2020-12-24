#ifndef __NUM_H_
#define __NUM_H_


/**
* @file:num.h
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:
* @detail:
* @author:郭轩铭
* @date:2020-11-27
* @version:v1.0
* @record:修改记录
*/
#include "reg52.h"

#define u8 unsigned char
#define u16 unsigned int

/*
*设置138译码器
*/
sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

/*
*设声明全局变量
*/
extern u8 code smgduan[16];
extern u8 light[3];
extern u8 num;
extern u8 ReadBuff[10];   //设置接收字符串缓存


void Delay(u16 i);
  
void Cal();

void Drive138(u8 num);

void DisplayNum();


#endif

