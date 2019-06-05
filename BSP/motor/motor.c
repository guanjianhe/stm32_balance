#include "motor.h"

static void MOTOR_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                  GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_15);
}


static void PWM_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void PWM_Mode_Config(uint16_t period, uint16_t prescaler)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef   TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /*��ʱ���ڣ���ʱ����Ϊ(arr+1)��T��TΪʱ��Դ����*/
    TIM_TimeBaseStructure.TIM_Period = period;

    /*
    * �Զ�ʱ��ʱ��TIMxCLK��Ԥ��Ƶֵ����Ƶ����Ϊ���������TIMx_CNT
    * ������ʱ�ӣ��õ������������ʱ��Ƶ��Ϊf(CK_CNT)=f(TIMxCLK)/(N+1)��
    * ����N��Ϊ��������Ա��ʱ�ӷ�Ƶֵ������Ƶ�Ļ���72MHz
    */
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;

    /*û�κ�Ӱ��*/
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    /*����ģʽ�����ϼ���*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    /*��ʼ��*/
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /*
     * ���ģʽ����
     * PWM1ģʽ�������ϻ����¼���ʱ����TIMx_CNT<TIMx_CCRn(�ȽϼĴ���,����ֵ����TIM_Pulse��Ա������)ʱ��
     * ͨ��n���Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��PWM2ģʽ��PWM1ģʽ�෴����Ч��ƽ��TIM_OCPolarity��Ա���á�
     */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

    /* ������Ч��ƽ */
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    /* �������ģʽ��״̬��ʹ�ܻ�ر���� */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;


    /* ����Ա�Ĳ���ֵ��Ϊ�ȽϼĴ���TIMx_CCR����ֵ */
    TIM_OCInitStructure.TIM_Pulse = 0;

    /* ��ʼ��ͨ��4�����Ըı����ϳ�Ա��ֵ������ͨ��Ҳһ�� */
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);


    /*
     * �������ÿ⺯��TIM_SetComparex��̬�޸ıȽϼĴ�����ֵ����TIM_Mode_Config()��
     * ����TIM_SetCompare1(TIM3,500);
     */

    //    TIM_SetCompare4( TIM2, 72 * 0 );


    /* ʹ��TIM�ȽϼĴ���CCRx���� */
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    /* ʹ��TIM���ؼĴ���ARR */
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    /* ʹ�ܶ�ʱ��2 */
    TIM_Cmd(TIM2, ENABLE);

}



void motor_init(void)
{
    MOTOR_GPIO_Config();
    PWM_GPIO_Config();
    PWM_Mode_Config(999, 0);
}

