#ifndef  __SEARCHWINDOW_HPP__
#define  __SEARCHWINDOW_HPP__

#include <EK/EK_gui.hpp>
#include <EK/EK_sd.hpp>
	
class SearchWindow : public Window<SearchWindow> {
	public:

	private:
	  BUTTON_Handle CloseButton, SearchButton, BackspaceButton;
	  EDIT_Handle SearchEdit;
	  bool ShouldClose, ShouldReturnResult;
	
	public:
		SearchWindow(SD_Card&);
	  ~SearchWindow();
	  void CloseButtonClicked(void);
	  void SearchButtonClicked(void);
	  void CharButtonClicked(char);
	  void BackspaceButtonClicked(void);
	  virtual bool Refresh(void);
	  bool GetShouldReturnResult(void);
	  string GetSearch(void);
};

extern SearchWindow* CurrentSearchWindow;

#endif
