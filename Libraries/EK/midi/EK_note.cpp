#include "EK_note.hpp"
#include <stdlib.h>
#include <string.h>
#include "../EK_retarget.hpp"

namespace MIDI {
	Note::Note(int8_t noteId, int8_t octave) {
		SetOctave(octave);
		SetNoteId(noteId);
	}
	
	Note::Note(uint8_t midiNote) {
		SetOctave(midiNote / 12 - 1);
		SetNoteId(midiNote % 12);
	}
	
	Note::Note(const char* noteBuf) {
 		SetOctave(OctaveFromString(noteBuf));
	  SetNoteId(NoteIdFromString(noteBuf));
	}
	
	int8_t Note::GetNoteId() {
	  return NoteId;
	}
	
	int8_t Note::GetOctave() {
	  return Octave;
	}
	
	void Note::Transpose(int8_t steps) {
	  SetNoteId(NoteId + steps);
	}
	
	Note Note::operator+(int8_t steps) {
		Note noteCopy = *this;
	  noteCopy.Transpose(steps);
		return noteCopy;
	}
	
	Note Note::operator+(Note& note) {
		Note noteCopy = *this;
	  noteCopy.Transpose(note.GetNoteId());
		return noteCopy;
	}
	
	Note& Note::operator+=(int8_t steps) {
	  Transpose(steps);
		return *this;
	}
	
	Note& Note::operator+=(Note& note) {
	  Transpose(note.GetNoteId());
		return *this;
	}
	
  uint8_t Note::GetMIDINote(void) {
		return (NoteId + (Octave + 1) * 12) & 0x7f;
	}
	
	Note::operator string() {
		const char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
		char buf[5];
		sprintf(buf, "%s%d", notes[NoteId], Octave);
	  return buf;
	}
	
	void Note::SetNoteId(int8_t noteId) {
		if (noteId < NOTE_C) {
			NoteId = NOTE_C2 + noteId;
			SetOctave(Octave - 1);
		}	else if (noteId > NOTE_B) {
			NoteId = noteId - NOTE_C2;
			SetOctave(Octave + 1);
		} else
			NoteId = noteId;
	}
	
	void Note::SetOctave(int8_t octave) {
		if (octave < -1)
			Octave = -1;
		else if (octave > 9)
			Octave = 9;
		else
			Octave = octave;
	}
	
#define NOTE_STR_TO_ID(buf, str, id) if (strstr((buf), (str)) != NULL) return (id);
	
	int8_t Note::NoteIdFromString(const char* noteBuf) {
		NOTE_STR_TO_ID(noteBuf, "Cb", NOTE_CF); NOTE_STR_TO_ID(noteBuf, "C#", NOTE_CS);	NOTE_STR_TO_ID(noteBuf, "C", NOTE_C);
		NOTE_STR_TO_ID(noteBuf, "Db", NOTE_DF); NOTE_STR_TO_ID(noteBuf, "D#", NOTE_DS); NOTE_STR_TO_ID(noteBuf, "D", NOTE_D);	
		NOTE_STR_TO_ID(noteBuf, "Eb", NOTE_EF); NOTE_STR_TO_ID(noteBuf, "E#", NOTE_ES);	NOTE_STR_TO_ID(noteBuf, "E", NOTE_E);
		NOTE_STR_TO_ID(noteBuf, "Fb", NOTE_FF); NOTE_STR_TO_ID(noteBuf, "F#", NOTE_FS); NOTE_STR_TO_ID(noteBuf, "F", NOTE_F);
		NOTE_STR_TO_ID(noteBuf, "Gb", NOTE_GF); NOTE_STR_TO_ID(noteBuf, "G#", NOTE_GS);	NOTE_STR_TO_ID(noteBuf, "G", NOTE_G);
		NOTE_STR_TO_ID(noteBuf, "Ab", NOTE_AF); NOTE_STR_TO_ID(noteBuf, "A#", NOTE_AS); NOTE_STR_TO_ID(noteBuf, "A", NOTE_A);	
		NOTE_STR_TO_ID(noteBuf, "Bb", NOTE_BF); NOTE_STR_TO_ID(noteBuf, "B#", NOTE_BS);	NOTE_STR_TO_ID(noteBuf, "B", NOTE_B);
		return NOTE_DEFAULT;
	}
	
	int8_t Note::OctaveFromString(const char* noteBuf) {
	  if (noteBuf[1] == 'b' || noteBuf[1] == '#') {
			if (noteBuf[2] == 'm') {
			  if (noteBuf[3] == '\0')
				  return OCTAVE_DEFAULT;
				return atoi(&noteBuf[3]);
			} else {
			  if (noteBuf[2] == '\0')
				  return OCTAVE_DEFAULT;
		    return atoi(&noteBuf[2]);
			}
		} else {
			if (noteBuf[1] == 'm') {
			  if (noteBuf[2] == '\0')
				  return OCTAVE_DEFAULT;
		    return atoi(&noteBuf[2]);
			} else {
			  if (noteBuf[1] == '\0')
				  return OCTAVE_DEFAULT;
		    return atoi(&noteBuf[1]);
			}
		}
	}
}
