/*
   DotMatrixDisplay8X8.h - an 8x8 dot matrix dispaly for tic-tac-toe - description

   Copyright (c) 2020 Michael Milewski
*/
//#ifndef DotMatrixDisplay8X8_h
#define DotMatrixDisplay8X8_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <LedControl.h> // TODO: make this a dependancy

// grid
const static byte grid [8] = {
  B00100100,
  B00100100,
  B11111111,
  B00100100,
  B00100100,
  B11111111,
  B00100100,
  B00100100
};
// large X
const static byte showX [8] = {
  B11000011,
  B11000011,
  B01100110,
  B00111100,
  B00111100,
  B01100110,
  B11000011,
  B11000011
};
// large O
const static byte showO [8] = {
  B00111100,
  B01100110,
  B11000011,
  B11000011,
  B11000011,
  B11000011,
  B01100110,
  B00111100
};
// win row 1
const static byte winRow1 [8] = {
  B00000000,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
// win row 2
const static byte winRow2 [8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B00000000,
  B00000000,
  B00000000
};
// win row 3
const static byte winRow3 [8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111
};
// win col 1
const static byte winCol1 [8] = {
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000
};
// win col 2
const static byte winCol2 [8] = {
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00001000
};
// win col 3
const static byte winCol3 [8] = {
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001
};
// win diag 1
const static byte winDiag1 [8] = {
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001
};
// win diag 2
const static byte winDiag2 [8] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};
// win types
const static byte* winTypes[] = {winRow1, winRow2, winRow3, winCol1, winCol2, winCol3, winDiag1, winDiag2};

class DotMatrixDisplay8X8 {
  private:
    /* LedControl to write to the display */
    // TODO: how to only call constructor in my constructor?
    LedControl ledControl = LedControl(12, 11, 10, 1);
    /* write a byte array to the display */
    void writeValues(byte* values);
    /* optional serial printer for debugging*/
    HardwareSerial* printer;
    /* place an X in a square */
    void placeXIn(int square, byte* boardDisplay);
    /* place an O in a square */
    void placeOIn(int square, byte* boardDisplay);
    /* last updated at */
    unsigned long lastUpdatedAt = 0;
    /* demo state */
    int demoState = 0;

  public:
    /*
       Create a new display
       Params:
       dataPin  pin to shift data out
       clkPin   pin for the clock
       csPin    pin for selecting the device
    */
    DotMatrixDisplay8X8(int dataPin, int clkPin, int csPin);

    void init();
    void init(HardwareSerial &print);

    // TODO: can we just have a reference to the board?
    //    void init(int pinDataIn, int pinClk, int pinLoad);

    // show ready for user input
    void showReady();

    // show animated step by step move
    //    void showStepMove(int[] board, int currentStep);

    // show board state
    void showBoard(int* board);

    // show automated move
    //    void showInstantMove(int[] board, int position)

    // show winner
    //    void displayWinner(int[] board, int[] winningLine);

    // show demo
    void showDemo();
};

//#endif
