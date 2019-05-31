#include "led.h"

/* ��ʼ��LED */
void led_init(void)
{
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*����GPIOC����ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* ѡ��Ҫ���Ƶ�GPIO���� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

    /*������������Ϊ50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /*��������ģʽΪͨ���������*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    /*���ÿ⺯������ʼ��GPIO*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* �ر�led�� */
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


