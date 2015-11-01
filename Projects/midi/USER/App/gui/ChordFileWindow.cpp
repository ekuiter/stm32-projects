#include "ChordFileWindow.hpp"
#include <gui_style.hpp>
#include <EK/EK_retarget.hpp>
#include <stdio.h>
#include <string>

#define INCLUDE_FROM_CLASS
#include "ChordFileWindowDLG.c"

using std::string;

extern WM_HWIN CreateChordFileWindow(void);
ChordFileWindow* CurrentChordFileWindow = NULL;
extern GUI_CONST_STORAGE GUI_BITMAP bmplay, bmpause, bmstop, bmclose, bmbusy;

ChordFileWindow::ChordFileWindow(string fileName, MIDI::MIDI& midi, class SD_Card& SD_Card):
  Window(CreateChordFileWindow), Midi(midi), SD_Card(SD_Card), ChordFile(new MIDI::ChordFile(fileName, midi)),
  PlayPauseButton(GetWidget(ID_BUTTON_1)), StopButton(GetWidget(ID_BUTTON_2)), CloseButton(GetWidget(ID_BUTTON_3)), ChordFileProgress(GetWidget(ID_PROGBAR_0)),
	VelocitySlider(GetWidget(ID_SLIDER_0)), TempoSlider(GetWidget(ID_SLIDER_1)), ChordStyleListbox(GetWidget(ID_LISTBOX_0)), TitleText(GetWidget(ID_TEXT_3),
	ChordFile->GetTitle()), ArtistText(GetWidget(ID_TEXT_4), ChordFile->GetArtist()), NoteText(GetWidget(ID_TEXT_5)), ListboxClicked(true), ShouldClose(false) {
	if (CurrentChordFileWindow != NULL) {
	  printf("Only one ChordFileWindow allowed at a time!\r\n");
		return;
	}
	CurrentChordFileWindow = this;
	Midi.SetTempo(ChordFile->GetTempo());
		
	SetButtonStyle(PlayPauseButton, &bmplay, GUI_STYLE_MAIN);
	SetButtonStyle(StopButton, &bmstop, GUI_STYLE_MAIN);
	SetButtonStyle(CloseButton, &bmclose, GUI_STYLE_MAIN);
		
  PROGBAR_SetMinMax(ChordFileProgress, 0, ChordFile->GetTotalBeats() * 1000);
	WM_GetWindowRectEx(ChordFileProgress, &ChordFileProgressRectangle.Rect);
		
	SLIDER_SetRange(VelocitySlider, 0, 127);
  SLIDER_SetNumTicks(VelocitySlider, 0);
  SLIDER_SetValue(VelocitySlider, NOTE_ON_VELOCITY_DEFAULT);
	SLIDER_SetRange(TempoSlider, 0, TEMPO_MAX - TEMPO_MIN);
  SLIDER_SetNumTicks(TempoSlider, 0);
  SLIDER_SetValue(TempoSlider, TEMPO_MAX - (int) ChordFile->GetTempo());
		
	LISTBOX_SetAutoScrollV(ChordStyleListbox, 1);
	LISTBOX_SetScrollbarWidth(ChordStyleListbox, 20);
	const int len = 100;
	char buf[len] = CHORDSTYLES_PATH;
  SD_Card.List(buf, len, AddChordStyle);
  SetListboxSelected(ChordStyleListbox, ChordFile->GetCurrentChordStyle()->GetStyleName());
}

ChordFileWindow::~ChordFileWindow() {
	Stop();
	CurrentChordFileWindow = NULL;
	delete ChordFile;
}

void ChordFileWindow::PlayPauseButtonClicked(void) {
	if (ChordFile->GetState() == MIDI::PlayState) {
		Pause();
		SetButtonStyle(PlayPauseButton, &bmplay);
	} else {
		ChordFile->Play(UserChordStyleName);
		SetButtonStyle(PlayPauseButton, &bmpause);
  }
}

void ChordFileWindow::StopButtonClicked(void) {
	Stop();
	SetButtonStyle(PlayPauseButton, &bmplay);
}

void ChordFileWindow::CloseButtonClicked(void) {
  Block(BUTTON_BLOCK_DURATION, CloseButton, &bmbusy);
	ShouldClose = true;
}

void ChordFileWindow::ChordFilePercentageClicked(void) {
  ChordFile->SeekPercentage(ChordFileProgressRectangle.GetClickPercentage(PIDState));
}

void ChordFileWindow::VelocitySliderValueChanged(void) {
  Midi.SetVelocity(127 - SLIDER_GetValue(VelocitySlider));
}

void ChordFileWindow::TempoSliderValueChanged(void) {
  Midi.SetTempo(TEMPO_MAX - SLIDER_GetValue(TempoSlider));
}

void ChordFileWindow::ChordStyleListboxValueChanged(void) {
	if (!ListboxClicked) {
		ListboxClicked = true;
		return;
	}
	bool Paused = false;
	if (ChordFile->GetState() == MIDI::PlayState) { 
		Paused = true;
		Pause();
	}
	UserChordStyleName = GetListboxText(ChordStyleListbox);
	if (Paused) {
	  ChordFile->Play(UserChordStyleName);
		GUI_EnterBlocking(CloseButton, &bmbusy);
		while (ChordFile->GetState() == MIDI::PlayState && ChordFile->GetCurrentChordStyle()->GetStyleName() != UserChordStyleName);
		GUI_LeaveBlocking(CloseButton, &bmclose);
	}
}

bool ChordFileWindow::Refresh() {
	static int runCount = 0;
	PROGBAR_SetValue(ChordFileProgress, ChordFile->GetBeat() * 1000);
	if (runCount % 4 == 0) {
		if (ChordFile->GetState() == MIDI::StopState)
			SetButtonStyle(PlayPauseButton, &bmplay);
		if (UserChordStyleName.empty()) {
		  string lastChordStyle, currentChordStyle = ChordFile->GetCurrentChordStyle()->GetStyleName();
			if (ChordFile->GetLastChordStyle() != NULL)
				lastChordStyle = ChordFile->GetLastChordStyle()->GetStyleName();
			if (GetListboxText(ChordStyleListbox) == lastChordStyle)
				SetListboxSelected(ChordStyleListbox, currentChordStyle);
		}
	}
	TitleText.Advance();
	ArtistText.Advance();
	GUI_PID_GetState(&PIDState);
	if (ChordFileProgressRectangle.Clicked(PIDState))
		DebouncedClick(&ChordFileWindow::ChordFilePercentageClicked, 300);
	runCount++;
	/*if (Midi.Available()) {
		MIDI::Message message = Midi.Read();
		if (message.Is(MIDI::Command::NoteOn))
			TEXT_SetText(NoteText, static_cast<string>(message.GetNote()).c_str());
	}*/
  return !ShouldClose;
}

void ChordFileWindow::AddChordStyle(char* path, char* fn) {
  LISTBOX_AddString(CurrentChordFileWindow->ChordStyleListbox, strtok(fn, "."));
}

void ChordFileWindow::Pause(void) {
  GUI_EnterBlocking(CloseButton, &bmbusy);
	ChordFile->Pause();
	GUI_LeaveBlocking(CloseButton, &bmclose);
}

void ChordFileWindow::Stop(void) {
  GUI_EnterBlocking(CloseButton, &bmbusy);
	ChordFile->Stop();
	GUI_LeaveBlocking(CloseButton, &bmclose);
}

void ChordFileWindow::SetListboxSelected(LISTBOX_Handle listbox, string select) {
  int itemCount = LISTBOX_GetNumItems(listbox);
	for (int i = 0; i < itemCount; i++) {
		string item = GetListboxText(listbox, i);
		if (item == select) {
			if (!LISTBOX_GetItemSel(listbox, i)) {
				CurrentChordFileWindow->ListboxClicked = false;
				LISTBOX_SetSel(listbox, i);
			}
			break;
		}
	}
}

void ChordFileWindow::MarqueeText::Advance(void) {
  int waitMs = CurrentIndex == 0 ? WaitStart : WaitBetween;
	if (OSTimeGet() > LastUpdate + waitMs * (OS_TICKS_PER_SEC / 1000)) {
		if (Text[CurrentIndex] == '\0' || CurrentIndex == TextLength + strlen(MARQUEE_DELIMITER))
			CurrentIndex = 0;
		else
			CurrentIndex++;
		TEXT_SetText(TextHandle, &Text[CurrentIndex]);
		LastUpdate = OSTimeGet();
	}
}
