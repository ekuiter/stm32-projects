#ifndef  __MAINWINDOW_HPP__
#define  __MAINWINDOW_HPP__

#include <EK/EK_gui.hpp>
	
class MainWindow : public Window<MainWindow> {
  private:
    BUTTON_Handle SheetFolderButton, ChordFileButton, KeyboardButton;
	
	public:
		MainWindow();
	  ~MainWindow();
	  void Initialize(void);
	  void ChooseSheetFolderButtonClicked(void);
	  void ChooseChordFileButtonClicked(void);
	  void KeyboardButtonClicked(void);
	  virtual bool Refresh(void);
};

extern MainWindow* CurrentMainWindow;

#endif
