/*
 * File:            XInputController.cpp
 * Author:          TheRealKasumi
 * Description:     This file provides an implementation for the Abstractcontroller to support XInput devices.
*/

#pragma comment(lib, "XInput.lib")

#include "XInputController.h"

XInputController::XInputController(const uint8_t controllerNumber)
{
    this->controllerNumber = controllerNumber;
}

bool XInputController::connect()
{
    return isConnected();
}

bool XInputController::isConnected()
{
    return poll() == ERROR_SUCCESS;
}

DWORD XInputController::poll()
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(controllerNumber, &state);

	if(result == ERROR_SUCCESS)
	{
		controllerState.A_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
		controllerState.B_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
		controllerState.X_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
		controllerState.Y_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
		controllerState.L_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		controllerState.R_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		controllerState.Plus_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		controllerState.Minus_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		controllerState.Home_Button = false;
		controllerState.D_Up = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		controllerState.D_Right = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		controllerState.D_Down = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		controllerState.D_Left = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		controllerState.Left_Stick_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		controllerState.Right_Stick_Button = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		controllerState.Left_Stick_X = state.Gamepad.sThumbLX;
		controllerState.Left_Stick_Y = state.Gamepad.sThumbLY;
		controllerState.Right_Stick_X = state.Gamepad.sThumbRX;
		controllerState.Right_Stick_Y = state.Gamepad.sThumbRY;
		controllerState.L_Trigger = state.Gamepad.bLeftTrigger;
		controllerState.R_Trigger = state.Gamepad.bRightTrigger;
		controllerState.cycleTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastCycle).count();
	}

	lastCycle = std::chrono::steady_clock::now();

    return result;
}

ControllerState XInputController::getControllerState()
{
    return controllerState;
}