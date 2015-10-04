#ifndef __EK_SD_HPP
#define __EK_SD_HPP

#include "EK_config.hpp"
#include <stdbool.h>
#include <FATFS/src/ff.h>
#include <SD_Card/sdio_sd.h>

class SD_Card {
	typedef void (*displayFunc_t)(char*, char*);
  
	private:
		FATFS fs;
	  FRESULT Assert(FRESULT, const char*, const char*, const char*);
		static void PrintFilename(char* path, char* fn);
	
	public:
		SD_Card(void);
		void Mount(void);
	  DWORD GetSize(DWORD*);
	  void PrintSize(void);
	  FRESULT List(char*, int, displayFunc_t = PrintFilename);
	  int Read(char*, char*, UINT);
	  void Print(char*, bool = false);
	  int Write(char*, char*, UINT);
	  void MakeFilesystem(void);
};

#endif
