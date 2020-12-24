/**
* @file:num.c
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:数码管
* @detail:
* @author:郭轩铭
* @date:2020-11-27
* @version:v1.0
* @record:修改记录
*/

#include "num.h"

/**
* @brief:延时函数
* @Name:Delay
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:
* @return:
**/
void Delay(u16 i)
{
    while(--i);
}

/**
* @brief:计算各位显示
* @Name:Cal
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void Cal()
{
  light[2] = num % 1000 / 100;
  light[1] = num % 1000 % 100 / 10;
  light[0] = num % 1000 % 10 % 10;
  //light[0] = num % 10;
  ReadBuff[2] = light[0] + '0';
  ReadBuff[1] = light[1] + '0';
  ReadBuff[0] = light[2] + '0';
}

/**
* @brief:138译码器
* @Name:Drive138
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void Drive138(u8 num)
{
  LSA = num & 0x01;
  LSB = (num & 0x02) >> 1; 
  LSC = (num & 0x04) >> 2;
}

/**
* @brief:显示数码管
* @Name:DisplayNum
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void DisplayNum()
{
  int i = 0;
  for(;i<3;i++)
  {
    Drive138(i);
    P0 = smgduan[light[i]];
    Delay(200);
  }
}
