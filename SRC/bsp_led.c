#include "bsp_led.h"

void led_configuration(void)
{
	RCC->AHB1ENR|=1<<5;//ʹ��PORTFʱ�� 
	GPIO_Set(GPIOF,PIN8|PIN9|PIN10,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PF9,PF10����
	LED0=1;//LED0�ر�
	LED1=1;//LED1�ر�
	BEEP = 0;
}
