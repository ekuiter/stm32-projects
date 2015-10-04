#include <includes.h>     

MAKE_TASK(TouchPanel, 256u, 3);
MAKE_TASK(SD, 256u, 4);
MAKE_TASK(GUI, 512u, 5);
 
void AppInit(void) {
  USART_Config(115200);
  TaskTouchPanelCreate();
  TaskGUICreate();
}							 

static void TaskGUI(void) {   
  GUI_Touch_Config();
  TaskSDCreate();

  while (1)
    GUI_Delay(100);
}

static void TaskTouchPanel(void) {
  while (1) {
   GUI_TOUCH_Exec();
   OSTimeDlyHMSM(0, 0, 0, 20);
  }
}

char buf[24000];

static void TaskSD(void) {
  int br;
  SD_Config();
  SD_PrintSize();
  br = SD_ReadFile("0:/logo.dta", buf, 24000);
  printf("Bytes read: %d\r\n", br);
  GUI_DrawStreamedBitmap((void*) buf, 0, 0);
  while (1)
    OSTimeDlyHMSM(0, 1, 0, 0);
}
