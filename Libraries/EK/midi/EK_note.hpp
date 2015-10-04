#ifndef __EK_MIDI_NOTE_HPP
#define __EK_MIDI_NOTE_HPP

#include <stdint.h>
#include <string>

#define NOTE_CF 11
#define NOTE_C  0
#define NOTE_CS 1
#define NOTE_DF 1
#define NOTE_D  2
#define NOTE_DS 3
#define NOTE_EF 3
#define NOTE_E  4
#define NOTE_ES 5
#define NOTE_FF 4
#define NOTE_F  5
#define NOTE_FS 6
#define NOTE_GF 6
#define NOTE_G  7
#define NOTE_GS 8
#define NOTE_AF 8
#define NOTE_A  9
#define NOTE_AS 10
#define NOTE_BF 10
#define NOTE_B  11
#define NOTE_BS 0
#define NOTE_C2 12

#define NOTE_NUMBER    12
#define NOTE_DEFAULT   NOTE_C
#define OCTAVE_DEFAULT 4

using std::string;

namespace MIDI {
	class Note {
		private:
			int8_t NoteId; // NOTE_C up to NOTE_B
		  int8_t Octave; // -1 up to 9
		  int8_t NoteIdFromString(const char*);
		  int8_t OctaveFromString(const char*);
		  void SetNoteId(int8_t);
		  void SetOctave(int8_t);
		
		public:
			Note(int8_t, int8_t);
		  Note(uint8_t);
		  Note(const char*); // C / C-1 / C9 / F#4 / Eb / Bb-1
		  int8_t GetNoteId(void);
		  int8_t GetOctave(void);
		  void Transpose(int8_t steps);
		  Note operator+(int8_t steps);
		  Note operator+(Note& note);
		  Note& operator+=(int8_t steps);
		  Note& operator+=(Note& note);
		  uint8_t GetMIDINote(void);
		  operator string();
	};
}

#endif
