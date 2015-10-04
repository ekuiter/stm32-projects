#include "EK_midi.hpp"

namespace MIDI {
	MIDI::MIDI(USART_TypeDef* port, uint8_t channel): Port(port), Serial(port, 31250), Velocity(NOTE_ON_VELOCITY_DEFAULT) {
		SetChannel(channel);
	}

	uint8_t MIDI::GetChannel(void) {
		return Channel;
	}

	void MIDI::SetChannel(uint8_t channel) {
		if (channel < 1 || channel > 16)
			channel = 1;
		Channel = channel;
	}
	
	uint8_t MIDI::GetVelocity() {
	  return Velocity;
	}
	
	void MIDI::SetVelocity(uint8_t velocity) {
	  Velocity = velocity;
	}
	
	MIDITempo& MIDI::GetTempo() {
	  return Tempo;
	}
	
	void MIDI::SetTempo(MIDITempo tempo) {
	  Tempo = tempo;
	}

	void MIDI::NoteOn(Note note) {
		Write(Command::NoteOn, note.GetMIDINote(), Velocity & 0x7f);
	}

	void MIDI::NoteOff(Note note, uint8_t velocity) {
		Write(Command::NoteOff, note.GetMIDINote(), velocity & 0x7f);
	}
	
	void MIDI::AllNotesOff(void) {
	  Write(Command::ControlChange, 123, 0);
	}
	
	void MIDI::DelayBeats(double beats) {
		double bps = (double) Tempo / 60;
		double seconds = beats / bps;
	  DelayMs(seconds * 1000);
	}

	void MIDI::PlayNote(Note note, double beats) {
		NoteOn(note);
		DelayBeats(beats);
		NoteOff(note);
	}

	void MIDI::PlayScale(Key key, double beatsPerNote) {
		Note& note = key.GetNote();
		Mode mode = key.GetMode();
		uint8_t notes[] = { NOTE_C, NOTE_D, (mode == Major ? NOTE_E : NOTE_EF), NOTE_F, NOTE_G,
		  (mode == Major ? NOTE_A : NOTE_AF), (mode == Major ? NOTE_B : NOTE_BF), NOTE_C2 };
		for (int i = 0; i < 8; i++)
			PlayNote(Note(notes[i], note.GetOctave()) += note.GetNoteId(), beatsPerNote);
	}

	extern "C" uint8_t OSTimeDlyHMSM(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t ms);

	void MIDI::DelayMs(uint16_t duration) {
	  OSTimeDlyHMSM(0, 0, duration / 1000, duration % 1000);
	}
}
