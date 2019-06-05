#include "stm32f10x.h"
#include "led.h"
#include "encode.h"
#include "motor.h"
#include "uart.h"
#include "timer.h"
#include "stdio.h"

uint32_t speed = 0;
/*ok*/
int main()
{
    uint8_t buf[100];
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    led_init();
    motor_init();
    encode_init();
    uart_init();
    timer_init();
    AIN1_H;
    AIN2_L;
    PWMA = 800;
	

    while (1)
    {
        sprintf((char *)buf,"speed = %d\r\n",(int16_t)speed);
        xputs((const char*)buf);        
    }
}

