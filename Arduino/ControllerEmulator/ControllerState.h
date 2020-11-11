/*
 * File:            ControllerState.h
 * Author:          TheRealKasumi
 * Description:     This file provides a structure that holds the current state of the controller.
*/

#ifndef ControllerStateH
#define ControllerStateH

#include <stdint.h>

typedef struct ControllerState
{
    bool A_Button;
    bool B_Button;
    bool X_Button;
    bool Y_Button;
    bool L_Button;
    bool R_Button;
    bool Plus_Button;
    bool Minus_Button;
    bool Home_Button;
    bool D_Up;
    bool D_Right;
    bool D_Down;
    bool D_Left;
    bool Left_Stick_Button;
    bool Right_Stick_Button;
    int32_t Left_Stick_X;
    int32_t Left_Stick_Y;
    int32_t Right_Stick_X;
    int32_t Right_Stick_Y;
    int32_t L_Trigger;
    int32_t R_Trigger;    
} ControllerState;

#endif