/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * ����   �������ƴ�
 * �ļ���  ��init.c
 * ����    ���ɿس�ʼ��
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/

#include "includes.h"
#include "pwm_out.h"
#include "mpu6050.h"
#include "i2c_soft.h"
#include "led.h"
#include "ctrl.h"
#include "ms5611.h"
#include "ak8975.h"
#include "ultrasonic.h"

u8 All_Init()
{
//	NVIC_PriorityGroupConfig(NVIC_GROUP);		//�ж����ȼ��������
	
//	SysTick_Configuration(); 	//�δ�ʱ��
	
	I2c_Soft_Init();					//��ʼ��ģ��I2C
	
	PWM_IN_Init();						//��ʼ�����ջ��ɼ�����
	
	PWM_Out_Init(400);				//��ʼ������������	
	
	Usb_Hid_Init();						//�ɿ�usb�ӿڵ�hid��ʼ��
	
	MS5611_Init();						//��ѹ�Ƴ�ʼ��
	
	Delay_ms(400);						//��ʱ
	
	MPU6050_Init(20);   			//���ٶȼơ������ǳ�ʼ��������20hz��ͨ
//	
	LED_Init();								//LED���ܳ�ʼ��
//	
	Usart2_Init(500000);			//����2��ʼ������������Ϊ������
	Uart4_Init(500000);

//	
//	//TIM_INIT();
//	
	Para_Init();							//������ʼ��
	
	Delay_ms(100);						//��ʱ
	
	Ultrasonic_Init();   			//��������ʼ��
	
//	
	ak8975_ok = !(ANO_AK8975_Run());
//	
//	if( !mpu6050_ok )
//	{
//		LED_MPU_Err();
//	}
//	else if( !ak8975_ok )
//	{
//		LED_Mag_Err();
//	}
//	else if( !ms5611_ok )
//	{
//		LED_MS5611_Err();
//	}
//	
//	aircraft_mode_led(MAXMOTORS);
//	
//	Cycle_Time_Init();
	
 	return (1);
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/