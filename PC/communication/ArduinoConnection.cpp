/*
 * File:            ArduinoConnection.h
 * Author:          TheRealKasumi
 * Description:     This file provides a class to connect to an arduino or similar microcontroller via a serial connection. 
                    It also provides the functionality to send the controller state to the microcontroller. 
*/

#include "ArduinoConnection.h"

ArduinoConnection::ArduinoConnection(const char *port, const uint32_t baud)
{
    serial = new SerialPort(port, baud);
    if(!serial->isConnected())
    {
        delete serial;
        serial = 0;
    }    
}

ArduinoConnection::~ArduinoConnection()
{
    disconnect();
}

bool ArduinoConnection::isConnected()
{
    if(serial == 0)
    {
        return false;
    }

    return serial->isConnected();
}

int ArduinoConnection::read(const char *buffer, unsigned int len)
{
    if(!serial)
    {
        return 0;
    }

    return serial->read(buffer, len);    
}

bool ArduinoConnection::write(const char *buffer, unsigned int len)
{
    if(!serial)
    {
        return false;
    }

    return serial->write(buffer, len);
}

bool ArduinoConnection::sendControllerState(ControllerState controllerState)
{
    if(!serial)
    {
        return false;
    }

	char message[39];
    message[0] = controllerState.A_Button;
    message[1] = controllerState.B_Button;
    message[2] = controllerState.X_Button;
    message[3] = controllerState.Y_Button;
    message[4] = controllerState.L_Button;
    message[5] = controllerState.R_Button;
    message[6] = controllerState.Plus_Button;
    message[7] = controllerState.Minus_Button;
    message[8] = controllerState.Home_Button;
    message[9] = controllerState.D_Up;
    message[10] = controllerState.D_Right;
    message[11] = controllerState.D_Down;
    message[12] = controllerState.D_Left;
    message[13] = controllerState.Left_Stick_Button;
    message[14] = controllerState.Right_Stick_Button;
	memcpy(&message[15], reinterpret_cast<char*>(&controllerState.Left_Stick_X), sizeof(controllerState.Left_Stick_X));
    memcpy(&message[19], reinterpret_cast<char*>(&controllerState.Left_Stick_Y), sizeof(controllerState.Left_Stick_Y));
    memcpy(&message[23], reinterpret_cast<char*>(&controllerState.Right_Stick_X), sizeof(controllerState.Right_Stick_X));
    memcpy(&message[27], reinterpret_cast<char*>(&controllerState.Right_Stick_Y), sizeof(controllerState.Right_Stick_Y));
    memcpy(&message[31], reinterpret_cast<char*>(&controllerState.L_Trigger), sizeof(controllerState.L_Trigger));
    memcpy(&message[35], reinterpret_cast<char*>(&controllerState.R_Trigger), sizeof(controllerState.R_Trigger));

	return serial->write(message, 39);
}

void ArduinoConnection::disconnect()
{
    if(serial)
    {
        serial->closeSerial();
        delete serial;
        serial = 0;
    }
}