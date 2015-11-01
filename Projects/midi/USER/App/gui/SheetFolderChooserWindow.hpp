#ifndef  __SHEETFOLDERCHOOSERWINDOW_HPP__
#define  __SHEETFOLDERCHOOSERWINDOW_HPP__

#include "ChooserWindow.hpp"

#define SHEETFOLDERS_PATH "sheetfolders"
#define SHEETFOLDERS_SUFFIX ".txt"
	
class SheetFolderChooserWindow : public ChooserWindow {
  private:
		BUTTON_Handle SearchButton;
		vector<string> FileDescriptions;
    static void AddFile(char*, char*);
		virtual void OpenFile(string);
	  void RunSearch(void);
		
	public:
		SheetFolderChooserWindow(class SD_Card&);
	  void SearchButtonClicked(void);
};

#endif
