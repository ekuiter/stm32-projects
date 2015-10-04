#ifndef __EK_MIDI_CHORDFILE_HPP
#define __EK_MIDI_CHORDFILE_HPP

#include <tasks.hpp>
#include "EK_midi.hpp"
#include "EK_chordstyle.hpp"
#include "../EK_tasks.hpp"
#include <jdksmidi/world.h>
#include <jdksmidi/tempo.h>
#include <stdio.h>

#define CHORDFILE_TITLE_LENGTH  50
#define CHORDFILE_ARTIST_LENGTH 50

using jdksmidi::MIDITempo;

namespace MIDI {
	struct Chord {
	  Key Key;
		int Beats;
		string ChordStyleName;
		Chord(class Key key, int beats, string chordStyleName): Key(key), Beats(beats), ChordStyleName(chordStyleName) {}
	};
	
	class ChordFile;
	enum ControlState { PlayState, PauseState, StopState };
	
	struct ControlRequest {
	  ControlState State;
		double Beat;
		int ChordIndex;
	  Task<ChordFilePlayTaskStackSize, void(*)(ChordFile*), ChordFile*>* PlayTask;

		ControlRequest(Task<ChordFilePlayTaskStackSize, void(*)(ChordFile*), ChordFile*>* pt): ChordIndex(0), PlayTask(pt) {
		  SetState(StopState);
		}
		
		void SetState(ControlState state) {
		  State = state;
			if (state == StopState) {
				Beat = 0;
				ChordIndex = 0;
			}
		}
	};
		
  class ChordFile {
	  private:
			Task<ChordFilePlayTaskStackSize, void(*)(ChordFile*), ChordFile*> PlayTask;
			char Title[CHORDFILE_TITLE_LENGTH], Artist[CHORDFILE_ARTIST_LENGTH];
		  MIDITempo Tempo;
		  vector<Chord> Chords;
		  int TotalBeats;
		  bool ParseSuccess;
		  string UserChordStyleName;
		  ChordStyle* CurrentChordStyle;
		  ChordStyle* LastChordStyle;
		  MIDI& Midi;
		  ControlRequest ControlRequest;
		  int ReadChord(FILE*, char*, char*, string*);
		  int ReadChords(FILE*);
		  void RunPlayTask(void);
		
		public:
			ChordFile(string, class MIDI&);
		  ~ChordFile();
		  void Play(string);
		  void Pause(void);
		  void Stop(void);
		  void SeekChord(int);
		  void SeekBeat(int);
		  void SeekPercentage(int);
		  ControlState GetState(void);
		  double GetBeat(void);
		  int GetTotalBeats(void);
		  MIDITempo& GetTempo(void);
		  void SetTempo(MIDITempo);
		  char* GetTitle(void);
		  char* GetArtist(void);
		  class ChordStyle* GetCurrentChordStyle(void);
		  class ChordStyle* GetLastChordStyle(void);
		  static void GetInfo(string, string*, string*);
		  friend void RunChordFilePlayTask(ChordFile*);
	};
}

#endif
