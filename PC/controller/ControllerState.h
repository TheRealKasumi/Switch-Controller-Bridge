/*
 * File:            ControllerState.h
 * Author:          TheRealKasumi
 * Description:     This file provides a class that holds the current state of the controller.
*/

#ifndef ControllerStateH
#define ControllerStateH

#include <stdint.h>
#include <iostream>
#include <iomanip>

class ControllerState
{
public:
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
	long cycleTime;

    ControllerState()
    {
        A_Button = 0;
        B_Button = 0;
        X_Button = 0;
        Y_Button = 0;
        L_Button = 0;
        R_Button = 0;
        Plus_Button = 0;
        Minus_Button = 0;
        Home_Button = 0;
        D_Up = 0;
        D_Right = 0;
        D_Down = 0;
        D_Left = 0;
        Left_Stick_Button = 0;
        Right_Stick_Button = 0;
        Left_Stick_X = 0;
        Left_Stick_Y = 0;
        Right_Stick_X = 0;
        Right_Stick_Y = 0;
        L_Trigger = 0;
		R_Trigger = 0;
    }

    void print()
    {
        std::cout << "A:" << A_Button << std::endl;
        std::cout << "B:" << B_Button << std::endl;
        std::cout << "X:" << X_Button << std::endl;
        std::cout << "Y:" << Y_Button << std::endl;
        std::cout << "Up:" << D_Up << std::endl;
        std::cout << "Down:" << D_Down << std::endl;
        std::cout << "Left:" << D_Left << std::endl;
        std::cout << "Right:" << D_Right << std::endl;
        std::cout << "LB:" << L_Button << std::endl;
        std::cout << "RB:" << R_Button << std::endl;
        std::cout << "LT:" << L_Trigger << "          " << std::endl;
        std::cout << "RT:" << R_Trigger << "          " << std::endl;
        std::cout << "Start:" << Plus_Button << std::endl;
        std::cout << "Back:" << Minus_Button << std::endl;
        std::cout << "LSB:" << Left_Stick_Button << std::endl;
        std::cout << "RSB:" << Right_Stick_Button << std::endl;
        std::cout << "LX:" << Left_Stick_X << "          " << std::endl;
        std::cout << "LY:" << Left_Stick_Y << "          " << std::endl;
        std::cout << "RX:" << Right_Stick_X << "          " << std::endl;
		std::cout << "RY:" << Right_Stick_Y << "          " << std::endl;

		if(cycleTime == 0)
			cycleTime = 1;
		int pollRate = 1000000 / cycleTime;
		std::cout << "Rate:" << pollRate << "/s          " << std::endl;
    }    
} ;

#endif