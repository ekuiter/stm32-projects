#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <rt_sys.h>
#include <EK_config.h>
#include <FATFS/src/ff.h>
#include "stm32f10x.h"

/* 
  tested functions:
  printf / sprintf / fprintf / scanf
  fopen / fclose
  fgetc / fgets
  fputc / fputs
  feof / rewind

  Using stdout / stderr / stdin with f... functions works as expected.
  (stdout / stderr prints to USART and / or GUI, stdin reads from USART.)
	For GUI printing, #define PRINTF_USE_GUI in EK_config.h and call ConfigWriteToGUI!

  For now, only one file can be opened at a time. (malloc doesn't work reliably for bigger structures!)
  
  fopen modes:
  r  - Open file   and allow read
  r+ - Open file   and allow read  and allow write
  w  - Create file and allow write
  w+ - Create file and allow write and allow read
  ...b - Same as above (no special treatment for binary data)
  anything else - Open file and create file if necessary and allow read and allow write
*/

#pragma import(__use_no_semihosting)

struct __FILE {
	FIL fsrc;
	bool eof;
};

#ifdef PRINTF_USE_GUI
#include <uCGUI_LIB/USER/uCGUI/WM/WM.h>
#include <uCGUI_LIB/USER/uCGUI/Widget/TEXT.h>
#include <string.h>

static char* TextBuf = 0;
static int MaxTextBufLength = 0;
static WM_HWIN TextItem = 0;

void ConfigWriteToGUI(char* buf, int len, WM_HWIN ti) {
  TextBuf = buf;
	MaxTextBufLength = len;
	TextItem = ti;
	memset(TextBuf, 0, MaxTextBufLength);
}

void FlushGUI(void) {
  TEXT_SetText(TextItem, TextBuf);
}
#endif

extern void HeapMarkAlloc(void*, size_t, const char*, const char*, int);

FILE* fopen(const char* path, const char* modeBuf) {
	unsigned char mode = FA_OPEN_ALWAYS | FA_READ | FA_WRITE;
	FILE* f;
	if (strcmp("r", modeBuf)  == 0 || strcmp("rb", modeBuf)  == 0) mode = FA_READ;
	if (strcmp("r+", modeBuf) == 0 || strcmp("r+b", modeBuf) == 0) mode = FA_READ | FA_WRITE;
	if (strcmp("w", modeBuf)  == 0 || strcmp("wb", modeBuf)  == 0) mode = FA_CREATE_ALWAYS | FA_WRITE;
  if (strcmp("w+", modeBuf) == 0 || strcmp("w+b", modeBuf) == 0) mode = FA_CREATE_ALWAYS | FA_READ | FA_WRITE;
	f = malloc(sizeof(FILE));
	if (f != NULL && f_open(&f->fsrc, path, mode) == FR_OK) {
		HeapMarkAlloc(f, sizeof(FILE), "fopen", path, 0);
		f->eof = false;
	  return f;
	}
	return NULL;
}

#ifndef PRINTF_USE_GUI
#define PRINTF_USE_USART
#endif

int fputc(int c, FILE* f) {
	if (f == stdout || f == stderr) {
#ifdef PRINTF_USE_GUI
		if (TextBuf != 0) {
		  int TextBufLength = strlen(TextBuf);
			if (TextBufLength >= MaxTextBufLength - 1) {
				memset(TextBuf, 0, MaxTextBufLength);
				TextBuf[0] = c;
			} else
				TextBuf[TextBufLength] = c;
		}
#endif
#ifdef PRINTF_USE_USART
		if (c == '\n') fputc('\r', stdout);
		if (c == '\b' || c == 127) fputc('~', stdout);
		USART_SendData(USART1, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
#endif
	} else if (f == stdin) {
	} else if (f != NULL) {
		UINT bw = 0;
		f_write(&f->fsrc, &c, 1, &bw);
	}
	return c;
}

int fgetc(FILE* f) {
	int c = EOF;
	if (f == stdin) {
		while (!USART_GetITStatus(USART1, USART_IT_RXNE));
		c = USART_ReceiveData(USART1);
		if (c == '\b' || c == 127) c = '~';
	  fputc(c, stdout);
	} else if (f == stdout || f == stderr) {
	} else if (f != NULL) {
		UINT br = 0;
		char buf;
		f_read(&f->fsrc, &buf, 1, &br);
		c = buf;
		if (br == 0) {
			f->eof = true;
			c = EOF;
		}
	}
  return c;
}

int feof(FILE* f) {
  if (f != NULL)
		return f->eof;
	return -1;
}

int ferror(FILE* f) {
  return 0;
}

void rewind(FILE* f) {
	if (f != NULL)
    f_lseek(&f->fsrc, 0);
}

extern void HeapMarkFree(void*, const char*, const char*, int);

int fclose(FILE* f) {
	if (f != NULL) {
	  f_close(&f->fsrc);
		free(f);
		HeapMarkFree(f, "fclose", "", 0);
    return 0;
	}
	return -1;
}

int __backspace(FILE* f) {
	if (f != NULL) {
	  f_lseek(&f->fsrc, f_tell(&f->fsrc) - 1);
		return 0;
	}
  return -1;
}

void __aeabi_assert(const char *expr, const char *file, int line) {
  printf("ASSERT FAILED: %s (in file %s at line %d)", expr, file, line);
	while (1);
}
