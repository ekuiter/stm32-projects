#include "EK_key.hpp"
#include <string.h>
#include "../EK_retarget.hpp"

namespace MIDI {
	Key::Key(class Note& note, enum Mode mode): Note(note), Mode(mode) {}
	Key::Key(int8_t noteId, int8_t octave, enum Mode mode): Note(noteId, octave), Mode(mode) {}
	Key::Key(const char* noteBuf): Note(noteBuf), Mode(ModeFromString(noteBuf)) {}
		
  class Note& Key::GetNote(void) {
		return Note;
	}
	
	enum Mode Key::GetMode(void) {
	  return Mode;
	}

	enum Mode Key::ModeFromString(const char* noteBuf) {
	  if (strstr(noteBuf, "m") != NULL)
			return Minor;
		else
			return Major;
	}
}
