#include "ChordFileChooserWindow.hpp"
#include "ChordFileWindow.hpp"

extern WM_HWIN CreateChooserWindow(void);

ChordFileChooserWindow::ChordFileChooserWindow(MIDI::MIDI& Midi, class SD_Card& SD_Card): ChooserWindow(CreateChooserWindow, SD_Card), Midi(Midi) {
  const int len = 100;
	char buf[len] = CHORDFILES_PATH;
  SD_Card.List(buf, len, AddFile);
}

void ChordFileChooserWindow::AddFile(char* path, char* fn) {
	string fileName = strtok(fn, "."), Title, Artist;
	MIDI::ChordFile::GetInfo(fileName, &Title, &Artist);
  LISTBOX_AddString(CurrentChooserWindow->Listbox, (Title + " - " + Artist).c_str());
	CurrentChooserWindow->FileNames.push_back(fileName);
}

void ChordFileChooserWindow::OpenFile(string fileName) {
	RunDialog(new ChordFileWindow(fileName, Midi, SD_Card));
}
