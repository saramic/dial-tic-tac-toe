/*
   DotMatrixDisplay8X8.cpp - an 8x8 dot matrix dispaly for tic-tac-toe - implementation

   Copyright (c) 2020 Michael Milewski
*/

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// TODO: what is the deal with <...> includes?
//#include <DotMatrixDisplay8X8.h>
#include "DotMatrixDisplay8X8.h"
#include <LedControl.h> // TODO: make this a dependancy

#define SIZEOF_ARRAY(x) sizeof(x) / sizeof(x[0])

DotMatrixDisplay8X8::DotMatrixDisplay8X8(int dataPin, int clkPin, int csPin) {
  ledControl = LedControl(dataPin, clkPin, csPin, 1);
}

void DotMatrixDisplay8X8::init() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  ledControl.shutdown(0, false);
  /* Set the brightness to a medium values */
  ledControl.setIntensity(0, 8);
  /* and clear the display */
  ledControl.clearDisplay(0);
  showReady();
}

void DotMatrixDisplay8X8::init(HardwareSerial &print) {
  printer = &print;
  printer->begin(9600);
  printer->println("debug on dot matrix");
  init();
}

void DotMatrixDisplay8X8::showReady() {
  writeValues(showX);
  delay(1000);
  writeValues(showO);
  delay(1000);
  writeValues(grid);
  delay(1000);
}

void DotMatrixDisplay8X8::showBoard(int* board) {
  byte boardDisplay [8];
  //  memcpy(boardDisplay, board, sizeof(grid[0])*len);
  memcpy(boardDisplay, grid, sizeof(grid));
  for (int square = 0; square < 9; square++) {
    if (board[square] == 1) {
      placeXIn(square, boardDisplay);
    } else if (board[square] == 2) {
      placeOIn(square, boardDisplay);
    }
  }
  writeValues(boardDisplay);
}

void DotMatrixDisplay8X8::writeValues(byte* values) {
  //  TODO: how do you get size of an array of bytes? below returns 2, sizeof pointer?
  //  for (int row = 0; row < (sizeof(values) / sizeof(values[0])); row++) {
  for (int row = 0; row < 8; row++) {
    ledControl.setRow(0, row, values[row]);
  }
}

void DotMatrixDisplay8X8::showDemo() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdatedAt > 200) {
    if (demoState < 18) {
      int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      if (demoState < 9) {
        board[demoState] = 1;
      } else {
        board[demoState - 9] = 2;
      }
      showBoard(board);
    }
    if (demoState > 17) {
      if (demoState % 2 == 0) {
        writeValues(showX);
      } else {
        writeValues(winTypes[(33 - demoState) / 2]);
      }
    }
    demoState++;
    if (demoState > 33) {
      demoState = 0;
    }
    lastUpdatedAt = currentTime;
  }
  delay(10);
}

void DotMatrixDisplay8X8::placeXIn(int square, byte* boardDisplay) {
  switch (square) {
    case 0:
      boardDisplay[0] = boardDisplay[0] | B10000000;
      boardDisplay[1] = boardDisplay[1] | B01000000;
      break;
    case 1:
      boardDisplay[0] = boardDisplay[0] | B00010000;
      boardDisplay[1] = boardDisplay[1] | B00001000;
      break;
    case 2:
      boardDisplay[0] = boardDisplay[0] | B00000010;
      boardDisplay[1] = boardDisplay[1] | B00000001;
      break;
    case 3:
      boardDisplay[3] = boardDisplay[3] | B10000000;
      boardDisplay[4] = boardDisplay[4] | B01000000;
      break;
    case 4:
      boardDisplay[3] = boardDisplay[3] | B00010000;
      boardDisplay[4] = boardDisplay[4] | B00001000;
      break;
    case 5:
      boardDisplay[3] = boardDisplay[3] | B00000010;
      boardDisplay[4] = boardDisplay[4] | B00000001;
      break;
    case 6:
      boardDisplay[6] = boardDisplay[6] | B10000000;
      boardDisplay[7] = boardDisplay[7] | B01000000;
      break;
    case 7:
      boardDisplay[6] = boardDisplay[6] | B00010000;
      boardDisplay[7] = boardDisplay[7] | B00001000;
      break;
    case 8:
      boardDisplay[6] = boardDisplay[6] | B00000010;
      boardDisplay[7] = boardDisplay[7] | B00000001;
      break;
    default:
      break;
  }
}

void DotMatrixDisplay8X8::placeOIn(int square, byte* boardDisplay) {
  switch (square) {
    case 0:
      boardDisplay[0] = boardDisplay[0] | B11000000;
      boardDisplay[1] = boardDisplay[1] | B11000000;
      break;
    case 1:
      boardDisplay[0] = boardDisplay[0] | B00011000;
      boardDisplay[1] = boardDisplay[1] | B00011000;
      break;
    case 2:
      boardDisplay[0] = boardDisplay[0] | B00000011;
      boardDisplay[1] = boardDisplay[1] | B00000011;
      break;
    case 3:
      boardDisplay[3] = boardDisplay[3] | B11000000;
      boardDisplay[4] = boardDisplay[4] | B11000000;
      break;
    case 4:
      boardDisplay[3] = boardDisplay[3] | B00011000;
      boardDisplay[4] = boardDisplay[4] | B00011000;
      break;
    case 5:
      boardDisplay[3] = boardDisplay[3] | B00000011;
      boardDisplay[4] = boardDisplay[4] | B00000011;
      break;
    case 6:
      boardDisplay[6] = boardDisplay[6] | B11000000;
      boardDisplay[8] = boardDisplay[8] | B11000000;
      break;
    case 7:
      boardDisplay[6] = boardDisplay[6] | B00011000;
      boardDisplay[7] = boardDisplay[7] | B00011000;
      break;
    case 8:
      boardDisplay[6] = boardDisplay[6] | B00000011;
      boardDisplay[7] = boardDisplay[7] | B00000011;
      break;
    default:
      break;
  }
}
