#ifndef __EK_USART_HPP
#define __EK_USART_HPP

#include "stm32f10x.h"
#include <stdio.h>
#include <EK_config.h>
#include <string.h>

typedef void (*clockFunc_t)(uint32_t, FunctionalState);

class USART {
  private:
		USART_TypeDef* Port;
	  uint32_t BaudRate, WordLength, StopBits, Parity;
		void ConfigInternal();
	  clockFunc_t GetClockFunc();
	  uint32_t GetClock();
	  const char* GetTxPin();
	  const char* GetRxPin();
	public:
		USART(USART_TypeDef*);
		USART(USART_TypeDef*, uint32_t, uint16_t = USART_WordLength_8b, uint16_t = USART_StopBits_1, uint16_t = USART_Parity_No);
	  void Config(uint32_t, uint16_t = USART_WordLength_8b, uint16_t = USART_StopBits_1, uint16_t = USART_Parity_No);
	  char* ReadLn(char*, int, const char* = NULL);
	  
	  void Write(uint8_t ch) {
		  USART_SendData(Port, ch);
      while (USART_GetFlagStatus(Port, USART_FLAG_TC) == RESET);
		}
		
		bool Available(void) {
		  return USART_GetITStatus(Port, USART_IT_RXNE);
		}
};

#endif
