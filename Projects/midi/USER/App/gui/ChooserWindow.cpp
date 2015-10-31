#include "ChooserWindow.hpp"
#include <gui_style.hpp>

#define INCLUDE_FROM_CLASS
#include "ChooserWindowDLG.c"

using std::string;

extern WM_HWIN CreateChooserWindow(void);
ChooserWindow* CurrentChooserWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose, bmopen, bmbusy;

ChooserWindow::ChooserWindow(class SD_Card& SD_Card):
  Window(CreateChooserWindow), SD_Card(SD_Card), CloseButton(GetWidget(ID_BUTTON_0)), 
  OpenButton(GetWidget(ID_BUTTON_1)), ShouldClose(false), Listbox(GetWidget(ID_LISTBOX_0)) {
	if (CurrentChooserWindow != NULL) {
	  printf("Only one ChooserWindow allowed at a time!\r\n");
		return;
	}
	CurrentChooserWindow = this;
	
	BUTTON_SetFocussable(CloseButton, 0);
	BUTTON_SetFocussable(OpenButton, 0);
	WIDGET_SetEffect(CloseButton, &WIDGET_Effect_None);
	WIDGET_SetEffect(OpenButton, &WIDGET_Effect_None);
	BUTTON_SetBkColor(CloseButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(CloseButton, BUTTON_BI_UNPRESSED, &bmclose);
	BUTTON_SetBkColor(OpenButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(OpenButton, BUTTON_BI_UNPRESSED, &bmopen);
		
	LISTBOX_SetAutoScrollV(Listbox, 1);
	LISTBOX_SetScrollbarWidth(Listbox, 20);
}
	
ChooserWindow::~ChooserWindow() {
  CurrentChooserWindow = NULL;
}

void ChooserWindow::CloseButtonClicked(void) {
	ShouldClose = true;
}

void ChooserWindow::OpenButtonClicked(void) {
	GUI_EnterBlocking(CloseButton, &bmbusy);
	OSTimeDlyHMSM(0, 0, 0, 300);
	int selection = LISTBOX_GetSel(Listbox);
	if (selection >= 0)
	  OpenFile(FileNames[selection]);
	GUI_LeaveBlocking(CloseButton, &bmclose);
}

bool ChooserWindow::Refresh(void) {
  return !ShouldClose;
}
