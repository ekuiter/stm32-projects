#include "tasks.hpp"
#include <includes.h>
#include <EK.hpp>
#include <jdksmidi/world.h>
#include <jdksmidi/midi.h>
#include <jdksmidi/fileread.h>
#include <jdksmidi/fileshow.h>
#include <jdksmidi/sequencer.h>
#include <jdksmidi/filereadmultitrack.h>
#include "gui/MainWindow.hpp"
#include "gui/KeyboardWindow.hpp"
#include <gui_style.hpp>

using namespace::jdksmidi;

static void RunTouchPanelTask(void);
static void RunGUITask(void);

static Task<TouchPanelTaskStackSize> TouchPanelTask("TouchPanelTask", RunTouchPanelTask);
static Task<GUITaskStackSize> GUITask("GUITask", RunGUITask);

namespace MIDI {
	extern void RunChordFilePlayTask(ChordFile*);
}

simpleRunFunc_t PriorityTable[] = {
  (simpleRunFunc_t) MIDI::RunChordFilePlayTask,
  RunTouchPanelTask,
	RunGUITask,
	NULL
};

static USART Serial(USART1, 115200);
SD_Card SD_Card;
MIDI::MIDI Midi(USART2);

void AppInit(void) {
	printf("Welcome!\r\n");
	Heap.StartAnalysis();
	Midi.AllNotesOff();
	SD_Card.Mount();
  SD_Card.PrintSize();
	TouchPanelTask.Run();
  GUITask.Run();
	/*while (1) {
	  if (Midi.Available()) {
		  MIDI::Message message = Midi.Read();
		  if (message.Is(MIDI::Command::NoteOn))
		  	printf("%s\n", static_cast<string>(message.GetNote()).c_str());
  	}
	}*/
	while (1) {
		Task<>::ReportStackUsages();
		Heap.ReportHeapUsage();
		printf("\r\n");
	  OSTimeDlyHMSM(0, 0, 5, 0);
	}
}

static void RunTouchPanelTask(void) {   
	while (1) {
	 GUI_TOUCH_Exec();
	 OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

static void RunGUITask(void) {
	GUI_Touch_Config();
	WINDOW_SetDefaultBkColor(GUI_STYLE_MAIN);
	MainWindow::RunDialog(new MainWindow());
	GUI_Clear();
	GUITask.Delete();
}

/*static void RunMIDITask(void) {	
	/MIDIFileReadStreamFile rs("kaze.mid");
	//MIDIMultiTrack tracks(1);
	//MIDIFileReadMultiTrack track_loader(&tracks);
	MIDIFileShow shower(NULL, true);
	MIDIFileRead reader(&rs, &shower);
  //MIDIFileRead reader(&rs, &track_loader);
	
  //printf("number of tracks: %d, %d", tracks.GetNumTracks(), reader.ReadNumTracks());
	// set amount of tracks equal to midifile
	//tracks.ClearAndResize(reader.ReadNumTracks());
	//printf("number of tracks: %d, %d", tracks.GetNumTracks(), reader.ReadNumTracks());

  // MIDISequencerGUIEventNotifierText notifier( stdout );
  // MIDISequencer seq( &tracks, &notifier );
	//MIDISequencer seq(&tracks);

	// load the midifile into the multitrack object
	printf("BEFORE\r\n");
	if (!reader.Parse())
		printf("Error parsing file\r\n");
  printf("AFTER\r\n");
	
	//DumpMIDIMultiTrack(&tracks);
	//PlayDumpSequencer(&seq);
	//double dt = seq.GetMisicDurationInSeconds();
	//printf("Duration in seconds: %f\r\n", dt);/
}*/
