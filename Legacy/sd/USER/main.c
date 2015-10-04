#include "stm32f10x.h"
#include <SD_Card/sdio_sd.h>
#include <FATFS/src/ff.h>
#include <EK/usart.h>
#include <EK/sd.h>
#include <string.h>

static char path[512] = "0:";

int main(void) {
  USART_Config(115200);
  printf("\r\nDetecting SD Card ...\r\n");
	SD_Config();
	SD_ListFiles(path, 512);
	SD_PrintSize();
  while (1);
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) { 
  while (1);
}
#endif
