/*
 * File:            SerialPort.h
 * Author:          TheRealKasumi
 * Description:     This file provides a class to establish a serial connection to an device.
*/

#include "SerialPort.h"

SerialPort::SerialPort(const char *port, const DWORD baudRate)
{
    connected = false;

    handle = CreateFileA(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

	if(handle != INVALID_HANDLE_VALUE)
	{
        DCB serialParameters = {0};
        if(GetCommState(handle, &serialParameters))
        {
            serialParameters.BaudRate = baudRate;
            serialParameters.ByteSize = 8;
            serialParameters.StopBits = ONESTOPBIT;
            serialParameters.Parity = NOPARITY;
            serialParameters.fDtrControl = DTR_CONTROL_ENABLE;
            if (SetCommState(handle, &serialParameters))
            {
                connected = true;
                PurgeComm(handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if(connected)
    {
        connected = false;
        try 
        {
            CloseHandle(handle);
        }
        catch(...)
        {}
    }
}

bool SerialPort::isConnected()
{
    if(!ClearCommError(handle, &error, &status))
    {
        connected = false;
    }

    return connected;
}

int SerialPort::read(const char *buffer, const unsigned int len)
{
	DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(handle, &error, &status);

    if(status.cbInQue > 0)
    {
        if(status.cbInQue > len)
        {
            toRead = len;
        }
        else
        {
            toRead = status.cbInQue;
        }
    }

	memset((void*)buffer, 0, len);

	if(ReadFile(handle, (void*)buffer, toRead, &bytesRead, NULL))
    {
        return bytesRead;
    }

    return 0;
}

bool SerialPort::write(const char *buffer, const unsigned int len)
{
    DWORD bytesSend;

	if(!WriteFile(handle, (void*)buffer, len, &bytesSend, 0))
    {
        ClearCommError(handle, &error, &status);
        return false;
    }
    
    return true;
}

void SerialPort::closeSerial()
{
    CloseHandle(handle);
}
