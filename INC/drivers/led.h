#ifndef _LED_H_
#define	_LED_H_

#include "stm32f4xx.h"

#define NEW_ANOPILOT

#ifndef NEW_ANOPILOT
//�ɰ�

#define LED1_OFF         ANO_GPIO_LED_E->BSRRL = ANO_Pin_LED1   //H
#define LED1_ON          ANO_GPIO_LED_E->BSRRH = ANO_Pin_LED1		//L
#define LED2_OFF         ANO_GPIO_LED->BSRRL = ANO_Pin_LED2
#define LED2_ON          ANO_GPIO_LED->BSRRH = ANO_Pin_LED2
#define LED3_OFF         ANO_GPIO_LED->BSRRL = ANO_Pin_LED3
#define LED3_ON          ANO_GPIO_LED->BSRRH = ANO_Pin_LED3
#define LED4_OFF         ANO_GPIO_LED->BSRRL = ANO_Pin_LED4
#define LED4_ON          ANO_GPIO_LED->BSRRH = ANO_Pin_LED4

#else
//�°�

#define LED1_OFF         ANO_GPIO_LED_E->BSRRL = ANO_Pin_LED1   //H
#define LED1_ON          ANO_GPIO_LED_E->BSRRH = ANO_Pin_LED1		//L
#define LED2_ON          ANO_GPIO_LED->BSRRL = ANO_Pin_LED2
#define LED2_OFF         ANO_GPIO_LED->BSRRH = ANO_Pin_LED2
#define LED3_ON          ANO_GPIO_LED->BSRRL = ANO_Pin_LED3
#define LED3_OFF         ANO_GPIO_LED->BSRRH = ANO_Pin_LED3
#define LED4_ON          ANO_GPIO_LED->BSRRL = ANO_Pin_LED4
#define LED4_OFF         ANO_GPIO_LED->BSRRH = ANO_Pin_LED4

#endif

/***************LED GPIO����******************/
#define ANO_RCC_LED			RCC_AHB1Periph_GPIOE
#define ANO_GPIO_LED		GPIOD
#define ANO_GPIO_LED_E		GPIOE
#define ANO_Pin_LED1		GPIO_Pin_2
#define ANO_Pin_LED2		GPIO_Pin_10
#define ANO_Pin_LED3		GPIO_Pin_9
#define ANO_Pin_LED4		GPIO_Pin_8
/*********************************************/
/*
//RGB_Info == 0����ɫ����˫��1�Σ���ǰģʽΪ3���������
//RGB_Info == 1����ɫ����˫��2�Σ���ǰģʽΪ4���������
//RGB_Info == 2����ɫ����˫��3�Σ���ǰģʽΪ6���������
//RGB_Info == 3����ɫ����˫��4�Σ���ǰģʽΪ8���������
//RGB_Info == 4����ɫ����1�μ����˸�����Դ������쳣��
//RGB_Info == 5����ɫ����2�μ����˸�����������쳣��
//RGB_Info == 6����ɫ����3����˸����ѹ���쳣��
//RGB_Info == 7����ɫ������˸���������������Լ�У׼�С�
//RGB_Info == 8��������ɫ�������Լ�ʧ�ܣ���������

//RGB_Info == 9��	������ɫ���ֶ�ģʽ����������̬ģʽ����
//RGB_Info == 10��������ɫ���Զ�ģʽ���������㶨�ߣ���
//RGB_Info == 11�������̺�ɫ��GPS�ź����������Զ�ģʽ����
//RGB_Info == 12�������̻�ɫ�������źŸ����������Զ�ģʽ����

//RGB_Info == 13��˫���װ�ɫ���ֶ�ģʽ����������̬ģʽ����
//RGB_Info == 14��˫������ɫ���Զ�ģʽ���������㶨�ߣ���
//RGB_Info == 15��˫���̺�ɫ��GPS�ź����������Զ�ģʽ����
//RGB_Info == 16��˫���̻�ɫ�������źŸ��Ž������Զ�ģʽ����

//RGB_Info == 17��˫������ɫ������ģʽ��

//RGB_Info == 18����ɫ���������������͡�
//RGB_Info == 19������ɫ����������У׼�С�
//RGB_Info == 20������ɫ���������ٶȼ�У׼�С�
//RGB_Info == 21����ɫ����������У׼�С�
//RGB_Info == 22����ɫ������У׼ʧ�ܡ�


RGB_Info == 9��	��ɫ�������ֶ�����ģʽ���� 
RGB_Info == 23, ��ɫ�������ֶ�����ģʽ����
RGB_Info == 24, ��ɫ��������ѹ��������
RGB_Info == 25, ��ɫ��������ѹ���߽���
RGB_Info == 26, ��ɫ��������������������
RGB_Info == 27, ��ɫ���������������߽���
����������������
LED_Info == ����
*/
enum  //led���
{
	X=0,
	B,
	R,
	G,
	LED_NUM,

};

typedef struct
{
	u8 RGB_Info;
	u8 LED_Info;

	u8 RGB_Info_old;
}LED_state;
extern LED_state light;

void LED_Init(void);
void LED_1ms_DRV(void );
void LED_Duty(void);

void LED_MPU_Err(void);
void LED_Mag_Err(void);
void LED_MS5611_Err(void);
void aircraft_mode_led(u8 maxmotors);


#endif
