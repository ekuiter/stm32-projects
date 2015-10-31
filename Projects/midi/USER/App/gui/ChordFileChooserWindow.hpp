#ifndef  __CHORDFILECHOOSERWINDOW_HPP__
#define  __CHORDFILECHOOSERWINDOW_HPP__

#include <EK/midi/EK_midi.hpp>
#include "ChooserWindow.hpp"
	
class ChordFileChooserWindow : public ChooserWindow {
  private:
		MIDI::MIDI& Midi;		
    static void AddFile(char*, char*);
		virtual void OpenFile(string);
		
	public:
		ChordFileChooserWindow(MIDI::MIDI&, class SD_Card&);
};

#endif
