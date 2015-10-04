#ifndef __EK_MIDI_CHORDSTYLE_HPP
#define __EK_MIDI_CHORDSTYLE_HPP

#include "EK_key.hpp"
#include <vector>
#include <string>
#include <map>
#include <stdio.h>

using std::vector;
using std::string;
using std::map;

namespace MIDI {
	class Chord;
	struct ControlRequest;
	
	struct ChordPhase {
	  vector<Note> Notes;
		int NoteNumber;
		double Beats;
	};
	
	class ChordStyle {
		private:
		  string StyleName;
			vector<ChordPhase> MajorPhases;
	    vector<ChordPhase> MinorPhases;
		  bool ParseSuccess;
		  static ChordStyle* LoadedChordStyle;
		  void ReadPhases(vector<ChordPhase>& Phases, FILE* f);
		
		public:
		  ChordStyle(string);
		  void Play(Chord&, class MIDI&, ControlRequest* = NULL);
		  string GetStyleName(void);
	};
}

#endif
