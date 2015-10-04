#ifndef __EK_MIDI_MIDI_HPP
#define __EK_MIDI_MIDI_HPP

#include "../EK_usart.hpp"
#include "EK_note.hpp"
#include "EK_key.hpp"
#include "EK_chordfile.hpp"
#include <jdksmidi/world.h>
#include <jdksmidi/tempo.h>
#include "../EK_retarget.hpp"

#define NOTE_STRING_MAX_LENGTH    6 // e.g.: Ebm-1\0
#define NOTE_ON_VELOCITY_DEFAULT  64
#define NOTE_OFF_VELOCITY_DEFAULT 48
#define LINE_BUFFER_LENGTH 40
#define CHORDSTYLES_PATH "chordstyles" // no trailing slash!
#define CHORDSTYLES_SUFFIX ".txt" // dot is required!
#define CHORDSTYLES_DEFAULT "triad" // no path / suffix!
#define CHORDFILES_PATH "chordfiles"
#define CHORDFILES_SUFFIX ".txt"

using jdksmidi::MIDITempo;

namespace MIDI {
	namespace Command {
		enum Command {
			NoteOff = 0x80, NoteOn = 0x90, AftertouchPolyphonic = 0xa0, ControlChange = 0xb0, ProgramChange = 0xc0, Aftertouch = 0xd0, PitchBendChange = 0xe0, System = 0xf0
		};
	};
	
	struct Message {
		uint8_t Command;
		uint8_t Channel;
		uint8_t* Data;
		Message(uint8_t cmd, uint8_t chan, uint8_t* data): Command(cmd), Channel(chan), Data(data) {}
		
		~Message() {
		  delete[] Data;
		}
		
		bool Is(Command::Command command) {
			return Command == command;
		}
		
		Note GetNote(void) {
		  if (Is(Command::NoteOn) || Is(Command::NoteOff) || Is(Command::AftertouchPolyphonic))
				return Note(Data[0]);
			return Note("C");
		}
		
		int8_t GetVelocity(void) {
		  if (Is(Command::NoteOn) || Is(Command::NoteOff) || Is(Command::AftertouchPolyphonic))
				return Data[1];
			return -1;
		}
	};
	
	class MIDI {
		private:		
			USART_TypeDef* Port;
			USART Serial;
			uint8_t Channel;
		  uint8_t Velocity;
		  MIDITempo Tempo;
		  void DelayMs(uint16_t);
		
			uint8_t ReadByte(void) {
				while (!USART_GetITStatus(Port, USART_IT_RXNE));
				return USART_ReceiveData(Port);
			}
		
		public:
			MIDI(USART_TypeDef*, uint8_t = 1);
			uint8_t GetChannel(void);
			void SetChannel(uint8_t);
		  uint8_t GetVelocity();
		  void SetVelocity(uint8_t);
		  MIDITempo& GetTempo();
		  void SetTempo(MIDITempo);
			void NoteOn(Note);
			void NoteOff(Note, uint8_t = NOTE_OFF_VELOCITY_DEFAULT);
		  void AllNotesOff(void);
		  void DelayBeats(double);
			void PlayNote(Note, double);
			void PlayScale(Key, double);
		
			Message Read(void) {
				uint8_t status;
				while(((status = ReadByte()) >> 7) == 0);
				uint8_t	command = status & 0xf0, channel = status & 0xf;
				int dataLength = 0;
				switch (command) {
					case Command::NoteOff:
					case Command::NoteOn:
					case Command::AftertouchPolyphonic:
					case Command::ControlChange:
					case Command::PitchBendChange:
						dataLength += 2;
						break;
					case Command::ProgramChange:
					case Command::Aftertouch:
						dataLength += 1;
						break;
					case Command::System:
						dataLength += 0;
						break;
				}
				printf("IN: 0x%02x", status);
				uint8_t* data = new uint8_t[dataLength];
				for (int i = 0; i < dataLength; i++) {
				  data[i] = ReadByte();
				  printf(" 0x%02x", data[i]);
				}
				return Message(command, channel, data);
			}
			
			bool Available(void) {
			  return Serial.Available();
			}
		
			void Write(uint8_t status) {
				//printf("OUT: 0x%02x\r\n", (status & 0xf0) | (Channel - 1));
				Serial.Write((status & 0xf0) | (Channel - 1));
			}	

			void Write(uint8_t status, uint8_t data1) {
				//printf("OUT: 0x%02x 0x%02x\r\n", (status & 0xf0) | (Channel - 1), data1);
				Serial.Write((status & 0xf0) | (Channel - 1));
				Serial.Write(data1);
			}

			void Write(uint8_t status, uint8_t data1, uint8_t data2) {
				//printf("OUT: 0x%02x 0x%02x 0x%02x\r\n", (status & 0xf0) | (Channel - 1), data1, data2);
				Serial.Write((status & 0xf0) | (Channel - 1));
				Serial.Write(data1);
				Serial.Write(data2);
			}
	};
}

#endif
