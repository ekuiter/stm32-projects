#ifndef  __SHEETSWINDOW_HPP__
#define  __SHEETSWINDOW_HPP__

#include <EK/EK_gui.hpp>
#include <EK/EK_sd.hpp>
#include <vector>
#include "LISTVIEW.h"
	
class SheetsWindow : public Window<SheetsWindow> {
	public:
		enum Mode { FILENAME, SEARCH };

	private:
	  BUTTON_Handle CloseButton, SearchButton, UpButton, DownButton;
	  LISTVIEW_Handle Listview;
	  enum Mode Mode;
	  string Query;
	  bool ShouldClose, ShouldTriggerSearch;
	  static void AddFile(char*, char*);
	  void ReadFile(const char*, string);
	
	public:
		SheetsWindow(string, SD_Card&, enum Mode);
	  ~SheetsWindow();
	  void CloseButtonClicked(void);
	  void SearchButtonClicked(void);
	  void UpButtonClicked(void);
	  void DownButtonClicked(void);
	  virtual bool Refresh(void);
	  bool GetShouldTriggerSearch(void);
};

extern SheetsWindow* CurrentSheetsWindow;

#endif
