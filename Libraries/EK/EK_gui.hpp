#ifndef __EK_GUI_HPP
#define __EK_GUI_HPP

#include <stdio.h>
#include <stdint.h>
#include <uCOS-II/Source/ucos_ii.h>
#include <uCGUI_LIB/USER/uCGUI/Core/GUI.h>
#include <uCGUI_LIB/USER/uCGUI/WM/WM.h>
#include <uCGUI_LIB/USER/uCGUI/Widget/DIALOG.h>
#include <uCGUI_LIB/USER/uCGUI/Widget/TEXT.h>
#include <string>
	
#define GUI_FONT_13_1 &GUI_Font13_1
#define GUI_FONT_16_1 &GUI_Font16_1
#define GUI_FONT_24_1 &GUI_Font24_1

#define LISTBOX_TEXT_LENGTH 30

void GUI_Touch_Config(int, int, int, int, int, int);
void GUI_Touch_Config(void);
void GUI_Touch_Config_Runtime(void);
void GUI_EnterBlocking(BUTTON_Handle, const GUI_BITMAP*);
void GUI_LeaveBlocking(BUTTON_Handle, const GUI_BITMAP*);

using std::string;

template<typename T>
class Window {	
  protected:
		typedef WM_HWIN (*createWindowFunc_t)(void);
    typedef void (T::*buttonClickFunc_t)(void);	
		WM_HWIN Handle;
	  createWindowFunc_t CreateWindowFunc;
	  uint32_t LastClick;
	
	public:
		Window(createWindowFunc_t createWindowFunc): Handle(0), CreateWindowFunc(createWindowFunc), LastClick(0) {
		  Handle = CreateWindowFunc();
		}
			
		~Window() {
			if (Handle)
		    GUI_EndDialog(Handle, 0);
		}
		
		WM_HWIN GetHandle(void) {
		  return Handle;
		}
		
		WM_HWIN GetWidget(int id) {
			return WM_GetDialogItem(Handle, id);
		}
		
		void DebouncedClick(buttonClickFunc_t buttonClickFunc, int debounceMs) {
			uint32_t currentClick = OSTimeGet();
			if (currentClick > LastClick + debounceMs * (OS_TICKS_PER_SEC / 1000)) {
				LastClick = currentClick;
				(reinterpret_cast<T*>(this)->*buttonClickFunc)();
			}
		}
		
		string GetListboxText(LISTBOX_Handle listbox, int i) {
			const int len = LISTBOX_TEXT_LENGTH;
			char buf[len] = {0};
			LISTBOX_GetItemText(listbox, i, buf, len - 1);
			return string(buf);
		}
		
		string GetListboxText(LISTBOX_Handle listbox) {
			return GetListboxText(listbox, LISTBOX_GetSel(listbox));
		}
		
		virtual bool Refresh(void) = 0;
};

#endif
