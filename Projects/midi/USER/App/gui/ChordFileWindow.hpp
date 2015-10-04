#ifndef  __CHORDFILEWINDOW_HPP__
#define  __CHORDFILEWINDOW_HPP__

#include "tasks.hpp"
#include <EK/EK_tasks.hpp>
#include <EK/EK_gui.hpp>
#include <EK/EK_sd.hpp>
#include <EK/midi/EK_midi.hpp>
#include <uCGUI_LIB/USER/uCGUI/Widget/PROGBAR.h>

#define TEMPO_MIN 80
#define TEMPO_MAX 200
#define MARQUEE_DELIMITER "   -   "
	
class ChordFileWindow : public Window<ChordFileWindow> {
  private:
		MIDI::MIDI& Midi;
	  SD_Card& SD_Card;
	  MIDI::ChordFile* ChordFile;
	  string UserChordStyleName;
	  BUTTON_Handle PlayPauseButton, StopButton, CloseButton;
	  map<BUTTON_Handle, const GUI_BITMAP*> ButtonBitmaps;
	  PROGBAR_Handle ChordFileProgress;
	  struct {
		  GUI_RECT Rect;
			bool Clicked(GUI_PID_STATE& state) {
			  return state.Pressed && Rect.x0 <= state.x && state.x <= Rect.x1 && Rect.y0 <= state.y && state.y <= Rect.y1;
			}
			int GetClickPercentage(GUI_PID_STATE& state) {
				int width = Rect.x1 - Rect.x0, clickOffset = state.x - Rect.x0;
			  return clickOffset * 100 / width;
			}
		} ChordFileProgressRectangle;
		GUI_PID_STATE PIDState;
	  SLIDER_Handle VelocitySlider, TempoSlider;
	  LISTBOX_Handle ChordStyleListbox;
	  struct MarqueeText {
			static const int WaitStart = 1000, WaitBetween = 300;
			TEXT_Handle TextHandle;
			string Text;
			int TextLength;
		  int CurrentIndex, LastUpdate;
			MarqueeText(TEXT_Handle th, char* t): TextHandle(th), Text(string(t) + MARQUEE_DELIMITER + t + MARQUEE_DELIMITER + t + MARQUEE_DELIMITER),
				TextLength(strlen(t)), CurrentIndex(0), LastUpdate(OSTimeGet()) {
			  TEXT_SetText(TextHandle, Text.c_str());
			}
			void Advance(void);
		};
		MarqueeText TitleText, ArtistText;
		TEXT_Handle NoteText;
	  bool ListboxClicked, ShouldClose;
	  void Pause(void);
    void Stop(void);
	  void SetListboxSelected(LISTBOX_Handle, string);
	  void SetButtonBitmap(BUTTON_Handle, const GUI_BITMAP*);
	  static void AddChordStyle(char*, char*);

  public:
		ChordFileWindow(string, MIDI::MIDI& Midi, class SD_Card&);
	  ~ChordFileWindow();
		void PlayPauseButtonClicked(void);
		void StopButtonClicked(void);
	  void CloseButtonClicked(void);
	  void ChordFilePercentageClicked(void);
	  void VelocitySliderValueChanged(void);
   	void TempoSliderValueChanged(void);
	  void ChordStyleListboxValueChanged(void);
	  virtual bool Refresh(void);
};

extern ChordFileWindow* CurrentChordFileWindow;

#endif
