#include "uart.h"

/**
* @brief:��ʼ�������Լ�T2��ʱ��
* @Name:InitUart
* @author: ������
* @Data:2020-12-08
* @version:V1.0
* @param:��
* @return:��
**/
void InitConfig(void)
{
    /*
     * SCON: ��ʽ 1, 8-bit, �����������
     * TMOD: ���ö�ʱ��1�����ڷ�ʽ2, 8-bit �Զ���װ
     * TH1:  ��ʼֵΪ0xFD  �����ʣ�9600 ����Ƶ�ʣ�11.0592MHz
     */
    SCON = 0x50;
    TMOD |= 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;
    EA  = 1;
    //�򿪴����ж�
    ES  = 1;

    /* T2��ʱ����Ԥװ��ֵ�����16�ξ���1�롣 */
    RCAP2H=0x0B;
    RCAP2L=0xDC;
    /*����T2�ж�*/
    ET2=1;
    /*����T2��ʱ��*/
    TR2=1;
}

/**
* @brief:����һ���ֽ�����
* @Name:UartSendByte
* @author: ������
* @Data:2020-12-08
* @version:V1.0
* @param:[in] dat ������byte
* @return:��
**/
void UartSendByte(unsigned char dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

/**
* @brief:�����ַ���
* @Name:UartSendStr
* @author: ������
* @Data:2020-12-08
* @version:V1.0
* @param:[in] str �����ַ���ָ��
* @return:��
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
* @brief:�ж�����
* @Name:CheckPassword
* @author: ������
* @Data:2020-12-08
* @version:V1.0
* @param:��
* @return:��
**/
//void CheckPassword()
//{
//    //��������ַ���
//    UartSendStr(ReadBuff);
//    //���뻻��
//    UartSendByte('\r');
//    UartSendByte('\n');
//}

/**
* @brief:�����жϴ����� �����ڽ��յ����ݣ�����������϶��������𴮿��жϣ�
* @Name:UartInterrupt
* @author: ������
* @Data:2020-12-08
* @version:V1.0
* @param:��
* @return:��
**/
void UartInterrupt(void) interrupt 4
{
    if(RI==1)
    {
        RI = 0;
    }
}
