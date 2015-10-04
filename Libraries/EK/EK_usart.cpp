#include "EK_usart.hpp"
#include "EK_gpio.hpp"
#include "EK_retarget.hpp"
#include <stdbool.h>

USART::USART(USART_TypeDef* p): Port(p), WordLength(USART_WordLength_8b), StopBits(USART_StopBits_1), Parity(USART_Parity_No) {}

USART::USART(USART_TypeDef* p, uint32_t br, uint16_t wl, uint16_t sb, uint16_t par): Port(p), BaudRate(br), WordLength(wl), StopBits(sb), Parity(par) {
  ConfigInternal();
}

void USART::Config(uint32_t baudRate, uint16_t wordLength, uint16_t stopBits, uint16_t parity) {
	BaudRate = baudRate;
	WordLength = wordLength;
	StopBits = stopBits;
	Parity = parity;
  ConfigInternal();
}

void USART::ConfigInternal() {
  GetClockFunc()(GetClock(), ENABLE);
  GPIO_Pin(GetTxPin(), GPIO_Mode_AF_PP);
  GPIO_Pin(GetRxPin(), GPIO_Mode_IN_FLOATING);
	USART_InitTypeDef USART_InitStructure; 
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = WordLength;
  USART_InitStructure.USART_StopBits = StopBits;
  USART_InitStructure.USART_Parity = Parity;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(Port, &USART_InitStructure); 
  USART_ITConfig(Port, USART_IT_RXNE, ENABLE);
  USART_ITConfig(Port, USART_IT_TXE, ENABLE);
  USART_Cmd(Port, ENABLE);
	Write(0x00);
}

clockFunc_t USART::GetClockFunc() {
  if (Port == USART1) return &RCC_APB2PeriphClockCmd;
  if (Port == USART2) return &RCC_APB1PeriphClockCmd;
  if (Port == USART3) return &RCC_APB1PeriphClockCmd;
	return 0;
}

uint32_t USART::GetClock() {
  if (Port == USART1) return RCC_APB2Periph_USART1;
  if (Port == USART2) return RCC_APB1Periph_USART2;
  if (Port == USART3) return RCC_APB1Periph_USART3;
	return 0;
}

const char* USART::GetTxPin() {
  if (Port == USART1) return "PA9";
  if (Port == USART2) return "PA2";
  if (Port == USART3) return "PB10";
	return 0;
}

const char* USART::GetRxPin() {
  if (Port == USART1) return "PA10";
  if (Port == USART2) return "PA3";
  if (Port == USART3) return "PB11";
	return 0;
}

char* USART::ReadLn(char* buf, int len, const char* prompt) {
  if (Port != USART1)
		return NULL;
	char scanBuf[15]; // len may be up to 99999999 bytes
	sprintf(scanBuf, "%%%d[^\r\n]", len - 1);
	if (prompt)
		printf("%s", prompt);
	if (scanf(scanBuf, buf) != 1)
		buf[0] = 0;
	printf("\r\n");
	return buf;
}

/*char* USART::ReadLn(char* buf, int len) {
	char c = 0;
	int br = 0;
	while ((c = ReadFromUSART1()) != 0 && c != '\r' && c != '\n' && br < len - 1) {
		if (c == '\b' || c == 127) {
			br--;
			continue;
		}
	  buf[br] = c;
		br++;
	}
	printf("\r\n");
	buf[br] = 0;
  return buf;
}*/
