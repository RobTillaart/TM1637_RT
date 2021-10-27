//
//    FILE: TM1637_keypress_raw.ino
//  AUTHOR: William F. Dudley Jr.
// VERSION: 0.1.0
// PURPOSE: demo TM1637 library - keyscan() raw output
//    DATE: 2021-10-26
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;

// Note: 
// TM1637 boards need a pull up resistor from DIO to 3.3V for keyscan() to work.  
// 910 ohms or 1 Kohm works, the value isn't critical.

// TRIGGER is scope trigger signal for development.
// Comment out the #define if you don't need it or feel free to change to any unused pin.
// Hook your oscilloscope or logic analyzer trigger to it.
// This allows experimenting with the pull-up resistor from DIO to 3.3V.  
// Smaller values decrease rise time (a good thing) but too small and the microcontroller
// can't pull the line down (a bad thing).


// #if defined(ESP8266) || defined(ESP32)
// #define dispCLOCK D3
// #define dispDATA D4
// #define TRIGGER D1
// #else
#define dispCLOCK 3
#define dispDATA 4
#define TRIGGER 5
// #endif


void setup()
{
  Serial.begin(115200);
  delay(200);
  Serial.print("\n");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  Serial.println(__FILE__);

  TM.init(dispCLOCK, dispDATA);
#ifdef TRIGGER
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);
#endif
  TM.setBrightness(1);
  TM.displayClear();
}

char button_poll(void) {
#ifdef TRIGGER
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(1);
  digitalWrite(TRIGGER, LOW);
#endif
  uint8_t keypress = TM.keyscan();
  TM.displayHex(keypress);
  if(keypress < 0xfe) {
    Serial.print(F("KEYPRESS "));
    Serial.println(keypress, HEX);
  }
  return '\0';
}

void loop()
{
char c;
  c = button_poll();
#ifndef TRIGGER
  // for oscilloscope testing, don't delay for faster repetition rate
  delay(50);
#endif
}

// -- END OF FILE --
