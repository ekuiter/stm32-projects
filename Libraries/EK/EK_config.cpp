#include "EK_config.hpp"
#include "EK_retarget.hpp"

void EXTI_Config(uint32_t EXTI_Line, EXTITrigger_TypeDef EXTI_Trigger, EXTIMode_TypeDef EXTI_Mode, FunctionalState EXTI_LineCmd) {
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode;
  EXTI_InitStructure.EXTI_LineCmd = EXTI_LineCmd;
  EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Config(uint8_t NVIC_IRQChannel, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority, FunctionalState NVIC_IRQChannelCmd) {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;
  NVIC_Init(&NVIC_InitStructure);
}
