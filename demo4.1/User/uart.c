#include "uart.h"

/**
* @brief:初始化串口以及T2定时器
* @Name:InitUart
* @author: 郭轩铭
* @Data:2020-12-08
* @version:V1.0
* @param:空
* @return:空
**/
void InitConfig(void)
{
    /*
     * SCON: 方式 1, 8-bit, 允许接收数据
     * TMOD: 设置定时器1工作在方式2, 8-bit 自动重装
     * TH1:  初始值为0xFD  波特率：9600 晶振频率：11.0592MHz
     */
    SCON = 0x50;
    TMOD |= 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;
    EA  = 1;
    //打开串口中断
    ES  = 1;

    /* T2定时器赋预装载值，溢出16次就是1秒。 */
    RCAP2H=0x0B;
    RCAP2L=0xDC;
    /*允许T2中断*/
    ET2=1;
    /*启动T2定时器*/
    TR2=1;
}

/**
* @brief:发送一个字节数据
* @Name:UartSendByte
* @author: 郭轩铭
* @Data:2020-12-08
* @version:V1.0
* @param:[in] dat 待输入byte
* @return:空
**/
void UartSendByte(unsigned char dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

/**
* @brief:发送字符串
* @Name:UartSendStr
* @author: 郭轩铭
* @Data:2020-12-08
* @version:V1.0
* @param:[in] str 输入字符串指针
* @return:空
**/
void UartSendStr(unsigned char *str)
{
    while(*str != '\0')
    {
        UartSendByte(*str);
        str++;
    }
    UartSendByte('\r');
    UartSendByte('\n');
}

/**
* @brief:判断密码
* @Name:CheckPassword
* @author: 郭轩铭
* @Data:2020-12-08
* @version:V1.0
* @param:空
* @return:空
**/
//void CheckPassword()
//{
//    //测试输出字符串
//    UartSendStr(ReadBuff);
//    //加入换行
//    UartSendByte('\r');
//    UartSendByte('\n');
//}

/**
* @brief:串口中断处理函数 （串口接收到数据，发送数据完毕都可以引起串口中断）
* @Name:UartInterrupt
* @author: 郭轩铭
* @Data:2020-12-08
* @version:V1.0
* @param:空
* @return:空
**/
void UartInterrupt(void) interrupt 4
{
    if(RI==1)
    {
        RI = 0;
    }
}
