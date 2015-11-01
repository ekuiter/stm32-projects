#include "SearchWindow.hpp"
#include <gui_style.hpp>
#include <string.h>

#define INCLUDE_FROM_CLASS
#include "SearchWindowDLG.c"

extern WM_HWIN CreateSearchWindow(void);
SearchWindow* CurrentSearchWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose, bmsearch, bmback, bmbusy;

SearchWindow::SearchWindow(SD_Card& SD_Card): Window(CreateSearchWindow), CloseButton(GetWidget(ID_BUTTON_0)), SearchButton(GetWidget(ID_BUTTON_1)),
  BackspaceButton(GetWidget(ID_BUTTON_28)), SearchEdit(GetWidget(ID_EDIT_0)), ShouldClose(false), ShouldReturnResult(false) {
	if (CurrentSearchWindow != NULL) {
	  printf("Only one SearchWindow allowed at a time!\r\n");
		return;
	}
  CurrentSearchWindow = this;
	SetButtonStyle(CloseButton, &bmclose, GUI_STYLE_MAIN);
	SetButtonStyle(SearchButton, &bmsearch, GUI_STYLE_MAIN);
	SetButtonStyle(BackspaceButton, &bmback, GUI_STYLE_MAIN);
}
	
SearchWindow::~SearchWindow() {
  CurrentSearchWindow = NULL;
}

void SearchWindow::CloseButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
	ShouldClose = true;
}
	
void SearchWindow::SearchButtonClicked(void) {
	Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
  ShouldClose = true;
	ShouldReturnResult = true;
}

void SearchWindow::CharButtonClicked(char ch) {
	const int len = 100;
	char buf[len];
  EDIT_GetText(SearchEdit, buf, len - 1);
	int curLen = strlen(buf);
	buf[curLen] = ch;
	buf[curLen + 1] = '\0'; 
  EDIT_SetText(SearchEdit, buf);
}

void SearchWindow::BackspaceButtonClicked(void) {
	const int len = 100;
	char buf[len];
  EDIT_GetText(SearchEdit, buf, len);
	if (strlen(buf) == 0)
		return;
	buf[strlen(buf) - 1] = '\0';
  EDIT_SetText(SearchEdit, buf);
}

bool SearchWindow::Refresh(void) {
  return !ShouldClose;
}

bool SearchWindow::GetShouldReturnResult(void) {
  return ShouldReturnResult;
}

string SearchWindow::GetSearch(void) {
	const int len = 100;
	char buf[len];
  EDIT_GetText(SearchEdit, buf, len);
	return string(buf);
}
