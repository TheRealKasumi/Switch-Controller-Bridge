/*
 * File:            SerialToWireConverter.ino
 * Author:          TheRealKasumi
 * Description:     This programm reads the serial data sent from the pc programm. It then sends it to the second microcontroller
                    via I2C.
*/

#include <Wire.h>

void setup() {
  //Initialize the I2C bus
  Wire.begin();
  Wire.setClock(800000);

  //Initialize the serial connection
  Serial.begin(230400);
}

void loop() {
  //Read the 39 bytes for the controller state
  char rec[39] = {0};
  uint8_t read = 0;
  while (read < 39) {
    if (Serial.available()) {
      rec[read++] = Serial.read();
    }
  }

  //Transmit the first 20 bytes
  Wire.beginTransmission(9);
  Wire.write(0);
  for(uint8_t i = 0; i < 20; i++) {
    Wire.write(rec[i]); 
  }
  Wire.endTransmission();

  //Send the remaining 19 bytes
  Wire.beginTransmission(9);
  Wire.write(20);
  for(uint8_t i = 20; i < 39; i++) {
    Wire.write(rec[i]); 
  }
  Wire.endTransmission();

  //Send a message to the pc so it know that the controller
  //is ready to receive new data 
  Serial.write(1);
}
