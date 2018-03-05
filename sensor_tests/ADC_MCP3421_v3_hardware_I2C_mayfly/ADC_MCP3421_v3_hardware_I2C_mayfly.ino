/*****************************************************************************
ADC_MCP3421_v3_hardware_I2C_mayfly.ino
Written by:  Sander Smit <info@paleoterra.nl>
Modified by: Anthony Aufdenkampe <aaufdenkampe@limno.com>
             Beth Fisher <fisherba@umn.edu>
Hardware Platform: EnviroDIY Mayfly Arduino Datalogger
Software License: BSD-3.
  Copyright (c) 2017-2018, PaleoTerra and the EnviroDIY Development Team

This sketch meaures redox potential, in milli volts, for a
Paleo Terra Active Redox sensor with a built-in MCP3421 analog-to-digital converter,
and I2C communication.

Modified to:
  * Use Hardware Serial
  * Use the EnviroDIY Mayfly board

*****************************************************************************/

#include "Wire.h"  // Hardware I2C

//const int sdaPin = 10; // green wire  !! 10k pullup to Vdd !!
//const int sclPin = 11; // yellow wire  !! 10k pullup to Vdd !!
#define MCP3421 0x68

//SoftI2CMaster i2c = SoftI2CMaster( sclPin, sdaPin, 0 );

void setup() {
  pinMode(22, OUTPUT);    // power ON for 5V
  digitalWrite(22, HIGH);  // power ON for 5V

  Wire.begin(MCP3421); // join i2c bus (address optional for master)

  Serial.begin(115200); // Open serial connection to send info to the host
  while (!Serial) {}  // wait for Serial comms to become ready
  Serial.println("Starting up");
}

void loop() {

  Wire.beginTransmission( MCP3421 );
  Wire.write( B10001100 );  // initiate conversion, One-Shot mode, 18 bits, PGA x1
  Serial.println("I2C State"); //DEBUG!
  Serial.println(Wire.endTransmission()); //DEBUG!

  delay(300);  //255? // 18 bit conversion period; no polling (would be noisy) TODO fine-tune delay when almost ready, check RDY bit == 0 immediately

  Wire.requestFrom(MCP3421, 3, 0);  // As of Arduino 1.0.1, requestFrom() accepts a boolean argument changing its behavior for compatibility with certain I2C devices. See https://www.arduino.cc/en/Reference/WireRequestFrom
  // 18 bit
  byte res1 = Wire.read();
  byte res2 = Wire.read();
  byte res3 = Wire.read();
  // to fine-tune the delay between start of conversion and reading result:
  // - read one more byte from i2c
  // - MSB of this byte indicates conversion ready (0 = READY, 1 = NOT READY)
  Wire.endTransmission();

  // 18 bit
  float res;
  int sign = bitRead(res1,1); // one but least significant bit
  if (sign==1){
    res1 = ~res1; res2 = ~res2; res3 = ~res3; // two's complements
    res = bitRead(res1,0) * -1024; // 256 * 256 * 15.625 uV per LSB = 16
    res -= res2 * 4;
    res -= res3 * 0.015625;
    res -= 0.015625;
  } else {
    res = bitRead(res1,0) * 1024; // 256 * 256 * 15.625 uV per LSB = 16
    res += res2 * 4;
    res += res3 * 0.015625;
    Serial.print('+');
  }
  Serial.print(res); // , BIN);
  Serial.println(" mV");

  delay(1000);
}
