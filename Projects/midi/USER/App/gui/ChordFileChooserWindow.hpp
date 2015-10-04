#ifndef  __CHORDFILECHOOSERWINDOW_HPP__
#define  __CHORDFILECHOOSERWINDOW_HPP__

#include <EK/EK_tasks.hpp>
#include <EK/EK_gui.hpp>
#include <EK/EK_sd.hpp>
#include <EK/midi/EK_midi.hpp>
	
class ChordFileChooserWindow : public Window<ChordFileChooserWindow> {
  private:
		MIDI::MIDI& Midi;
	  SD_Card& SD_Card;
	  LISTBOX_Handle ChordFileListbox;
	  BUTTON_Handle CloseButton, OpenButton;
	  struct ChordFileDescriptor {
		  string FileName, Title, Artist;
			ChordFileDescriptor(string fileName): FileName(fileName) {
			  MIDI::ChordFile::GetInfo(FileName, &Title, &Artist);
			}
			string ToString(void) {
			  return Title + " - " + Artist;
			}
		};
	  vector<ChordFileDescriptor> ChordFileDescriptors;
		bool ShouldClose;
	  static void AddChordFile(char*, char*);
	
  public:
		ChordFileChooserWindow(MIDI::MIDI& Midi, class SD_Card&);
	  ~ChordFileChooserWindow();
	  void CloseButtonClicked(void);
	  void OpenButtonClicked(void);
	  virtual bool Refresh(void);
};

extern ChordFileChooserWindow* CurrentChordFileChooserWindow;

#endif
