#include <includes.h>
#include <EK.hpp>
#include <vector>

static void RunTouchPanelTask(void);
static void RunUSARTTask(void);
static void RunSDTask(void);
static void RunGUITask(void);
static Task<64> TouchPanelTask(3, RunTouchPanelTask);
static Task<256> USARTTask(4, RunUSARTTask);
Task<512> SDTask(5, RunSDTask);
static Task<512> GUITask(6, RunGUITask);

static USART Serial(USART1, 115200);
static SD_Card SD_Card;

void AppInit(void) {
	TouchPanelTask.Run();
	GUITask.Run();
	USARTTask.Run();
}

extern void CreatePrintableMainWindow(void);

static void RunGUITask(void) {
	GUI_Touch_Config();
  CreatePrintableMainWindow();
  printf("Welcome!\r\nPress \"Mount SD\" to begin.\r\n");
  while (1)
    GUI_Delay(100);
}

static void RunTouchPanelTask(void) {   
	while (1) {
	 GUI_TOUCH_Exec();
	 OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

void ListFiles(void) {
  const int len = 512;
	char path[len] = "0:";
  SD_Card.List(path, len);
}

void ReadFile(char* filename) {
	const int len = 512;
	char buf[len];
  buf[SD_Card.Read(filename, buf, len)] = 0;
	printf("%s\r\n", buf);
}

static const int len = 512, imgLen = 1024;
static char buf[len], str[] = "Testtextblabla", imgBuf[imgLen];

static void RunUSARTTask(void) {
  while(1) {
		printf("$ ");
		printf("> %s\r\n", Serial.ReadLn(buf, len));
		if (strstr(buf, "mount") != NULL)
			SDTask.Run();
		else if (strstr(buf, "list") != NULL)
			ListFiles();
		else if (strstr(buf, "read") != NULL)
			ReadFile(&buf[5]);
		else if (strstr(buf, "write") != NULL)
			SD_Card.Write(&buf[6], str, strlen(str));
		else if (strstr(buf, "show") != NULL) {
		  SD_Card.Read(&buf[5], imgBuf, imgLen);
      GUI_DrawStreamedBitmap((GUI_BITMAP_STREAM*) imgBuf, 0, 0);
		}
	}
}

static void RunSDTask(void) {                 
	SD_Card.Mount();
  SD_Card.PrintSize();
  while (1)
    OSTimeDlyHMSM(0, 1, 0, 0);
}
