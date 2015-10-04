#include "EK_gui.hpp"
#include "EK_retarget.hpp"

extern "C" void TP_Init(void);
extern "C" void _ExecCalibration(void);
extern "C" int CalibrationComplete;

void GUI_Touch_Config(int width, int height, int left, int right, int top, int bottom) {
  GUI_Init();
  TP_Init();
  if (width == 0 || height == 0)
    _ExecCalibration();
  else {
    GUI_TOUCH_Calibrate(GUI_COORD_X, 0, width, left, right);
    GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, height, top, bottom);
    CalibrationComplete = 1;
  }
}

void GUI_Touch_Config(void) {
  GUI_Touch_Config(320, 240, 114, 3937, 232, 3830);
}

void GUI_Touch_Config_Runtime(void) {
  GUI_Touch_Config(0, 0, 0, 0, 0, 0);
}

void GUI_EnterBlocking(BUTTON_Handle button, const GUI_BITMAP* bitmap) {
	BUTTON_SetBitmap(button, BUTTON_BI_UNPRESSED, bitmap);
	GUI_Exec();
}

void GUI_LeaveBlocking(BUTTON_Handle button, const GUI_BITMAP* bitmap) {
	BUTTON_SetBitmap(button, BUTTON_BI_UNPRESSED, bitmap);
	GUI_Exec();
}
