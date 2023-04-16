//
//    FILE: TM1637_displayCelsius.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;

int temperature = -9;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.begin(7, 6, 4);       //  clockpin, datapin, #digits
}


void loop()
{
  //  adjust brightness to temperature, just because it can be done.
  if (temperature < 0) TM.setBrightness(0);
  else TM.setBrightness(temperature / 20);

  //  simulate temperature
  TM.displayCelsius(temperature);  //  default colon off.
  temperature++;
  if (temperature == 100) temperature = -9;
  delay(250);
}


//  -- END OF FILE --
