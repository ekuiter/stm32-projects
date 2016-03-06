#include "MainWindow.hpp"
#include <gui_style.hpp>
#include <EK/EK_sd.hpp>
#include "SheetFolderChooserWindow.hpp"
#include "ChordFileChooserWindow.hpp"
#include "KeyboardWindow.hpp"

#define INCLUDE_FROM_CLASS
#include "MainWindowDLG.c"

extern WM_HWIN CreateMainWindow(void);
MainWindow* CurrentMainWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmsheetFolder, bmchordFile;
extern SD_Card SD_Card;
extern MIDI::MIDI Midi;

MainWindow::MainWindow():
  Window(CreateMainWindow),  SheetFolderButton(GetWidget(ID_BUTTON_0)), 
  ChordFileButton(GetWidget(ID_BUTTON_1)), KeyboardButton(GetWidget(ID_BUTTON_2)) {
	if (CurrentMainWindow != NULL) {
	  printf("Only one MainWindow allowed at a time!\r\n");
		return;
	}
	CurrentMainWindow = this;
	Initialize();
}
	
MainWindow::~MainWindow() {
  CurrentMainWindow = NULL;
}

void MainWindow::Initialize(void) {
	ForceButtonStyle(SheetFolderButton, &bmsheetFolder, GUI_STYLE_MAIN);
	ForceButtonStyle(ChordFileButton, &bmchordFile, GUI_STYLE_MAIN);
}

void MainWindow::ChooseSheetFolderButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, SheetFolderButton);
	RunDialog(new SheetFolderChooserWindow(SD_Card));
}

void MainWindow::ChooseChordFileButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, ChordFileButton);
	RunDialog(new ChordFileChooserWindow(Midi, SD_Card));
}

void MainWindow::KeyboardButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, ChordFileButton);
	RunDialog(new KeyboardWindow(Midi));
	Initialize();
	WM_Paint(Handle);
}

bool MainWindow::Refresh(void) {
  return true;
}
