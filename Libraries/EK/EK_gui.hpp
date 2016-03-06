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
#include <map>

using std::map;

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
		WM_HWIN Handle;
	  map<BUTTON_Handle, const GUI_BITMAP*> ButtonBitmaps;
	
  private:
    typedef void (T::*buttonClickFunc_t)(void);	
	  createWindowFunc_t CreateWindowFunc;
	  uint32_t LastClick;
	
	  void SetButtonStyle(BUTTON_Handle button, const GUI_BITMAP* bitmap, GUI_COLOR bkColor, bool setBkColor, bool forceSet = false) {
			if (forceSet || ButtonBitmaps[button] != bitmap) {
				BUTTON_SetFocussable(button, 0);
				WIDGET_SetEffect(button, &WIDGET_Effect_None);
				if (setBkColor)
				  BUTTON_SetBkColor(button, BUTTON_BI_UNPRESSED, bkColor);
				BUTTON_SetBitmap(button, BUTTON_BI_UNPRESSED, bitmap);
				ButtonBitmaps[button] = bitmap;
			}
		}
		
	protected:
		WM_HWIN GetHandle(void) {
		  return Handle;
		}
		
		WM_HWIN GetWidget(int id) {
			return WM_GetDialogItem(Handle, id);
		}
		
		void SetButtonStyle(BUTTON_Handle button, const GUI_BITMAP* bitmap, GUI_COLOR bkColor) {
			SetButtonStyle(button, bitmap, bkColor, true);
		}
		
		void SetButtonStyle(BUTTON_Handle button, const GUI_BITMAP* bitmap) {
			SetButtonStyle(button, bitmap, 0, false);
		}
		
		void ForceButtonStyle(BUTTON_Handle button, const GUI_BITMAP* bitmap, GUI_COLOR bkColor) {
			SetButtonStyle(button, bitmap, bkColor, true, true);
		}
		
		void ForceButtonStyle(BUTTON_Handle button, const GUI_BITMAP* bitmap) {
			SetButtonStyle(button, bitmap, 0, false, true);
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
		
		void Block(uint16_t duration, BUTTON_Handle button, const GUI_BITMAP* bitmap) {
			if (!ButtonBitmaps[button])
				printf("Not ButtonBitmap set!");
			GUI_EnterBlocking(button, bitmap);
			OSTimeDlyHMSM(0, 0, 0, duration);
			GUI_LeaveBlocking(button, ButtonBitmaps[button]);
		}
		
		void Block(uint16_t duration, BUTTON_Handle button) {
			Block(duration, button, ButtonBitmaps[button]);
		}
	
	public:
		Window(createWindowFunc_t createWindowFunc): Handle(0), CreateWindowFunc(createWindowFunc), LastClick(0) {
		  Handle = CreateWindowFunc != NULL ? CreateWindowFunc() : NULL;
		}
			
		~Window() {
			if (Handle != NULL)
		    GUI_EndDialog(Handle, 0);
		}
		
		void DebouncedClick(buttonClickFunc_t buttonClickFunc, int debounceMs) {
			uint32_t currentClick = OSTimeGet();
			if (currentClick > LastClick + debounceMs * (OS_TICKS_PER_SEC / 1000)) {
				LastClick = currentClick;
				(reinterpret_cast<T*>(this)->*buttonClickFunc)();
			}
		}
		
		template<typename TArg>
		void DebouncedClick(void (T::*buttonClickFuncWithArg)(TArg), TArg arg, int debounceMs) {
		  uint32_t currentClick = OSTimeGet();
			if (currentClick > LastClick + debounceMs * (OS_TICKS_PER_SEC / 1000)) {
				LastClick = currentClick;
				(reinterpret_cast<T*>(this)->*buttonClickFuncWithArg)(arg);
			}
		}
		
		virtual bool Refresh(void) = 0;
		
		typedef int (*processResultFunc_t)(void*);

		template <typename TWindow>
		static int RunDialog(TWindow* dialogWindow, processResultFunc_t processResultFunc) {
			int result = -1;
			while (dialogWindow->Refresh())
				GUI_Delay(50);
			if (processResultFunc != NULL)
			  result = processResultFunc(dialogWindow);
			delete dialogWindow;
			return result;
		}
		
		template <typename TWindow>
		static int RunDialog(TWindow* dialogWindow) {
			return RunDialog(dialogWindow, NULL);
		}
};

#endif
