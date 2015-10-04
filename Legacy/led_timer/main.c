#include "stm32f10x.h"

int main(void) { 
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = 17999; // 72000000hz/(17999+1)=4000hz
  TIM_TimeBaseInitStructure.TIM_Period = 1999; // (0..1999)/4000hz=500ms
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  TIM_TimeBaseInitStructure.TIM_Period = 1332; // (0..1332)/4000hz=333ms
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM2, ENABLE);
  TIM_Cmd(TIM3, ENABLE);

  while(1) {}
}

void TIM2_IRQHandler(void) {
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0))
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
  else
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void TIM3_IRQHandler(void) {
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1))
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);
  else
    GPIO_SetBits(GPIOB, GPIO_Pin_1);
}
