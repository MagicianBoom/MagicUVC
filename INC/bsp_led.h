#ifndef BSP_LED_H
#define BSP_LED_H

#include "stm32f4xx.h"
#include "sys.h"

void led_configuration(void);

#define BEEP PFout(8)
#define LED0 PFout(9)
#define LED1 PFout(10)

#endif

