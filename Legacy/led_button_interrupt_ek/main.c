#include "stm32f10x.h"
#include "config.h"

int main(void) {     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
 
  GPIO_Config(GPIOB, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Mode_Out_PP); // PB0 = LED1 / PB1 = LED2
  GPIO_Config(GPIOC, GPIO_Pin_13, GPIO_Mode_IN_FLOATING); // PC13 = USER_KEYA
  GPIO_Config(GPIOB, GPIO_Pin_2, GPIO_Mode_IN_FLOATING); // PB2 = USER_KEYB

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13); // PC13
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2); // PB2

  EXTI_Config(EXTI_Line13, EXTI_Trigger_Rising_Falling); // P*13 (PC13)
  EXTI_Config(EXTI_Line2, EXTI_Trigger_Rising_Falling); // P*2 (PB2)

  NVIC_Config(EXTI15_10_IRQn); // P*10-15 (PC13)
  NVIC_Config(EXTI2_IRQn); // P*2 (PB2)

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
