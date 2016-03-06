#ifndef  __KEYBOARDWINDOW_HPP__
#define  __KEYBOARDWINDOW_HPP__

#include <EK/EK_gui.hpp>
#include <EK/midi/ek_midi.hpp>
#include <gui_style.hpp>

#define WHITE_KEY_BASE_COLOR 0xffe6e6         // unpressed white key color
#define BLACK_KEY_BASE_COLOR GUI_BLACK        // unpressed black key color
#define PRESSED_COLOR    0x00a5ff             // pressed white/black key color
#define KEY_NUMBER       12									  // number of keys in an octave (const.)
#define KEY_WIDTH        14                   // width of a white key
#define KEY_HEIGHT       65                   // height of a white key
#define BLACK_KEY_WIDTH  8                    // width of a black key
#define BLACK_KEY_HEIGHT (KEY_HEIGHT * 2 / 3) // height of a black key
#define OCTAVE_NUMBER    6										// number of octaves to show on screen
#define OCTAVES_PER_ROW  3								    // number of octaves to show per row
#define OCTAVE_OFFSET    -1										// number of octaves to shift on screen
#define OCTAVE_WIDTH     (KEY_WIDTH * 7)			// width of an octave (const.)
#define OCTAVE_HEIGHT    KEY_HEIGHT						// height of an octave (const.)
// where to draw octaves
#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    240
#define OCTAVE_Y_PADDING 20
#define OCTAVES_X        ((SCREEN_WIDTH - (OCTAVE_WIDTH * OCTAVES_PER_ROW)) / 2)
#define OCTAVES_Y1       ((SCREEN_HEIGHT - (OCTAVE_HEIGHT * 2 + OCTAVE_Y_PADDING)) / 2)
#define OCTAVES_Y2       (OCTAVES_Y1 + OCTAVE_HEIGHT + OCTAVE_Y_PADDING)

class KeyboardWindow : public Window<KeyboardWindow> {	
  private:
		class Octave {
			private:
				int X, Y;
				bool PressedKeys[KEY_NUMBER];
			  static const GUI_COLOR WhiteKeyBaseColor = WHITE_KEY_BASE_COLOR, 
					BlackKeyBaseColor = BLACK_KEY_BASE_COLOR, PressedColor = PRESSED_COLOR;
			  static const GUI_POINT WhiteKeyLeftPolygon[], WhiteKeyMiddlePolygon[], WhiteKeyRightPolygon[];
				static const GUI_POINT* WhiteKeysPolygons[];
				static const int KeyWidth = KEY_WIDTH, KeyHeight = KEY_HEIGHT, BlackKeyWidth = BLACK_KEY_WIDTH,
					octaveWidth = OCTAVE_WIDTH,	octaveHeight = OCTAVE_HEIGHT, HalfBlackKeyWidth = BlackKeyWidth / 2,
				  BlackKeyHeight = BLACK_KEY_HEIGHT, WhiteKeyLeftPolygonSize, WhiteKeyMiddlePolygonSize,
				  WhiteKeyRightPolygonSize,	BlackKeysOffsets[], WhiteKeysPolygonsSize[];
			public:
				void SetPressed(int, bool);
			  void Initialize(int, int);
				void Draw(void);
		};
		MIDI::MIDI& Midi;
		Octave Octaves[OCTAVE_NUMBER];
	  void ReadLoop();
		
	public:
		KeyboardWindow(MIDI::MIDI&);
	  virtual bool Refresh(void);
};

extern KeyboardWindow* CurrentKeyboardWindow;

#endif
