#include "EK_sd.hpp"
#include "EK_retarget.hpp"
#include <stdio.h>
#include <string.h>

extern "C" void SD_LowLevel_Init(void);

extern "C" void SDIO_IRQHandler(void) {
  SD_ProcessIRQSrc();
}           

extern "C" WCHAR ff_convert(WCHAR wch, UINT dir) {
	return wch < 0x80 ? wch : 0; // do not support unicode
}

extern "C" WCHAR ff_wtoupper(WCHAR wch) {
  if (wch < 0x80) {
    if (wch >= 'a' && wch <= 'z')
			wch &= ~0x20;
		return wch;
  } else // do not support unicode
    return 0;
}

SD_Card::SD_Card(void) {
  SD_LowLevel_Init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_Config(SDIO_IRQn, 0, 0, ENABLE);
}

extern "C" uint8_t OSTimeDlyHMSM(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t ms);

void SD_Card::Mount(void) {
	if(SD_Detect() == SD_PRESENT)
   printf("SD Card detected.\r\n");
  else {
    printf("No SD Card detected. Waiting for connect ...\r\n");
    while(SD_Detect() != SD_PRESENT)
      OSTimeDlyHMSM(0, 0, 0, 100);
    printf("SD Card detected. Wait a sec ...\r\n");
    OSTimeDlyHMSM(0, 0, 1, 0);
  }
  Assert(f_mount(0, &fs), "SD Card mounted.", "Mounting failed.", NULL);
}

DWORD SD_Card::GetSize(DWORD* available) {
  FATFS* fs;
  DWORD free;
  // assuming 512 bytes / sector
  if (Assert(f_getfree("0:", &free, &fs), NULL, "Card size was not detected.", NULL) == FR_OK) {
		*available = (free * fs->csize) / 2 / 1024;
	  return ((fs->n_fatent - 2) * fs->csize) / 2 / 1024;
	} else
		return *available = 0;
}

void SD_Card::PrintSize(void) {
	DWORD available = 0, total = GetSize(&available);
	if (total)
    printf("%lu MB total (%lu MB available)\r\n", total, available);
}

FRESULT SD_Card::List(char* path, int len, displayFunc_t displayFunc) {
  FILINFO fno;
  DIR dir;
  int i;
  char* fn;
  FRESULT res;
#if _USE_LFN
  static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
  fno.lfname = lfn;
  fno.lfsize = sizeof(lfn);
#endif
  res = Assert(f_opendir(&dir, path), NULL, "Could not open directory.", path);
  if (res == FR_OK) {
    i = strlen(path);
    while (1) {
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0) break;
      if (fno.fname[0] == '.') continue;
#if _USE_LFN
      fn = *fno.lfname ? fno.lfname : fno.fname;
#else
      fn = fno.fname;
#endif
      if (fno.fattrib & AM_DIR) {
				if (i + 1 + strlen(fn) >= len) {
					printf("Path buffer is too small, file listing aborted.\r\n");
					return FR_INT_ERR;
				} else
          sprintf(&path[i], "/%s", fn);
        res = List(path, len, displayFunc);
        if (res != FR_OK) break;
        path[i] = 0;
      } else
        displayFunc(path, fn);
    }
  }
  return res;
}

// consider fgetc / fgets instead
int SD_Card::Read(char* path, char* buf, UINT btr) {
  FIL fsrc; 
  UINT br = 0;
  FRESULT res = Assert(f_open(&fsrc, path, FA_READ), NULL, "File could not be opened.", path);		
  if (res == FR_OK) {
    res = Assert(
      f_read(&fsrc, buf, btr, &br),
      NULL, "File could not be read.", path
    );     
    f_close(&fsrc);
  }
  return br;
}

void SD_Card::Print(char* path, bool binary) {
  if (FILE* f = fopen(path, "r")) {
		int c;
		while ((c = fgetc(f)) != EOF)
			if (binary)
				printf("%02x", (char) c);
			else
				printf("%c", c);
		printf("\r\n");
		fclose(f);
	} else
		printf("File could not be opened: %s\r\n", path);
}

// consider fputc / fputs instead
int SD_Card::Write(char* path, char* buf, UINT btw) {
  FIL fsrc; 
  UINT bw = 0;
  FRESULT res = Assert(f_open(&fsrc, path, FA_OPEN_ALWAYS | FA_WRITE), NULL, "File could not be opened.", path);		
  if (res == FR_OK) {
    res = Assert(
      f_write(&fsrc, buf, btw, &bw),
      "File successfully written.", "File could not be written.", path
    );     
    f_close(&fsrc);      
  }
  return bw;
}

void SD_Card::MakeFilesystem(void) {
  f_mkfs(0, 0, 512);
}

FRESULT SD_Card::Assert(FRESULT res, const char* msg, const char* error, const char* details) {
  if (res == FR_OK) {
    if (msg != NULL) printf("%s\r\n", msg);
  } else {
    printf("SD ERROR (%d): %s", res, error);
    if (details != NULL) printf(" (%s)", details);
    printf("\r\n");
  }
  return res;
}

void SD_Card::PrintFilename(char* path, char* fn) {
  printf("%s/%s\r\n", path, fn);
}
