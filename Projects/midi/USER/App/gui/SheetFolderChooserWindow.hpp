#ifndef  __SHEETFOLDERCHOOSERWINDOW_HPP__
#define  __SHEETFOLDERCHOOSERWINDOW_HPP__

#include "ChooserWindow.hpp"

#define SHEETFOLDER_PATH "sheetfolders"
	
class SheetFolderChooserWindow : public ChooserWindow {
  private:
    static void AddFile(char*, char*);
		virtual void OpenFile(string);
		
	public:
		SheetFolderChooserWindow(class SD_Card&);
};

#endif
