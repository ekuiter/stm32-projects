#include "stm32f10x.h"

int main(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
  while(1) {
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))
      GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
    else
      GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
      GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
    else
      GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);   
  } 
}
