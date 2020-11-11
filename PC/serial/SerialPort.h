/*
 * File:            SerialPort.h
 * Author:          TheRealKasumi
 * Description:     This file provides a class to establish a serial connection to an device.
*/

#ifndef SerialPortH
#define SerialPortH

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>

class SerialPort
{
private:
    HANDLE handle;
    bool connected;
    COMSTAT status;
    DWORD error;
    
public:
    explicit SerialPort(const char *port, const DWORD baudRate);
    ~SerialPort();

    bool isConnected();
    int read(const char *buffer, unsigned int len);
    bool write(const char *buffer, unsigned int len);
    void closeSerial();
};

#endif