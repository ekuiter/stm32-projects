#include "SheetFolderChooserWindow.hpp"
#include "SheetsWindow.hpp"
#include "SearchWindow.hpp"
#include <EK/EK_retarget.hpp>
#include <EK/EK_usart.hpp>
#include <string.h>
#include <gui_style.hpp>

#define INCLUDE_FROM_CLASS
#include "SheetFolderChooserWindowDLG.c"

#define LINE_BUFFER_LENGTH 100

extern WM_HWIN CreateSheetFolderChooserWindow(void);
extern GUI_CONST_STORAGE GUI_BITMAP bmsearch, bmclose, bmbusy;

SheetFolderChooserWindow::SheetFolderChooserWindow(class SD_Card& SD_Card): ChooserWindow(CreateSheetFolderChooserWindow, SD_Card), SearchButton(GetWidget(ID_BUTTON_2)) {
	SetButtonStyle(SearchButton, &bmsearch, GUI_STYLE_MAIN);
	
  const int len = 100;
	char buf[len] = SHEETFOLDERS_PATH;
  SD_Card.List(buf, len, AddFile);
	std::sort(FileNames.begin(), FileNames.end());
	std::sort(FileDescriptions.begin(), FileDescriptions.end());
	for (int i = 0; i < FileDescriptions.size(); i++)
	  LISTBOX_AddString(Listbox, FileDescriptions[i].c_str());
}

void SheetFolderChooserWindow::AddFile(char* path, char* fn) {
	string fileName = strtok(fn, ".");
	FILE* f = fopen((string(SHEETFOLDERS_PATH) + "/" + fileName + SHEETFOLDERS_SUFFIX).c_str(), "r");
	if (!f) {
		printf("File could not be opened: %s\r\n", path);
		return;
	}
	char buf[LINE_BUFFER_LENGTH];
	fgets(buf, LINE_BUFFER_LENGTH, f);
  fclose(f);
	Heap.Debug<string>("Pushing File Name");
	CurrentChooserWindow->FileNames.push_back(fileName);
	Heap.Debug<string>("Pushing File Description");
	((SheetFolderChooserWindow*) CurrentChooserWindow)->FileDescriptions.push_back("#" + fileName + ": " + buf);
}

static string search;

static int ProcessSheetsWindowResult(void* sheetsWindow) {
	return ((SheetsWindow*) sheetsWindow)->GetShouldTriggerSearch();
}

void SheetFolderChooserWindow::OpenFile(string fileName) {
	if (RunDialog(new SheetsWindow(fileName, SD_Card, SheetsWindow::FILENAME), ProcessSheetsWindowResult))
		RunSearch();
}

static int ProcessSearchWindowResult(void* searchWindow) {
	bool shouldReturnResult = ((SearchWindow*) searchWindow)->GetShouldReturnResult();
	if (shouldReturnResult)
		search = ((SearchWindow*) searchWindow)->GetSearch();
	return shouldReturnResult;
}

void SheetFolderChooserWindow::RunSearch(void) {
  if (!RunDialog(new SearchWindow(SD_Card), ProcessSearchWindowResult))
		return;
  if (RunDialog(new SheetsWindow(search, SD_Card, SheetsWindow::SEARCH), ProcessSheetsWindowResult))
		RunSearch();
}

void SheetFolderChooserWindow::SearchButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
  RunSearch();
}
