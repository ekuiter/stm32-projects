#include "EK_gpio.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <bitset>
#include <stdio.h>
#include "EK_retarget.hpp"

GPIO_Pin::GPIO_Pin(GPIO_TypeDef* port, uint16_t pin): Port(port), Pin(pin), Speed(GPIO_Speed_50MHz) {}
GPIO_Pin::GPIO_Pin(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed): Port(port), Pin(pin), Mode(mode), Speed(speed) {
  ConfigInternal();
}

GPIO_Pin::GPIO_Pin(const char* buf): Port(GetPortFromString(buf)), Pin(GetPinFromString(buf)), Speed(GPIO_Speed_50MHz) {}
GPIO_Pin::GPIO_Pin(const char* buf, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed): Port(GetPortFromString(buf)), Pin(GetPinFromString(buf)), Mode(mode), Speed(speed) {
	ConfigInternal();
}

void GPIO_Pin::Config(GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed) {
	Mode = mode;
	Speed = speed;
  ConfigInternal();
}

void GPIO_Pin::Print() {
	char port = 'A' + GetPortNumber();
  std::bitset<16> bits(Pin);
	int pin;
  for (pin = 0; pin < 16 && !bits[pin]; pin++);
	printf("P%c%d", port, pin);
}

void GPIO_Pin::Set(bool state) {
	GPIO_WriteBit(Port, Pin, state ? Bit_SET : Bit_RESET);
}

bool GPIO_Pin::Get() {
  return GPIO_ReadInputDataBit(Port, Pin);
}

void GPIO_Pin::On() {
	Set(true);
}

void GPIO_Pin::Off() {
	Set(false);
}

static bool portClockEnabled[7] = {false};

void GPIO_Pin::ConfigInternal() {
	int portNumber = GetPortNumber();
	if (!portClockEnabled[portNumber]) {
	  RCC_APB2PeriphClockCmd(GetClock(), ENABLE);
		portClockEnabled[portNumber] = true;
	}
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = Pin;
  GPIO_InitStructure.GPIO_Mode = Mode;
  GPIO_InitStructure.GPIO_Speed = Speed;
  GPIO_Init(Port, &GPIO_InitStructure);
}

int GPIO_Pin::GetPortNumber() {
  if (Port == GPIOA) return 0; if (Port == GPIOB) return 1; 
	if (Port == GPIOC) return 2; if (Port == GPIOD) return 3;
	if (Port == GPIOE) return 4; if (Port == GPIOF) return 5;
	if (Port == GPIOG) return 6;
	return -1;
}

uint32_t GPIO_Pin::GetClock() {
  switch(GetPortNumber()) {
	  case 0: return RCC_APB2Periph_GPIOA; case 1: return RCC_APB2Periph_GPIOB;
		case 2: return RCC_APB2Periph_GPIOC; case 3: return RCC_APB2Periph_GPIOD;
		case 4: return RCC_APB2Periph_GPIOE; case 5: return RCC_APB2Periph_GPIOF;
		case 6: return RCC_APB2Periph_GPIOG;
	}
	return 0;
}

GPIO_TypeDef* GPIO_Pin::GetPortFromString(const char* buf) {
  switch (buf[1]) {
	  case 'A': return GPIOA; case 'B': return GPIOB;
	  case 'C': return GPIOC; case 'D': return GPIOD;
	  case 'E': return GPIOE; case 'F': return GPIOF;
	  case 'G': return GPIOG;
	}
	return 0;
}

uint16_t GPIO_Pin::GetPinFromString(const char* buf) {
	int i = atoi(&buf[2]);
	return 1 << i;
}
