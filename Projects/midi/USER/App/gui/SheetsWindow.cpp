#include "SheetsWindow.hpp"
#include "SheetFolderChooserWindow.hpp"
#include <gui_style.hpp>

#define INCLUDE_FROM_CLASS
#include "SheetsWindowDLG.c"

#define LINE_BUFFER_LENGTH 100
#define LISTVIEW_SCROLL_ITEMS 3

extern WM_HWIN CreateSheetsWindow(void);
SheetsWindow* CurrentSheetsWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose, bmsearch, bmup, bmdown;

SheetsWindow::SheetsWindow(string fileName): Window(CreateSheetsWindow), CloseButton(GetWidget(ID_BUTTON_0)),
  SearchButton(GetWidget(ID_BUTTON_1)), UpButton(GetWidget(ID_BUTTON_2)), DownButton(GetWidget(ID_BUTTON_3)),
	Listview(GetWidget(ID_LISTVIEW_0)),	ShouldClose(false), ShouldTriggerSearch(false) {
	if (CurrentSheetsWindow != NULL) {
	  printf("Only one SheetsWindow allowed at a time!\r\n");
		return;
	}
  CurrentSheetsWindow = this;
	
	BUTTON_SetFocussable(CloseButton, 0);
	BUTTON_SetFocussable(SearchButton, 0);
	BUTTON_SetFocussable(UpButton, 0);
	BUTTON_SetFocussable(DownButton, 0);
	WIDGET_SetEffect(CloseButton, &WIDGET_Effect_None);
	WIDGET_SetEffect(SearchButton, &WIDGET_Effect_None);
	WIDGET_SetEffect(UpButton, &WIDGET_Effect_None);
	WIDGET_SetEffect(DownButton, &WIDGET_Effect_None);
	BUTTON_SetBkColor(CloseButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(CloseButton, BUTTON_BI_UNPRESSED, &bmclose);
	BUTTON_SetBkColor(SearchButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(SearchButton, BUTTON_BI_UNPRESSED, &bmsearch);
	BUTTON_SetBkColor(UpButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(UpButton, BUTTON_BI_UNPRESSED, &bmup);
	BUTTON_SetBkColor(DownButton, BUTTON_BI_UNPRESSED, GUI_STYLE_MAIN);
	BUTTON_SetBitmap(DownButton, BUTTON_BI_UNPRESSED, &bmdown);
	
	const char* path = (string(SHEETFOLDERS_PATH) + "/" + fileName + SHEETFOLDERS_SUFFIX).c_str();
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
	ShouldClose = true;
}
	
void SheetsWindow::SearchButtonClicked(void) {
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
