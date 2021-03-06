/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        �C/GUI-BitmapConvert-Demo V5.26.                            *
*        Compiled Aug  8 2014, 14:40:24                              *
*                                                                    *
*        (c) 2002-2014  Micrium, Inc.                                *
*        www.micrium.com                                             *
*                                                                    *
*        (c) 1998-2014  Segger Microcontroller GmbH & Co. KG         *
*        www.segger.com                                              *
*                                                                    *
*        May not be used in a product                                *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: chordFile                                             *
* Dimensions:  90 * 90                                               *
* NumColors:   4                                                     *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmchordFile;

/*********************************************************************
*
*       Palette
*
*  Description
*    The following are the entries of the palette table.
*    The entries are stored as a 32-bit values of which 24 bits are
*    actually used according to the following bit mask: 0xBBGGRR
*
*    The lower   8 bits represent the Red   component.
*    The middle  8 bits represent the Green component.
*    The highest 8 bits represent the Blue  component.
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorschordFile[] = {
  0xFBFBFB, 0x636363, 0x9D9D9D, 0x101010
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalchordFile = {
  4,  // Number of entries
  1,  // Has transparency
  &_ColorschordFile[0]
};

static GUI_CONST_STORAGE unsigned char _acchordFile[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xA5, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xFE, 0x09, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xD0, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xC0, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x40, 0x0B, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x2A, 0xAA, 0xAA, 0xAA, 0xA7, 0x6A, 0xA7, 0xEA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x00,
  0x00, 0x95, 0xAA, 0xAA, 0xAA, 0xA7, 0x5A, 0x5F, 0xDA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x60, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x09, 0x80, 0x1F, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x09, 0x80, 0xBF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x01, 0x80, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x01, 0x81, 0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x01, 0x4B, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x02, 0x5F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x96, 0xAA, 0xAA, 0xAA, 0xA7, 0xFF, 0xDA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x00,
  0x00, 0x95, 0x55, 0x55, 0x55, 0x7F, 0xFF, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x60, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0xBF, 0xFD, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x02, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x0B, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x2F, 0xFF, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0xBF, 0xFD, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x7F, 0xF6, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x01, 0xFF, 0xD8, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x0B, 0xFF, 0x40, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x96, 0xAA, 0xA7, 0xFF, 0x6A, 0xAD, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x00,
  0x00, 0x95, 0x55, 0x5F, 0xFD, 0x55, 0x7F, 0xFF, 0xD5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x60, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0xF8, 0x02, 0x7F, 0xFF, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0xD0, 0x09, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0xE0, 0x07, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x1F, 0x40, 0x2F, 0xFF, 0xD7, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0x40, 0x1F, 0xD9, 0xE2, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x55, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0x80, 0x1F, 0x42, 0xE0, 0x1F, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x09, 0xF6, 0xA7, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0x80, 0xBD, 0x02, 0xE0, 0x27, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x27, 0xF8, 0x01, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x2F, 0x80, 0xBE, 0x00, 0xD0, 0x0B, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x02, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x96, 0xAA, 0x9F, 0x6A, 0x7D, 0xAA, 0xFA, 0xA7, 0xF6, 0xAA, 0xAA, 0xAA, 0xAA, 0xBF, 0xFA, 0xAA, 0x7F, 0xDA, 0xAA, 0xAA, 0xA0, 0x00,
  0x00, 0x95, 0x55, 0x5F, 0xD5, 0x7F, 0x55, 0xF5, 0x57, 0xF5, 0x55, 0x55, 0x55, 0x55, 0x7F, 0xFD, 0x55, 0x7F, 0xF5, 0x55, 0x55, 0x60, 0x00,
  0x00, 0x98, 0x00, 0x0B, 0x40, 0x2D, 0x00, 0xB8, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x09, 0xE0, 0x07, 0x80, 0xB8, 0x01, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x27, 0xFD, 0x00, 0x1F, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x02, 0xD0, 0x09, 0x40, 0x14, 0x0B, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x09, 0xFF, 0x40, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x74, 0x02, 0x60, 0x14, 0x0B, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0xDA, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x9E, 0x00, 0x20, 0x26, 0x2F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x7F, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x27, 0x60, 0x00, 0x2E, 0x9D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF6, 0xA7, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x01, 0xD8, 0x00, 0x25, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xF8, 0x01, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0x9D, 0x6A, 0xAF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x02, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x9A, 0xAA, 0xAA, 0xAA, 0xA5, 0xFF, 0xFF, 0x6A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBF, 0xFA, 0xAA, 0x7F, 0xDA, 0xAA, 0xAA, 0xA0, 0x00,
  0x00, 0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5F, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7F, 0xFD, 0x55, 0x7F, 0xF5, 0x55, 0x55, 0x50, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xFD, 0x00, 0x1F, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xFF, 0x40, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0xDA, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x80, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x7F, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xD0, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF6, 0x27, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xF8, 0x02, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xF8, 0x01, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF4, 0x02, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x02, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xF4, 0x02, 0x60, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xBF, 0xFA, 0xAA, 0x7F, 0xDA, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xF4, 0x02, 0x60, 0x00, 0x00, 0x00, 0x00, 0x25, 0x7F, 0xFD, 0x55, 0x7F, 0xF5, 0x60, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF8, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0xFF, 0x60, 0x09, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xFD, 0x00, 0x1F, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7D, 0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xFF, 0x40, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x55, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x5A, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x55, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmchordFile = {
  90, // xSize
  90, // ySize
  23, // BytesPerLine
  2, // BitsPerPixel
  _acchordFile,  // Pointer to picture data (indices)
  &_PalchordFile   // Pointer to palette
};

/*************************** End of file ****************************/
