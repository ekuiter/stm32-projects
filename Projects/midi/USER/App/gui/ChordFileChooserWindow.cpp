#include "ChordFileChooserWindow.hpp"
#include "ChordFileWindow.hpp"
#include <gui_style.hpp>
#include <EK/EK_retarget.hpp>
#include <stdio.h>
#include <string>

#define INCLUDE_FROM_CLASS
#include "ChordFileChooserWindowDLG.c"

using std::string;

extern WM_HWIN CreateChordFileChooserWindow(void);
ChordFileChooserWindow* CurrentChordFileChooserWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose, bmopen, bmbusy;

ChordFileChooserWindow::ChordFileChooserWindow(MIDI::MIDI& midi, class SD_Card& SD_Card):
  Window(CreateChordFileChooserWindow), Midi(midi), SD_Card(SD_Card), ChordFileListbox(GetWidget(ID_LISTBOX_0)),
  CloseButton(GetWidget(ID_BUTTON_0)), OpenButton(GetWidget(ID_BUTTON_1)), ShouldClose(false) {
	if (CurrentChordFileChooserWindow != NULL) {
	  printf("Only one CurrentChordFileChooserWindow allowed at a time!\r\n");
		return;
	}
	CurrentChordFileChooserWindow = this;
	
	BUTTON_SetFocussable(CloseButton, 0);
	BUTTON_SetFocussable(OpenButton, 0);
	WIDGET_SetEffect(CloseButton, &WIDGET_Effect_None);
	WIDGET_SetEffect(OpenButton, &WIDGET_Effect_None);
	BUTTON_SetBkColor(CloseButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(CloseButton, BUTTON_BI_UNPRESSED, &bmclose);
	BUTTON_SetBkColor(OpenButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(OpenButton, BUTTON_BI_UNPRESSED, &bmopen);
		
	LISTBOX_SetAutoScrollV(ChordFileListbox, 1);
	LISTBOX_SetScrollbarWidth(ChordFileListbox, 20);
	const int len = 100;
	char buf[len] = CHORDFILES_PATH;
  SD_Card.List(buf, len, AddChordFile);
}
	
ChordFileChooserWindow::~ChordFileChooserWindow() {
  CurrentChordFileChooserWindow = NULL;
}

void ChordFileChooserWindow::AddChordFile(char* path, char* fn) {
	ChordFileDescriptor chordFileDescriptor(strtok(fn, "."));
  LISTBOX_AddString(CurrentChordFileChooserWindow->ChordFileListbox, chordFileDescriptor.ToString().c_str());
	CurrentChordFileChooserWindow->ChordFileDescriptors.push_back(chordFileDescriptor);
}

void ChordFileChooserWindow::CloseButtonClicked(void) {
	ShouldClose = true;
}

void ChordFileChooserWindow::OpenButtonClicked(void) {
	GUI_EnterBlocking(CloseButton, &bmbusy);
	OSTimeDlyHMSM(0, 0, 0, 300);
	string fileName = ChordFileDescriptors[LISTBOX_GetSel(ChordFileListbox)].FileName;
	ChordFileWindow* chordFileWindow = new ChordFileWindow(fileName, Midi, SD_Card);
	while (chordFileWindow->Refresh())
		GUI_Delay(50);
	delete chordFileWindow;
	GUI_LeaveBlocking(CloseButton, &bmclose);
}

bool ChordFileChooserWindow::Refresh(void) {
  return !ShouldClose;
}
