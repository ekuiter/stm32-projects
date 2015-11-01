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
	SetButtonStyle(SheetFolderButton, &bmsheetFolder, GUI_STYLE_MAIN);
	SetButtonStyle(ChordFileButton, &bmchordFile, GUI_STYLE_MAIN);
}
	
MainWindow::~MainWindow() {
  CurrentMainWindow = NULL;
}

void MainWindow::ChooseSheetFolderButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, SheetFolderButton);
	RunDialog(new SheetFolderChooserWindow(SD_Card));
}

void MainWindow::ChooseChordFileButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, ChordFileButton);
	RunDialog(new ChordFileChooserWindow(Midi, SD_Card));
}

bool MainWindow::Refresh(void) {
  return true;
}
