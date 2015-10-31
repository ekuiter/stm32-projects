#include "MainWindow.hpp"
#include <gui_style.hpp>
#include <EK/EK_sd.hpp>
#include <EK/EK_gpio.hpp>
#include "SheetFolderChooserWindow.hpp"
#include "ChordFileChooserWindow.hpp"

#define INCLUDE_FROM_CLASS
#include "MainWindowDLG.c"

extern WM_HWIN CreateMainWindow(void);
MainWindow* CurrentMainWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmsheetFolder, bmchordFile;
extern SD_Card SD_Card;
extern MIDI::MIDI Midi;
extern GPIO_Pin UserKeyA, UserKeyB;

MainWindow::MainWindow():
  Window(CreateMainWindow),  SheetFolderButton(GetWidget(ID_BUTTON_0)), 
  ChordFileButton(GetWidget(ID_BUTTON_1)) {
	if (CurrentMainWindow != NULL) {
	  printf("Only one MainWindow allowed at a time!\r\n");
		return;
	}
	CurrentMainWindow = this;
	
	BUTTON_SetFocussable(SheetFolderButton, 0);
	BUTTON_SetFocussable(ChordFileButton, 0);
	WIDGET_SetEffect(SheetFolderButton, &WIDGET_Effect_None);
	WIDGET_SetEffect(ChordFileButton, &WIDGET_Effect_None);
	BUTTON_SetBkColor(SheetFolderButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(SheetFolderButton, BUTTON_BI_UNPRESSED, &bmsheetFolder);
	BUTTON_SetBkColor(ChordFileButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(ChordFileButton, BUTTON_BI_UNPRESSED, &bmchordFile);
}
	
MainWindow::~MainWindow() {
  CurrentMainWindow = NULL;
}

void MainWindow::ChooseSheetFolderButtonClicked(void) {
	SheetFolderChooserWindow* sheetFolderChooserWindow = new SheetFolderChooserWindow(SD_Card);
	while (sheetFolderChooserWindow->Refresh())
		GUI_Delay(50);
	delete sheetFolderChooserWindow;
}

void MainWindow::ChooseChordFileButtonClicked(void) {
	ChordFileChooserWindow* chordFileChooserWindow = new ChordFileChooserWindow(Midi, SD_Card);
	while (chordFileChooserWindow->Refresh())
		GUI_Delay(50);
	delete chordFileChooserWindow;
}

bool MainWindow::Refresh(void) {
  return true;
}
