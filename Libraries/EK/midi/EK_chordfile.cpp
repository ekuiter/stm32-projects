#include "EK_chordfile.hpp"
#include "EK_key.hpp"
#include "EK_chordstyle.hpp"
#include <algorithm>

namespace MIDI {
	static char buf[LINE_BUFFER_LENGTH];
	
	void RunChordFilePlayTask(ChordFile* chordFile) {
		chordFile->RunPlayTask();
		chordFile->ControlRequest.SetState(StopState);
		chordFile->PlayTask.Delete();
	}
	
	ChordFile::ChordFile(string fileName, class MIDI& midi):
		PlayTask("ChordFilePlayTask", ::MIDI::RunChordFilePlayTask), ParseSuccess(false), LastChordStyle(NULL), Midi(midi), ControlRequest(&PlayTask) {
		const char* path = (string(CHORDFILES_PATH) + "/" + fileName + CHORDFILES_SUFFIX).c_str();
	  FILE* f = fopen(path, "r");
		if (!f) {
			printf("File could not be opened: %s\r\n", path);
			return;
		}
		fgets(Title, CHORDFILE_TITLE_LENGTH, f);
		Title[strlen(Title) - 2] = '\0';
		fgets(Artist, CHORDFILE_ARTIST_LENGTH, f);
		Artist[strlen(Artist) - 2] = '\0';
		int tempo;
		fscanf(f, "%d\r\n", &tempo);
		Tempo = tempo;
		TotalBeats = ReadChords(f);
		fclose(f);
		CurrentChordStyle = new ChordStyle(Chords[0].ChordStyleName);
		ParseSuccess = true;
	}
	
	ChordFile::~ChordFile(void) {
		Stop();
		delete LastChordStyle, delete CurrentChordStyle;
	}
	
	void ChordFile::Play(string userChordStyleName) {
		if (!ParseSuccess)
			return;
		UserChordStyleName = userChordStyleName;
		ControlRequest.SetState(PlayState);
		PlayTask.Run(this);
	}
	
	void ChordFile::Pause(void) {
	  if (ControlRequest.State == PlayState)
		  ControlRequest.SetState(PauseState);
		while (PlayTask.Running());
	}
	
	void ChordFile::Stop(void) {
		if (ControlRequest.State == PlayState || ControlRequest.State == PauseState) {
			ControlRequest.SetState(StopState);
			if (PlayTask.Running())
				while (PlayTask.Running());
			else
			  PlayTask.Delete();
		}
	}
	
	void ChordFile::SeekChord(int chordIndex) {
		if (chordIndex < 0)
			chordIndex = 0;
	  else if (chordIndex > Chords.size() - 1)
			chordIndex = Chords.size() - 1;
		bool Stopped = false;
		if (GetState() == PlayState || GetState() == PauseState) {
			if (GetState() == PlayState)
				Stopped = true;
		  Stop();
		}
		ControlRequest.Beat = 0;
		for (int i = 0; i < chordIndex; i++)
		  ControlRequest.Beat += Chords[i].Beats;
		ControlRequest.ChordIndex = chordIndex;
		if (Stopped)
		  Play(UserChordStyleName);
		else
			ControlRequest.SetState(PauseState);
	}
	
	void ChordFile::SeekBeat(int seekBeat) {
		int chordIndex = 0;
	  for (int i = 0; i < Chords.size(); i++) {
		  seekBeat -= Chords[i].Beats;
			if (seekBeat == 0) {
				chordIndex = i + 1;
				break;
			} else if (seekBeat < 0) {
				chordIndex = i;
				break;
			}
		}
		if (seekBeat > 0)
			chordIndex = Chords.size() - 1;
		SeekChord(chordIndex);
	}
	
	void ChordFile::SeekPercentage(int percentage) {
	  SeekBeat(percentage * TotalBeats / 100);
	}
	
	ControlState ChordFile::GetState(void) {
	  return ControlRequest.State;
	}
	
	double ChordFile::GetBeat(void) {
	  return ControlRequest.Beat;
	}
	
	int ChordFile::GetTotalBeats(void) {
	  return TotalBeats;
	}
	
	MIDITempo& ChordFile::GetTempo(void) {
	  return Tempo;
	}
  
	void ChordFile::SetTempo(MIDITempo tempo) {
	  Tempo = tempo;
	}
	
	class ChordStyle* ChordFile::GetCurrentChordStyle(void) {
		return CurrentChordStyle;
	}
	
	class ChordStyle* ChordFile::GetLastChordStyle(void) {
		return LastChordStyle;
	}
	
	char* ChordFile::GetTitle(void) {
		return Title;
	}
	
	char* ChordFile::GetArtist(void) {
		return Artist;
	}
	
	void ChordFile::GetInfo(string file, string* title, string* artist) {
		const char* path = (string(CHORDFILES_PATH) + "/" + file + CHORDFILES_SUFFIX).c_str();
	  FILE* f = fopen(path, "r");
		if (!f) {
			printf("File could not be opened: %s\r\n", buf);
			return;
		}
		char buf[CHORDFILE_TITLE_LENGTH];
		fgets(buf, CHORDFILE_TITLE_LENGTH, f);
		buf[strlen(buf) - 2] = '\0';
		*title = string(buf);
		fgets(buf, CHORDFILE_ARTIST_LENGTH, f);
		buf[strlen(buf) - 2] = '\0';
		*artist = string(buf);
	}
	
	int ChordFile::ReadChord(FILE* f, char* buf, char* keyBuf, string* chordStylePtr) {
		fgets(buf, LINE_BUFFER_LENGTH, f);
		if (strcmp(buf, "\r\n") == 0 || buf[0] == '#')
			return -1;
		else if (buf[0] == '!') {
			*chordStylePtr = strtok(&buf[1], "\r");
		  return -1;
		}
		int beats = 0;
	  sscanf(buf, "%5[^\t]%d\r\n", keyBuf, &beats);
		return beats;
	}
	
	int ChordFile::ReadChords(FILE* f) {
		char buf[LINE_BUFFER_LENGTH], keyBuf[NOTE_STRING_MAX_LENGTH];
		int totalBeats = 0, beats = 0;
		string chordStyle;
		while (!feof(f)) {
			while ((beats = ReadChord(f, buf, keyBuf, &chordStyle)) == -1);
			totalBeats += beats;
			if (chordStyle.empty())
				chordStyle = CHORDSTYLES_DEFAULT;
			Heap.Debug<Chord>("Pushing Chord");
			Chords.push_back(Chord(Key(keyBuf), beats, chordStyle));
		}
		return totalBeats;
	}
	
	void ChordFile::RunPlayTask(void) {
		for (int i = ControlRequest.ChordIndex; i < Chords.size(); i++) {
		  if (UserChordStyleName.empty()) {
   		  if (CurrentChordStyle->GetStyleName() != Chords[i].ChordStyleName) {
					delete LastChordStyle;
					LastChordStyle = CurrentChordStyle;
   		    CurrentChordStyle = new ChordStyle(Chords[i].ChordStyleName);
				}
      } else if (CurrentChordStyle->GetStyleName() != UserChordStyleName) {
				delete LastChordStyle;
				LastChordStyle = CurrentChordStyle;
				CurrentChordStyle = new ChordStyle(UserChordStyleName);
			}
			CurrentChordStyle->Play(Chords[i], Midi, &ControlRequest);
		}
	}
}
