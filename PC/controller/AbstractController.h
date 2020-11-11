/*
 * File:            AbstractController.h
 * Author:          TheRealKasumi
 * Description:     This file provides an abstract class for controller inputs. 
*/

#ifndef AbstractControllerH
#define AbstractControllerH

#include <stdint.h>
#include "ControllerState.h"

class AbstractController
{
protected:
    uint8_t controllerNumber;  
    ControllerState controllerState; 

public:
    virtual bool connect() = 0;
    virtual bool isConnected() = 0;
    virtual DWORD poll() = 0;
    virtual ControllerState getControllerState() = 0;
};

#endif