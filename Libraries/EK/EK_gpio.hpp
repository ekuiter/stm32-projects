#ifndef __EK_GPIO_HPP
#define __EK_GPIO_HPP

#include "stm32f10x.h"

class GPIO_Pin {
  private:
		GPIO_TypeDef* Port;
	  uint16_t Pin;
	  GPIOMode_TypeDef Mode;
	  GPIOSpeed_TypeDef Speed;
	  void ConfigInternal();
    int GetPortNumber();
	  uint32_t GetClock();
	  GPIO_TypeDef* GetPortFromString(const char*);
	  uint16_t GetPinFromString(const char*);
	public:
		GPIO_Pin(GPIO_TypeDef*, uint16_t);
	  GPIO_Pin(GPIO_TypeDef*, uint16_t, GPIOMode_TypeDef, GPIOSpeed_TypeDef = GPIO_Speed_50MHz);
  	GPIO_Pin(const char*);
  	GPIO_Pin(const char*, GPIOMode_TypeDef, GPIOSpeed_TypeDef = GPIO_Speed_50MHz);
	  void Config(GPIOMode_TypeDef, GPIOSpeed_TypeDef = GPIO_Speed_50MHz);
	  void Print();
		void Set(bool state);
		bool Get();
		void On();
	  void Off();
};

#endif
