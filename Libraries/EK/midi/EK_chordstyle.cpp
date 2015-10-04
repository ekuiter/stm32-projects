#include "EK_chordstyle.hpp"
#include "EK_midi.hpp"
#include <string.h>

namespace MIDI {
	static char buf[LINE_BUFFER_LENGTH];
	ChordStyle* ChordStyle::LoadedChordStyle = NULL;
	
	ChordStyle::ChordStyle(string styleName): StyleName(styleName), ParseSuccess(false) {
		const char* path = (string(CHORDSTYLES_PATH) + "/" + StyleName + CHORDSTYLES_SUFFIX).c_str();
	  FILE* f = fopen(path, "r");
		if (!f) {
			printf("File could not be opened: %s\r\n", buf);
		  return;
		}
		fgets(buf, LINE_BUFFER_LENGTH, f);
		ReadPhases(MajorPhases, f);
		ReadPhases(MinorPhases, f);
		fclose(f);
		ParseSuccess = true;
	}
	
  void ChordStyle::Play(Chord& chord, MIDI& midi, ControlRequest* controlRequest) {
		if (!ParseSuccess)
			return;
		double remainingBeats = chord.Beats;
		Note& note = chord.Key.GetNote();
		Mode mode = chord.Key.GetMode();
		vector<ChordPhase>& phases = mode == Major ? MajorPhases : MinorPhases;
		while (remainingBeats > 0.01) {
		  for (int i = 0; i < phases.size() && remainingBeats > 0.01; i++) {
				for (int j = 0; j < phases[i].NoteNumber; j++)
					midi.NoteOn(phases[i].Notes[j] + note);
				double delayBeats = phases[i].Beats == 0 ? remainingBeats : phases[i].Beats;
				remainingBeats -= delayBeats;
				if (controlRequest != NULL)
				  controlRequest->Beat += delayBeats;
				midi.DelayBeats(delayBeats);
				for (int j = 0; j < phases[i].NoteNumber; j++)
					midi.NoteOff(phases[i].Notes[j] + note);
				if (controlRequest != NULL) {
				  if (controlRequest->State == PauseState)
						controlRequest->PlayTask->Suspend();
					else if (controlRequest->State == StopState)
						controlRequest->PlayTask->Delete();
				}
			}
		}
	}
	
	string ChordStyle::GetStyleName() {
		return StyleName;
	}
	
	void ChordStyle::ReadPhases(vector<ChordPhase>& phases, FILE* f) {
		while (fgets(buf, LINE_BUFFER_LENGTH, f) && strcmp(buf, "Minor\r\n") != 0) {
			vector<Note> notes;
			int bufLen = strlen(buf);
			if (buf[bufLen - 2] == '\r')
			  buf[bufLen - 2] = '\0';
			char* note = strtok(buf, "\t");
			double beats = atof(note);
			if (beats != 0)
			  note = strtok(NULL, "\t");
			while (note != NULL) {
			  Heap.Debug<Note>("Pushing Note");
				notes.push_back(Note(note));
				note = strtok(NULL, "\t");
			}
			ChordPhase phase = { notes, notes.size(), beats };
			Heap.Debug("Pushing ChordPhase", phase);
			phases.push_back(phase);
		}
	}
}
