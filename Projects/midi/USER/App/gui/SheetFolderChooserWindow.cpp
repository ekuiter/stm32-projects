#include "SheetFolderChooserWindow.hpp"
#include "SheetsWindow.hpp"
#include <EK/EK_retarget.hpp>
#include <string.h>

#define LINE_BUFFER_LENGTH 100

SheetFolderChooserWindow::SheetFolderChooserWindow(class SD_Card& SD_Card): ChooserWindow(SD_Card) {
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

void SheetFolderChooserWindow::OpenFile(string fileName) {
	SheetsWindow* sheetsWindow = new SheetsWindow(fileName);
	while (sheetsWindow->Refresh())
		GUI_Delay(50);
	if (sheetsWindow->GetShouldTriggerSearch())
		printf("Should trigger search.\n");
	delete sheetsWindow;
}
