/*
 * File:            ControllerEmulator.ino
 * Author:          TheRealKasumi
 * Description:     This programm reads the controller data sent via I2C and enulates an XInput controller.
*/

#include <Wire.h>
#include <XInput.h>
#include "ControllerState.h"

//This array stores the bytes that represent the controller state
char data[39] = {0};
volatile bool changed = false;

void setup() {
  //Initialize the I2C bus
  Wire.begin(9);
  Wire.setClock(800000);
  Wire.onReceive(receiveEvent);

  //Initialize the xinput emulation
  XInput.setAutoSend(false);
  XInput.begin();

  //Initialize the serial connection
  //This is used for debugging only
  Serial.begin(115200);
}

void receiveEvent(int len) {
  //Read the start-index of the data
  uint8_t startIndex = Wire.read();

  //Read the remaining data and load it into the array
  for (uint8_t i = startIndex; i < 39 && i < startIndex + len - 1; i++) {
    data[i] = Wire.read();
  }

  //If all data was read, set the changed flag
  if (startIndex + len - 1 == 39) {
    changed = true;
  }
}

void loop() {
  //Check the changed flag
  if (changed) {
    changed = false;

    //Copy the byte array into the controller state structure
    ControllerState controllerState;
    memcpy(reinterpret_cast<char*>(&controllerState), data, 39);
    
    //Handle the controller buttons
    handleControllerOutput(controllerState);
  }
}

void handleControllerOutput(ControllerState &controllerState) {
  XInput.setButton(BUTTON_A, controllerState.A_Button);
  XInput.setButton(BUTTON_B, controllerState.B_Button);
  XInput.setButton(BUTTON_X, controllerState.X_Button);
  XInput.setButton(BUTTON_Y, controllerState.Y_Button);
  XInput.setButton(BUTTON_LB, controllerState.L_Button);
  XInput.setButton(BUTTON_RB, controllerState.R_Button);
  XInput.setButton(BUTTON_START, controllerState.Plus_Button);
  XInput.setButton(BUTTON_BACK, controllerState.Minus_Button);
  XInput.setDpad(controllerState.D_Up, controllerState.D_Down, controllerState.D_Left, controllerState.D_Right);
  XInput.setButton(BUTTON_L3, controllerState.Left_Stick_Button);
  XInput.setButton(BUTTON_R3, controllerState.Right_Stick_Button);
  XInput.setJoystick(JOY_LEFT, controllerState.Left_Stick_X, controllerState.Left_Stick_Y);
  XInput.setJoystick(JOY_RIGHT, controllerState.Right_Stick_X, controllerState.Right_Stick_Y);
  XInput.setTrigger(TRIGGER_LEFT, controllerState.L_Trigger);
  XInput.setTrigger(TRIGGER_RIGHT, controllerState.R_Trigger);

  XInput.send();
}
