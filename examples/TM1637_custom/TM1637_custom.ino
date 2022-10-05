//
//    FILE: TM1637_custom.ino
//  AUTHOR: Richard Jones
// VERSION: 0.1.0
// PURPOSE: demo TM1637 library
//    DATE: 3 October 2022
//     URL: https://github.com/radionerd

// Demonstration of how to display char *buff and override the TM1637 library asciiTo7Segment virtual function
// to create a custom 7 segment character set. 
// The letter 'A' becomes swapped with @ in this trivial example



#include "TM1637.h"

const int DISPLAY_DIGITS_6 = 6;
 
class myTM1637 : TM1637 {
  public:
  void setBrightness(uint8_t b) { TM1637::setBrightness(b);};
  
  void begin(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6) {TM1637::begin(clockPin,dataPin,digits);};
  
  void displayPChar( char * data ) { TM1637::displayPChar( &data[0] );};
  
  uint8_t asciiTo7Segment ( char c ) { // Override library ascii to 7 segment conversion

    //        -01-
    //    20 |    | 02
    //        -40-
    //    10 |    | 04
    //        -08-    .80

    //7+1  Segment patterns for ASCII 0x30-0x5F
    const uint8_t asciiTo8Segment[] = { 
      0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07, // 0123 4567 
      0x7f,0x6f,0x09,0x89, 0x58,0x48,0x4c,0xD3, // 89:; <=>?
      0x77,0x5f,0x7c,0x39, 0x5E,0x79,0x71,0x3d, // @aBC DEFG NB: @ <-> A in this derived class
      0x76,0x06,0x0E,0x75, 0x38,0x37,0x54,0x5c, // HIJK LMNO
      0x73,0x67,0x50,0x6D, 0x78,0x3E,0x1C,0x9c, // PQRS TUVW
      0x76,0x6E,0x5B,0x39, 0x52,0x0F,0x23,0x08  // XYZ[ /]^_
    };

    uint8_t  segments = c &0x80;
    c &= 0x7f;
    if ( c >= 0x60 ) c -= 0x20 ; // a-z -> A-Z
    if ( c == '.' ) segments = 0x80; // decimal point only
    if ( c == '-' ) segments |= 0x40; // minus sign
    if ( ( c >= 0x30 ) && ( c <= 0x5F ) ) {
      int index = c - 0x30;
      segments |= asciiTo8Segment[index];
    }
    return segments;
  }
};

myTM1637 myTM;

const int ADC_PIN = PA0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(__FILE__);

  myTM.begin(PB8, PB9 , DISPLAY_DIGITS_6 );       //  clockpin, datapin, digits

  myTM.setBrightness(2);
  
}


void loop()
{
  char buff[20];
  // Show A and @ swapped over on custom character set
  sprintf(buff,"@-A%3d", millis()/1000 );
  myTM.displayPChar(buff);
  Serial.println(buff); // Display and serial monitors disagree on A-@ symbols
  delay(1000);
}


// -- END OF FILE --
