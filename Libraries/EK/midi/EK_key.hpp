#ifndef __EK_MIDI_KEY_HPP
#define __EK_MIDI_KEY_HPP

#include <stdint.h>
#include "EK_note.hpp"

namespace MIDI {
	enum Mode { Major, Minor };
	
	class Key {
	  private:
			Note Note;
		  Mode Mode;
		  enum Mode ModeFromString(const char*);
		
		public:
			Key(class Note&, enum Mode);
			Key(int8_t, int8_t, enum Mode);
		  Key(const char*);
		  class Note& GetNote(void);
		  enum Mode GetMode(void);
	};
}

#endif
