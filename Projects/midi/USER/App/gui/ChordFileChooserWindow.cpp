#include "ChordFileChooserWindow.hpp"
#include "ChordFileWindow.hpp"

ChordFileChooserWindow::ChordFileChooserWindow(MIDI::MIDI& Midi, class SD_Card& SD_Card): ChooserWindow(SD_Card), Midi(Midi) {
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
	ChordFileWindow* chordFileWindow = new ChordFileWindow(fileName, Midi, SD_Card);
	while (chordFileWindow->Refresh())
		GUI_Delay(50);
	delete chordFileWindow;
}
