#ifndef  __CHOOSERWINDOW_HPP__
#define  __CHOOSERWINDOW_HPP__

#include <EK/EK_tasks.hpp>
#include <EK/EK_gui.hpp>
#include <EK/EK_sd.hpp>
	
class ChooserWindow : public Window<ChooserWindow> {
	protected:
		SD_Card& SD_Card;
	  virtual void OpenFile(string) = 0;
		
  private:
	  BUTTON_Handle CloseButton, OpenButton;
		bool ShouldClose;
	
  public:
	  vector<string> FileNames;
	  LISTBOX_Handle Listbox;
		ChooserWindow(class SD_Card&);
	  ~ChooserWindow();
	  void CloseButtonClicked(void);
	  void OpenButtonClicked(void);
	  virtual bool Refresh(void);
};

extern ChooserWindow* CurrentChooserWindow;

#endif
