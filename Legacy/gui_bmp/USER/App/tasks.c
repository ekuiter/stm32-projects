#include <includes.h>                                     
                             
MAKE_TASK(Button, 512u, 3);
MAKE_TASK(GUI, 512u, 4);
MAKE_TASK(Bitmap, 512u, 5);
 
void AppInit(void) {
  TaskGUICreate();							   
}						 

static void TaskGUI(void) {   
  s32 i;
  GUI_Init();
  GUI_SetFont(&GUI_Font32B_ASCII);
  GUI_SetColor(GUI_BLACK);
  GUI_SetBkColor(GUI_WHITE);
  TaskButtonCreate();
  TaskBitmapCreate();
  while (1) {
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringAt("Hello World!", 0, 0);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_DispDecAt(i++, 20, 160, 4);
    if (i > 9999) i = 0;
    OSTimeDlyHMSM(0, 0, 0, 20);
  }
}

static void TaskButton(void) {
  s32 i = 0;
  GUI_SetFont(&GUI_Font32B_ASCII);
  GUI_SetColor(GUI_BLACK);
  GUI_SetBkColor(GUI_WHITE);
  while (1) {
    GUI_DispDecAt(i, 20, 200, 4);
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0) {
      i++;
      if (i > 9999) i = 0;
    }
    OSTimeDlyHMSM(0, 0, 0, 20);
  }
}	

extern const GUI_BITMAP bmPenguins;                        
extern const GUI_BITMAP bmlogo;

static const GUI_BITMAP* lastBitmap = &bmPenguins;

static void TaskBitmap(void) {
  GUI_DrawBitmap(lastBitmap, 0, 0);
  while (1) {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)) {
      if (lastBitmap == &bmPenguins)
        GUI_DrawBitmap(lastBitmap = &bmlogo, 0, 0);
      else
        GUI_DrawBitmap(lastBitmap = &bmPenguins, 0, 0);
      OSTimeDlyHMSM(0, 0, 0, 400);
    }
    OSTimeDlyHMSM(0, 0, 0, 20);
  }
}
