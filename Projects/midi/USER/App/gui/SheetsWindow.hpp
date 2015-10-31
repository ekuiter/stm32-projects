#ifndef  __SHEETSWINDOW_HPP__
#define  __SHEETSWINDOW_HPP__

#include <EK/EK_gui.hpp>
#include <vector>
#include "LISTVIEW.h"

using std::vector;

struct Sheet {
  string Title, Artist;
	Sheet(string title, string artist): Title(title), Artist(artist) {}
};
	
class SheetsWindow : public Window<SheetsWindow> {
	private:
	  BUTTON_Handle CloseButton, SearchButton, UpButton, DownButton;
	  LISTVIEW_Handle Listview;
	  bool ShouldClose, ShouldTriggerSearch;
	
	public:
		SheetsWindow(string);
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
