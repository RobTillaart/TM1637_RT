//
//    FILE: TM1637_HEX.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo TM1637 library
//    DATE: 2021-02-15
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;

uint32_t start, stop;
volatile uint32_t val  = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.init(2, 3, 6);
  TM.displayClear();
  TM.displayHex(0xFEDCBA);
  delay(2000);
}


void loop()
{
  test();
  delay(1000);
}


void test()
{
  uint32_t d1, d2;
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    TM.displayHex(val);  // there is loop overhead etc
    val++;
  }
  stop = millis();
  Serial.print("TIME:\t");
  Serial.print(stop - start);
  Serial.print(" ms");
  d2 = stop - start;

  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    val++;
  }
  stop = millis();
  d1 = stop - start;
  Serial.print("\t");
  Serial.print(d2 - d1);
  Serial.println(" ms");
}


// -- END OF FILE --
