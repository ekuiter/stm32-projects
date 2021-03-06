/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.22                          *
*        Compiled Jul  4 2013, 15:16:01                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include <EK/EK_gui.hpp>
#include <uCGUI_LIB/USER/uCGUI/Widget/PROGBAR.h>
#include "ChordFileWindow.hpp"
#include <EK/EK_retarget.hpp>
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0    (GUI_ID_USER + 0x01)
#define ID_BUTTON_0    (GUI_ID_USER + 0x0D)
#define ID_BUTTON_1    (GUI_ID_USER + 0x02)
#define ID_BUTTON_2    (GUI_ID_USER + 0x04)
#define ID_PROGBAR_0    (GUI_ID_USER + 0x06)
#define ID_SLIDER_0    (GUI_ID_USER + 0x07)
#define ID_TEXT_0    (GUI_ID_USER + 0x08)
#define ID_TEXT_1    (GUI_ID_USER + 0x09)
#define ID_SLIDER_1    (GUI_ID_USER + 0x0A)
#define ID_LISTBOX_0    (GUI_ID_USER + 0x0B)
#define ID_TEXT_2    (GUI_ID_USER + 0x0C)
#define ID_BUTTON_3    (GUI_ID_USER + 0x0E)
#define ID_TEXT_3    (GUI_ID_USER + 0x0F)
#define ID_TEXT_4    (GUI_ID_USER + 0x10)


// USER START (Optionally insert additional defines)
#ifdef INCLUDE_FROM_CLASS
#else
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ChordFileWindow", ID_WINDOW_0, 0, 0, 320, 240, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "FocusButton", ID_BUTTON_0, 320, 0, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "PlayPauseButton", ID_BUTTON_1, 10, 10, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "StopButton", ID_BUTTON_2, 70, 10, 50, 50, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "ChordFileProgress", ID_PROGBAR_0, 10, 70, 300, 30, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "VelocitySlider", ID_SLIDER_0, 10, 125, 50, 105, 8, 0x0, 0 },
  { TEXT_CreateIndirect, "Velocity", ID_TEXT_0, 10, 110, 50, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Tempo", ID_TEXT_1, 70, 110, 50, 15, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "TempoSlider", ID_SLIDER_1, 70, 125, 50, 105, 8, 0x0, 0 },
  { LISTBOX_CreateIndirect, "ChordStyleListbox", ID_LISTBOX_0, 130, 125, 180, 105, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Chord Style", ID_TEXT_2, 130, 110, 180, 15, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "CloseButton", ID_BUTTON_3, 275, 10, 35, 35, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "TitleText", ID_TEXT_3, 130, 10, 135, 25, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "ArtistText", ID_TEXT_4, 130, 35, 135, 25, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'PlayPauseButton'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "");
    //
    // Initialization of 'StopButton'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "");
    //
    // Initialization of 'ChordFileProgress'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
    PROGBAR_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Velocity'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
    //
    // Initialization of 'Tempo'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
    //
    // Initialization of 'ChordStyleListbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
    LISTBOX_SetFont(hItem, GUI_FONT_24_1);
    //
    // Initialization of 'CloseButton'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetText(hItem, "");
    //
    // Initialization of 'TitleText'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_24_1);
    TEXT_SetText(hItem, "");
    //
    // Initialization of 'ArtistText'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetFont(hItem, GUI_FONT_24_1);
    TEXT_SetText(hItem, "");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'FocusButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'PlayPauseButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
			  CurrentChordFileWindow->DebouncedClick(&ChordFileWindow::PlayPauseButtonClicked, 300);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'StopButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				CurrentChordFileWindow->DebouncedClick(&ChordFileWindow::StopButtonClicked, 300);
			        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_0: // Notifications sent by 'VelocitySlider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				CurrentChordFileWindow->VelocitySliderValueChanged();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_1: // Notifications sent by 'TempoSlider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				CurrentChordFileWindow->TempoSliderValueChanged();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTBOX_0: // Notifications sent by 'ChordStyleListbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
			  CurrentChordFileWindow->ChordStyleListboxValueChanged();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'CloseButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
			  CurrentChordFileWindow->DebouncedClick(&ChordFileWindow::CloseButtonClicked, 300);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateChordFileWindow
*/
WM_HWIN CreateChordFileWindow(void);
WM_HWIN CreateChordFileWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
#endif
// USER END

/*************************** End of file ****************************/
