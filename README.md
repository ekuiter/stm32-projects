# Hy-Mini STM32 Projects

These are all my projects made for the **ARM Cortex-M3 STM32 platform** (using the **Hy-Mini STM32 Board** with LCD display, Touchscreen and SD card).

I use Keil MDK-ARM v5 on Windows 7. Because Keil really depends on the correct directory structure, this is one big repository instead of many small ones.
The individual directories' contents are described below.

## Legacy

These are my first attempts at using the ARM platform.

- **gui_bmp**: displays C-coded bitmaps and uses buttons and multitasking to showcase ucOS-II
- **led_button_interrupt**: press user buttons to light LEDs, uses plain STM32F10x Library
- **led_button_interrupt_ek**: rewritten `led_button_interrupt` with the EK library
- **led_button_loop**: same as `led_button_interrupt`, but without interrupts (just a run loop)
- **led_timer**: plain STM32F10x for timed LED blinking
- **sd**: lists all files on an SD card and the available space
- **sd_bmp**: displays a C-streamed bitmap from an SD card
- **HEX**: some HEX files which can be uploaded directly to the board (using the STM32 ST-Link Utility)

## Libraries

All the libraries my projects use. Most of them are NOT made by me (with one exception, the `EK` library).

- **CMSIS**: tools for Cortex-M3 processors
- **EK**: my own general-purpose library, described in detail below
- **FATFS**: an implementation of the FAT32 filesystem, used with SD cards
- **GLCD**: an LCD driver used by uCGUI
- **jdksmidi**: a MIDI sequencer I'd like to use with my `midi` project - doesn't work yet
- **SD_Card_**: an SD card driver used by various projects
- **STM32F10x_StdPeriph_Driver**: Standard library for STM32 processors, used practically everywhere
- **TouchPanel**: a Touchscreen driver used by uCGUI
- **uC-CPU**: Supporting library for uCOS-II
- **uC-LIB**: Supporting library for uCOS-II
- **uCGUI_LIB**: a GUI library used by various projects
- **uCOS-II**: a compact operating system with multitasking, stack management etc.

### The `EK` library

This is my own library targeted at the Hy-Mini STM32 Board. It is mostly a C++ wrapper for APIs I often use.

- **EK_config**: EXTI and NVIC configuration
- **EK_gpio**: simple GPIO configuration like this: `GPIO_Pin LED("PB0", GPIO_Mode_Out_PP); LED.On(); LED.Off();`
- **EK_gui**: uCGUI window handling, Touchscreen configuration / debouncing / blocking
- **EK_retarget**: Heap analysis, support for `printf`, `sprintf`, `fprintf`, `scanf`, `fopen`, `fclose`, `fgetc`, `fgets`, `fputc`, `fputs`, `feof`, `rewind`
- **EK_sd**: SD Card support for mounting, reading, writing, listing & printing files and formatting SD cards
- **EK_tasks**: Stack analysis, create, run, suspend, resume and delete tasks
- **EK_usart**: USART configuration, easy reading and writing
- **midi/EK_chordfile**: ChordFile class for playing, pausing and seeking chord files
- **midi/EK_chordstyle**: ChordStyle class for playing a single chord in a certain way
- **midi/EK_key**: Key class representing a key (C, D#, Ebm)
- **midi/EK_midi**: MIDI class for sending and receiving MIDI messages (such as Note On / Off)
- **midi/EK_note**: Note class representing a note (C3, D#4, Eb5)

## Projects

The actual projects I made for the STM32 processor.

- **_template_os_gui**: A general-purpose template with ucOS-II and ucGUI enabled by default.
  Use this as a starting point for all kinds of projects (LCD / Touchscreen / GUI / SD Card).
- **gui_sd**: This project lets you browse a FAT32-formatted SD card as well as reading and writing files.
  There is also a simple GUI which can show images with a special format.
- **midi**: see below

### The `midi` project

This project combines almost everything listed above.
It can communicate with a MIDI device with MIDI-IN and MIDI-OUT. Currently it can play back certain SD card files on a MIDI device.
The playable files are called `ChordFiles` and saved to the `chordfiles` directory on the SD card.
An example `ChordFile`, `chordfiles/example.txt`:
  
    Song title
    Song artist
    120             # this is the tempo in bpm

    #Verse 1        # an arbitrary name for a section
    !classic        # this loads the specified ChordStyle

    C	  4           # which chord to play and how long:
    D#	2           # key     | sharp / flat (optional) | minor (optional) | <TAB>        | number of beats
    Ebm	2           # CDEFGAB | # / b                   | m                | (no spaces!) | 1, 2, ... (integers!)

    #Pre-Chorus     # multiple sections and
    !stride         # ChordStyles are allowed
    
    ...             # IMPORTANT: no newline at end of file!
    
`ChordStyles` specify how chords are played. They are placed in the `chordstyles` directory. An example, `chordstyles/example.txt`:

    Major           # how to play a major chord
    0.5 C3          # see above:
    0.5	E3          # number of beats (floats allowed, 3 decimal places max) | <TAB>        | note(s) to play: key     | octave
    0.5	G3 C4       # 0.5, 0.333, 1, 1.5 (should add up to an integer!)      | (no spaces!) |                  CDEFGAB | -1 .. 9 (integer)
    0.5	E3
    Minor           # how to play a minor chord
    0.5	C3          # see above.
    0.5	Eb3
    0.5	G3 C4
    0.5	Eb3         # IMPORTANT: no newline at end of file!
    
Playback can be paused, resumed, seeked and stopped, volume (MIDI velocity) and tempo can be adjusted.
    
As of now, `midi` can not play back standard MIDI files. Further, reading data from MIDI-IN is already implemented in the API,
but not yet in the GUI.

## Utilities

These are some supporting files MDK-ARM uses. You shouldn't need to use them directly.