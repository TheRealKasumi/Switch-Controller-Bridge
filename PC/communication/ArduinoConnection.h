/*
 * File:            ArduinoConnection.h
 * Author:          TheRealKasumi
 * Description:     This file provides a class to connect to an arduino or similar microcontroller via a serial port. 
                    It also provides the functionality to send the controller state to the arduino. 
*/

#ifndef ArduinoConnectionH
#define ArduinoConnectionH

#include "../controller/ControllerState.h"
#include "../serial/SerialPort.h"

class ArduinoConnection
{
private:
    SerialPort *serial;

public:
    ArduinoConnection(const char *port, const uint32_t baud);
    ~ArduinoConnection();

    bool isConnected();
    int read(const char *buffer, unsigned int len);
    bool write(const char *buffer, unsigned int len);
    bool sendControllerState(ControllerState controllerState);
    void disconnect();
};

#endif