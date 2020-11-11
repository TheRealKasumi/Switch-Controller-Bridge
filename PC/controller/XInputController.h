/*
 * File:            XInputController.h
 * Author:          TheRealKasumi
 * Description:     This file provides an implementation for the Abstractcontroller to support XInput devices.
*/

#ifndef XInputControllerH
#define XInputControllerH

#include <stdint.h>
#include <windows.h>
#include <xinput.h>
#include <chrono>
#include "AbstractController.h"

class XInputController : AbstractController
{
private:
	std::chrono::steady_clock::time_point lastCycle = std::chrono::steady_clock::now();

public:
    XInputController(const uint8_t controllerNumber);

    bool connect();
    bool isConnected();
    DWORD poll();
    ControllerState getControllerState();
};

#endif