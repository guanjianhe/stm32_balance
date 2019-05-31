#include "stm32f10x.h"
#include "led.h"
#include "encode.h"
#include "motor.h"
#include "uart.h"


int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    led_init();
    motor_init();
    encode_init();
    uart_init();

    while (1)
    {
        xputs("hello world\r\n");
    }
}

