#include "SheetFolderChooserWindow.hpp"
#include <string.h>

SheetFolderChooserWindow::SheetFolderChooserWindow(class SD_Card& SD_Card): ChooserWindow(SD_Card) {
  const int len = 100;
	char buf[len] = SHEETFOLDER_PATH;
  SD_Card.List(buf, len, AddFile);
}

void SheetFolderChooserWindow::AddFile(char* path, char* fn) {
	string fileName = strtok(fn, ".");
  LISTBOX_AddString(CurrentChooserWindow->Listbox, fileName.c_str());
	CurrentChooserWindow->FileNames.push_back(fileName);
}

void SheetFolderChooserWindow::OpenFile(string fileName) {
	
}
