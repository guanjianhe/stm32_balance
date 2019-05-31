#include "led.h"

/* 初始化LED */
void led_init(void)
{
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启GPIOC外设时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* 选择要控制的GPIO引脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

    /*设置引脚速率为50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    /*调用库函数，初始化GPIO*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* 关闭led灯 */
    led_off();
}

void led_on(void)
{
    GPIOC->BRR = GPIO_Pin_13;
}

void led_off(void)
{
    GPIOC->BSRR = GPIO_Pin_13;
}

void led_toggle(void)
{
    GPIOC->ODR ^= GPIO_Pin_13;
}


