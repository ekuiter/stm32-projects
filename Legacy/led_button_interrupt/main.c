#include "stm32f10x.h"

void GPIO_Configuration(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void EXTI_Configuration(void) {
  EXTI_InitTypeDef EXTI_InitStructure;

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);

  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;

  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  EXTI_Init(&EXTI_InitStructure);

  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Configuration(void) {
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_Init(&NVIC_InitStructure);
}

int main(void) {     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
 
  GPIO_Configuration();
  EXTI_Configuration();
  NVIC_Configuration();

  while(1) {}
}

void EXTI15_10_IRQHandler(void) {
  EXTI_ClearITPendingBit(EXTI_Line13);
  if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1)
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
  else
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
}

void EXTI2_IRQHandler(void) {
  EXTI_ClearITPendingBit(EXTI_Line2);
  if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0)
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);
  else
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
}
