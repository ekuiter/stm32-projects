#include "ChooserWindow.hpp"
#include <gui_style.hpp>

#define INCLUDE_FROM_CLASS
#include "ChooserWindowDLG.c"

using std::string;

ChooserWindow* CurrentChooserWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose, bmopen, bmbusy;

ChooserWindow::ChooserWindow(createWindowFunc_t createWindowFunc, class SD_Card& SD_Card):
  Window(createWindowFunc), SD_Card(SD_Card), CloseButton(GetWidget(ID_BUTTON_0)), 
  OpenButton(GetWidget(ID_BUTTON_1)), ShouldClose(false), Listbox(GetWidget(ID_LISTBOX_0)) {
	if (CurrentChooserWindow != NULL) {
	  printf("Only one ChooserWindow allowed at a time!\r\n");
		return;
	}
	CurrentChooserWindow = this;
	SetButtonStyle(CloseButton, &bmclose, GUI_STYLE_MAIN);
	SetButtonStyle(OpenButton, &bmopen, GUI_STYLE_MAIN);		
	LISTBOX_SetAutoScrollV(Listbox, 1);
	LISTBOX_SetScrollbarWidth(Listbox, 20);
}
	
ChooserWindow::~ChooserWindow() {
  CurrentChooserWindow = NULL;
}

void ChooserWindow::CloseButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
	ShouldClose = true;
}

void ChooserWindow::OpenButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
	int selection = LISTBOX_GetSel(Listbox);
	if (selection >= 0)
	  OpenFile(FileNames[selection]);
}

bool ChooserWindow::Refresh(void) {
  return !ShouldClose;
}
