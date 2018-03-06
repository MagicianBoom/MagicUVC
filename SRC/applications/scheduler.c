/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * ����   �������ƴ�
 * �ļ���  ��scheduler.c
 * ����    ���������
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "scheduler.h"
#include "includes.h"
#include "time.h"
#include "mpu6050.h"
#include "ak8975.h"
#include "led.h"
#include "rc.h"
#include "imu.h"
#include "pwm_in.h"
#include "ctrl.h"
#include "ms5611.h"
#include "parameter.h"
#include "ultrasonic.h"
#include "height_ctrl.h"
#include "fly_mode.h"

s16 loop_cnt;


loop_t loop;

void Loop_check()  //TIME INTTERRUPT
{
	loop.time++; //u16
	loop.cnt_2ms++;
	loop.cnt_5ms++;
	loop.cnt_10ms++;
	loop.cnt_20ms++;
	loop.cnt_50ms++;

	if( loop.check_flag == 1)
	{
		loop.err_flag ++;     //ÿ�ۼ�һ�Σ�֤��������Ԥ��������û�����ꡣ
	}
	else
	{	
		loop.check_flag = 1;	//�ñ�־λ��ѭ�����������
	}
	
		LED_1ms_DRV( );								//20��led������ʾ
}

void Duty_1ms()
{
	Get_Cycle_T(1)/1000000.0f;

	ANO_DT_Data_Exchange();												//����ͨ�Ŷ�ʱ����
}

float test[5];
void Duty_2ms()
{
	float inner_loop_time;
	
	inner_loop_time = Get_Cycle_T(0)/1000000.0f; 						//��ȡ�ڻ�׼ȷ��ִ������
	
	test[0] = GetSysTime_us()/1000000.0f;
	
	MPU6050_Read(); 															//��ȡmpu6�ᴫ����

	MPU6050_Data_Prepare( inner_loop_time );			//mpu6�ᴫ�������ݴ���
	
	/*IMU������̬�����룺���ִ�����ڣ��������������ݣ�ת������ÿ�룩��������ٶȼ����ݣ�4096--1G���������ROLPITYAW��̬��*/
 	IMUupdate(0.5f *inner_loop_time, mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);

	CTRL_1( inner_loop_time ); 										//�ڻ����ٶȿ��ơ����룺ִ�����ڣ��������ٶȣ��������ٶȣ��Ƕ�ǰ������������PWMռ�ձȡ�<����δ��װ>
	
	RC_Duty( inner_loop_time , Rc_Pwm_In );				// ң����ͨ�����ݴ��� �����룺ִ�����ڣ����ջ�pwm��������ݡ�
	
	
	
	test[1] = GetSysTime_us()/1000000.0f;
}

void Duty_5ms()
{
	float outer_loop_time;
	
	outer_loop_time = Get_Cycle_T(2)/1000000.0f;								//��ȡ�⻷׼ȷ��ִ������
	
	test[2] = GetSysTime_us()/1000000.0f;

 	CTRL_2( outer_loop_time ); 											// �⻷�Ƕȿ��ơ����룺ִ�����ڣ������Ƕȣ�ҡ����������̬�Ƕȣ�������������ٶȡ�<����δ��װ>
	
	test[3] = GetSysTime_us()/1000000.0f;
}

void Duty_10ms()
{

		
	  ANO_AK8975_Read();			//��ȡ������������	
}

void Duty_20ms()
{
	Parameter_Save();
}

void Duty_50ms()
{
	//Mode();	
	mode_check(CH_filter,mode_value);
	LED_Duty();								//LED����
	Ultra_Duty();
}


void Duty_Loop()   					//�����������Ϊ1ms���ܵĴ���ִ��ʱ����ҪС��1ms��
{

	if( loop.check_flag == 1 )
	{
		loop_cnt = time_1ms;
		
		Duty_1ms();							//����1ms������
		
		if( loop.cnt_2ms >= 2 )
		{
			loop.cnt_2ms = 0;
			Duty_2ms();						//����2ms������
		}
		if( loop.cnt_5ms >= 5 )
		{
			loop.cnt_5ms = 0;
			Duty_5ms();						//����5ms������
		}
		if( loop.cnt_10ms >= 10 )
		{
			loop.cnt_10ms = 0;
			Duty_10ms();					//����10ms������
		}
		if( loop.cnt_20ms >= 20 )
		{
			loop.cnt_20ms = 0;
			Duty_20ms();					//����20ms������
		}
		if( loop.cnt_50ms >= 50 )
		{
			loop.cnt_50ms = 0;
			Duty_50ms();					//����50ms������
		}
		
		loop.check_flag = 0;		//ѭ��������ϱ�־
	}
}




	/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
	
