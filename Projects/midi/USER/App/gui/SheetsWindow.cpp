#include "SheetsWindow.hpp"
#include "SheetFolderChooserWindow.hpp"
#include <gui_style.hpp>
#include <cctype>

#define INCLUDE_FROM_CLASS
#include "SheetsWindowDLG.c"

#define LINE_BUFFER_LENGTH 100
#define LISTVIEW_SCROLL_ITEMS 3

extern WM_HWIN CreateSheetsWindow(void);
SheetsWindow* CurrentSheetsWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose, bmsearch, bmup, bmdown, bmbusy;

SheetsWindow::SheetsWindow(string query, SD_Card& SD_Card, enum Mode mode): Window(CreateSheetsWindow), CloseButton(GetWidget(ID_BUTTON_0)),
  SearchButton(GetWidget(ID_BUTTON_1)), UpButton(GetWidget(ID_BUTTON_2)), DownButton(GetWidget(ID_BUTTON_3)),
	Listview(GetWidget(ID_LISTVIEW_0)),	Mode(mode), Query(query), ShouldClose(false), ShouldTriggerSearch(false) {
	if (CurrentSheetsWindow != NULL) {
	  printf("Only one SheetsWindow allowed at a time!\r\n");
		return;
	}
  CurrentSheetsWindow = this;
	SetButtonStyle(CloseButton, &bmclose, GUI_STYLE_MAIN);
	SetButtonStyle(SearchButton, &bmsearch, GUI_STYLE_MAIN);
	SetButtonStyle(UpButton, &bmup, GUI_STYLE_MAIN);
	SetButtonStyle(DownButton, &bmdown, GUI_STYLE_MAIN);
	
	if (Mode == FILENAME) {
	  CurrentSheetsWindow->ReadFile((string(SHEETFOLDERS_PATH) + "/" + Query + SHEETFOLDERS_SUFFIX).c_str(), Query);
	} else if (Mode == SEARCH) {
		if (Query.length() < 3) {
		  const char* rowBuf[3] = { "", "Search too short", "" };
  		LISTVIEW_AddRow(Listview, rowBuf);
		} else {
	    const int len = 100;
		  char buf[len] = SHEETFOLDERS_PATH;
		  SD_Card.List(buf, len, AddFile);
			if (LISTVIEW_GetNumRows(Listview) == 0) {
			  const char* rowBuf[3] = { "", "No sheets found", "" };
  		  LISTVIEW_AddRow(Listview, rowBuf);
			}
		}
	}
}
	
void SheetsWindow::AddFile(char* path, char* fn) {
	string fileName = strtok(fn, ".");
	CurrentSheetsWindow->ReadFile((string(SHEETFOLDERS_PATH) + "/" + fileName + SHEETFOLDERS_SUFFIX).c_str(), fileName);
}

static bool CompareCharPredicate(char ch1, char ch2) {
		return std::toupper(ch1) == std::toupper(ch2);
}

static int stristr(string str1, string str2) {
    string::const_iterator it = std::search(str1.begin(), str1.end(), str2.begin(), str2.end(), CompareCharPredicate);
    return it != str1.end();
}

void SheetsWindow::ReadFile(const char* path, string fileName) {
  FILE* f = fopen(path, "r");
	if (!f) {
		printf("File could not be opened: %s\r\n", path);
		return;
	}
	char buf[LINE_BUFFER_LENGTH], titleBuf[LINE_BUFFER_LENGTH / 2], artistBuf[LINE_BUFFER_LENGTH / 2];
	fgets(buf, LINE_BUFFER_LENGTH, f);
	const char* rowBuf[3] = { fileName.c_str() };
	while (!feof(f)) {
		fgets(buf, LINE_BUFFER_LENGTH, f);
		if (strcmp(buf, "\r\n") == 0 || buf[0] == '#')
			continue;
		if (sscanf(buf, "\"%49[^\"]\",\"%49[^\"]\"\r\n", titleBuf, artistBuf) < 2)
			artistBuf[0] = '\0';
		if (Mode == SEARCH && !stristr(titleBuf, Query) && !stristr(artistBuf, Query))
			continue;
		rowBuf[1] = titleBuf;
		rowBuf[2] = artistBuf;
		LISTVIEW_AddRow(Listview, rowBuf);
	}		
	fclose(f);
}
	
SheetsWindow::~SheetsWindow() {
  CurrentSheetsWindow = NULL;
}

void SheetsWindow::CloseButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
	ShouldClose = true;
}
	
void SheetsWindow::SearchButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
  ShouldClose = true;
	ShouldTriggerSearch = true;
}

void SheetsWindow::UpButtonClicked(void) {
	LISTVIEW_SetSel(Listview, LISTVIEW_GetSel(Listview) - LISTVIEW_SCROLL_ITEMS);
}
	
void SheetsWindow::DownButtonClicked(void) {
  LISTVIEW_SetSel(Listview, LISTVIEW_GetSel(Listview) + LISTVIEW_SCROLL_ITEMS);
}

bool SheetsWindow::Refresh(void) {
  return !ShouldClose;
}

bool SheetsWindow::GetShouldTriggerSearch(void) {
  return ShouldTriggerSearch;
}
