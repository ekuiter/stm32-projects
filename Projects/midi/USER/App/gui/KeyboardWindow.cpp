#include "KeyboardWindow.hpp"
#include <EK/ek_gpio.hpp>

GPIO_Pin UserKeyA("PC13");

KeyboardWindow::KeyboardWindow(MIDI::MIDI& midi): Window(NULL), Midi(midi) {
	WM_Deactivate();
	GUI_SetBkColor(GUI_STYLE_MAIN);
	GUI_Clear();
	for (int i = 0; i < OCTAVES_PER_ROW; i++)
  	Octaves[i].Initialize(OCTAVES_X + i * OCTAVE_WIDTH, OCTAVES_Y1);
	for (int i = OCTAVES_PER_ROW; i < OCTAVE_NUMBER; i++)
  	Octaves[i].Initialize(OCTAVES_X + (i - OCTAVES_PER_ROW) * OCTAVE_WIDTH, OCTAVES_Y2);
	ReadLoop();
	WM_Activate();
}

void KeyboardWindow::ReadLoop(void) {
  while (1) {
	  while (Midi.Available()) {
		  MIDI::Message message = Midi.Read();
			MIDI::Note note = message.GetNote();
			int octave = note.GetOctave() + OCTAVE_OFFSET;
		  if (message.Is(MIDI::Command::NoteOn) && octave >= 0 && octave < OCTAVE_NUMBER)
				Octaves[octave].SetPressed(note.GetNoteId(), message.GetVelocity());
  	}
		if (UserKeyA.Get() == 0)
			break;
	}
}

bool KeyboardWindow::Refresh(void) {
  return false;
}

const GUI_POINT KeyboardWindow::Octave::WhiteKeyLeftPolygon[] = {
	{1, 1}, {1, KeyHeight - 1}, {KeyWidth - 1, KeyHeight - 1}, {KeyWidth - 1, BlackKeyHeight + 1},
	{KeyWidth - HalfBlackKeyWidth - 1, BlackKeyHeight + 1}, {KeyWidth - HalfBlackKeyWidth - 1, 1}
}, KeyboardWindow::Octave::WhiteKeyMiddlePolygon[] = {
	{HalfBlackKeyWidth + 1, 1}, {HalfBlackKeyWidth + 1, BlackKeyHeight + 1}, {1, BlackKeyHeight + 1},
	{1, KeyHeight - 1}, {KeyWidth - 1, KeyHeight - 1}, {KeyWidth - 1, BlackKeyHeight + 1}, 
	{KeyWidth - HalfBlackKeyWidth - 1, BlackKeyHeight + 1}, {KeyWidth - HalfBlackKeyWidth - 1, 1}
}, KeyboardWindow::Octave::WhiteKeyRightPolygon[] = {
	{HalfBlackKeyWidth + 1, 1}, {HalfBlackKeyWidth + 1, BlackKeyHeight + 1}, {1, BlackKeyHeight + 1},
	{1, KeyHeight - 1}, {KeyWidth - 1, KeyHeight - 1}, {KeyWidth - 1, 1}
};

const int KeyboardWindow::Octave::WhiteKeyLeftPolygonSize = sizeof(KeyboardWindow::Octave::WhiteKeyLeftPolygon) / sizeof(GUI_POINT),
	KeyboardWindow::Octave::WhiteKeyMiddlePolygonSize = sizeof(WhiteKeyMiddlePolygon) / sizeof(GUI_POINT),
	KeyboardWindow::Octave::WhiteKeyRightPolygonSize = sizeof(WhiteKeyRightPolygon) / sizeof(GUI_POINT),
  KeyboardWindow::Octave::BlackKeysOffsets[] = {1, 2, 4, 5, 6}, // black keys are drawn 1, 2, 4, ... KeyWidth's from the left
	KeyboardWindow::Octave::WhiteKeysPolygonsSize[] = {
		WhiteKeyLeftPolygonSize, WhiteKeyMiddlePolygonSize, WhiteKeyRightPolygonSize, WhiteKeyLeftPolygonSize,
	  WhiteKeyMiddlePolygonSize, WhiteKeyMiddlePolygonSize, WhiteKeyRightPolygonSize
	};
	
const GUI_POINT* KeyboardWindow::Octave::WhiteKeysPolygons[] = {
	WhiteKeyLeftPolygon, WhiteKeyMiddlePolygon, WhiteKeyRightPolygon, WhiteKeyLeftPolygon,
	WhiteKeyMiddlePolygon, WhiteKeyMiddlePolygon, WhiteKeyRightPolygon
};

void KeyboardWindow::Octave::Initialize(int x, int y) {
	X = x;
	Y = y;
	GUI_SetColor(BlackKeyBaseColor);
	for (int i = 1; i < 7; i++)
		GUI_DrawLine(X + i * KeyWidth, Y, X + i * KeyWidth, Y + KeyHeight); // white keys outline
	GUI_DrawRect(X, Y, X + octaveWidth, Y + octaveHeight); // outer outline
	for (int i = 0; i < 5; i++)
		GUI_DrawRect(X + BlackKeysOffsets[i] * KeyWidth - HalfBlackKeyWidth, Y, // black keys outline
								 X + BlackKeysOffsets[i] * KeyWidth + HalfBlackKeyWidth, Y + BlackKeyHeight);
  for (int i = 0; i < KEY_NUMBER; i++)
	  SetPressed(i, false);
}
		
void KeyboardWindow::Octave::SetPressed(int i, bool pressed) {
	if (i < 0 || i >= KEY_NUMBER)
		return;
	PressedKeys[i] = pressed;
	bool isWhiteKey = i == 0 || i == 2 || i == 4 || i == 5 || i == 7 || i == 9 || i == 11;
	GUI_COLOR baseColor = isWhiteKey ? WhiteKeyBaseColor : BlackKeyBaseColor;
	GUI_SetColor(pressed ? PressedColor : baseColor);
  int offset;
	if (isWhiteKey) {
		if (i == 0)  offset = 0; if (i == 2) offset = 1; if (i == 4) offset = 2;
		if (i == 5)  offset = 3; if (i == 7) offset = 4; if (i == 9) offset = 5;
		if (i == 11) offset = 6;
		GUI_FillPolygon(WhiteKeysPolygons[offset], WhiteKeysPolygonsSize[offset], X + offset * KeyWidth, Y);
	} else {
		if (i == 1) offset = 1; if (i == 3)  offset = 2; if (i == 6) offset = 4;
		if (i == 8) offset = 5; if (i == 10) offset = 6;
		GUI_FillRect(X + offset * KeyWidth - HalfBlackKeyWidth + 1, Y + 1,
								 X + offset * KeyWidth + HalfBlackKeyWidth - 1, Y + BlackKeyHeight - 1);
	}
}
