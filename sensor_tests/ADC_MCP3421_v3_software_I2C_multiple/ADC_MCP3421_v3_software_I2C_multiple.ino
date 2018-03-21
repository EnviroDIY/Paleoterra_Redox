/*****************************************************************************
ADC_MCP3421_v3_software_I2C.ino
Written by:  Bobby Schultz <schu3119@umn.edu>
from original code by Sander Smit <info@paleoterra.nl>
Hardware Platform: Arduino-compatible board, currently EnviroDIY Mayfly

This sketch meaures redox potential, in milli volts, for a multi-sensor set of
Paleo Terra Active Redox sensor with a built-in MCP3421 analog-to-digital converter,
and I2C communication.

*****************************************************************************/

#include "SoftI2CMaster.h"

const int sdaPin = 7; // green wire  !! 10k pullup to Vdd !!
const int sclPin = 6; // yellow wire  !! 10k pullup to Vdd !!

const int sdaPin1 = 5;
const int sclPin1 = 4;

const int sdaPin2 = 11;
const int sclPin2 = 10;

#define MCP3421 0x68

SoftI2CMaster i2c = SoftI2CMaster( sclPin, sdaPin, 0 );
SoftI2CMaster i2c1 = SoftI2CMaster( sclPin1, sdaPin1, 0);
SoftI2CMaster i2c2 = SoftI2CMaster( sclPin2, sdaPin2, 0);


void setup() {
  pinMode(22, OUTPUT);    // power ON for 5V
  digitalWrite(22, HIGH);  // power ON for 5V

  Serial.begin(115200); // Open serial connection to send info to the host
  while (!Serial) {}  // wait for Serial comms to become ready
  Serial.println("Starting up");
}

void loop() {

  //INIT VARIABLES
  byte res1 = 0;
  byte res2 = 0;
  byte res3 = 0;
  
  //INIT I2C 0
  i2c.beginTransmission( MCP3421 );
  i2c.write( B10001100 );  // initiate conversion, One-Shot mode, 18 bits, PGA x1
  i2c.endTransmission();
  
  //INIT I2C 1
  i2c1.beginTransmission( MCP3421 );
  i2c1.write( B10001100 );  // initiate conversion, One-Shot mode, 18 bits, PGA x1
  i2c1.endTransmission();

  //INIT I2C 2
  i2c2.beginTransmission( MCP3421 );
  i2c2.write( B10001100 );  // initiate conversion, One-Shot mode, 18 bits, PGA x1
  i2c2.endTransmission();

  delay(300);  //255? // 18 bit conversion period; no polling (would be noisy) TODO fine-tune delay when almost ready, check RDY bit == 0 immediately
  
  //READ FROM I2C 0
  i2c.requestFrom( MCP3421 );
  res1 = i2c.read();
  res2 = i2c.read();
  res3 = i2c.readLast();
  i2c.endTransmission();

  // 18 bit
  Serial.print("Data 0: ");
  Serial.print(ProcessVoltage(res1, res2, res3)); // , BIN);
  Serial.println(" mV");  

  //READ FROM I2C 1
  i2c1.requestFrom( MCP3421 );
  res1 = i2c1.read();
  res2 = i2c1.read();
  res3 = i2c1.readLast();
  i2c1.endTransmission();

  // 18 bit
  Serial.print("Data 1: ");
  Serial.print(ProcessVoltage(res1, res2, res3)); // , BIN);
  Serial.println(" mV");

  //READ FROM I2C 2
  i2c2.requestFrom( MCP3421 );
  res1 = i2c2.read();
  res2 = i2c2.read();
  res3 = i2c2.readLast();
  i2c2.endTransmission();

  Serial.print("Data 2: ");
  Serial.print(ProcessVoltage(res1, res2, res3)); // , BIN);
  Serial.println(" mV");

  Serial.println("\n\n");
  delay(1000);
}

float ProcessVoltage(int res1, int res2, int res3) {
  float res = 0;
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
//    Serial.print('+'); //DEBUG!
  }
  return res; //Return voltage in milivolts
//  Serial.print(res); // , BIN);
//  Serial.println(" mV");
}

