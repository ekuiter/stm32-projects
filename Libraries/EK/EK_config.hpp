#ifndef __EK_CONFIG_HPP
#define __EK_CONFIG_HPP

#include "stm32f10x.h"

void EXTI_Config(uint32_t EXTI_Line, EXTITrigger_TypeDef EXTI_Trigger, EXTIMode_TypeDef EXTI_Mode, FunctionalState EXTI_LineCmd = ENABLE);
void NVIC_Config(uint8_t NVIC_IRQChannel, uint8_t NVIC_IRQChannelPreemptionPriority = 0x0f, uint8_t NVIC_IRQChannelSubPriority = 0x0f, FunctionalState NVIC_IRQChannelCmd = ENABLE);

#endif
