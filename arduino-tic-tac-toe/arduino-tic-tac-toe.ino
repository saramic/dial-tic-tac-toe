#include "DotMatrixDisplay8X8.h"

DotMatrixDisplay8X8 displayGame(12, 11, 10);

void setup() {
  displayGame.init();
  //  displayGame.init(Serial);
}

void loop() {
  displayGame.showDemo();
}
