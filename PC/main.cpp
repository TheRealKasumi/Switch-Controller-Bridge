/*
 * File:            main.cpp
 * Author:          TheRealKasumi
 * Description:     This programm reads the input of an controller and sends the controller state to an microcontroller via serial port. 
                    The microcontroller then again emulates an controller so that you can loop the inputs through your computer. 
                    This allows you to monitor the controller inputs on your pc and use them for example as overlay when you are streaming.
*/

#include <iostream>
#include <string>
#include <chrono>

#include "controller/XInputController.h"
#include "communication/ArduinoConnection.h"

using namespace std;

void printWelcome();
string askSerialPort();
int askControllerNumber();
bool checkAck(ArduinoConnection *connection);
COORD GetConsoleCursorPosition(HANDLE consoleHandle);
void SetConsoleCursorPosition(HANDLE consoleHandle, int x, int y);

int main(int argc, char *args[])
{
	printWelcome();
	string port = askSerialPort();
	int controllerNumber = askControllerNumber();

reset:
	ArduinoConnection connection(port.c_str(), 230400);
	XInputController controller(controllerNumber);

	if(controller.isConnected())
	{
		cout << "Connection successfull. Transfering data. Press CTRL+C to stop." << endl;
	}
	else
	{
		cout << "Serial connection failed." << endl;
		fflush(stdin);
		cin.get();
		return 1;
	}

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int cursorRow = GetConsoleCursorPosition(consoleHandle).Y;

	int i = 0;
	while(true)
	{
		controller.poll();
		ControllerState state = controller.getControllerState();
		connection.sendControllerState(state);

		if(i++ % 10 == 0)
		{
			SetConsoleCursorPosition(consoleHandle, 0, cursorRow);
			state.print();
		}

		if(!checkAck(&connection))
		{
			cout << "Data not acknowledged, assuming connection loss. Reconnect..." << endl;
			goto reset;
		}
	}
}

void printWelcome()
{
	cout << "Controller Bridge by TheRealKasumi." << endl;
}

string askSerialPort()
{
	cout << "Please enter the serial port, of your Arduino: ";

	int port = -1;
	while(port < 0)
	{
		fflush(stdin);
		cin >> port;
		if(port < 0)
		{
			cout << "The port is invalid." << endl;
			cin.clear();
		}
	}


	return string("\\\\.\\COM") + to_string(port);
}

int askControllerNumber()
{
	cout << "Please enter controller number (1-4): ";

	int number = 0;
	while(number < 1)
	{
		fflush(stdin);
		cin >> number;
		if(number < 1)
		{
			cout << "The controller number is invalid." << endl;
			cin.clear();
		}
	}


	return number - 1;
}

COORD GetConsoleCursorPosition(HANDLE consoleHandle)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if(GetConsoleScreenBufferInfo(consoleHandle, &cbsi))
    {
		return cbsi.dwCursorPosition;
    }
    else
	{
		COORD invalid = { 0, 0 };
		return invalid;
    }
}

void SetConsoleCursorPosition(HANDLE consoleHandle, int x, int y)
{
    COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(consoleHandle, coord);
}

bool checkAck(ArduinoConnection *connection)
{
	char data = 0;
	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	while(!connection->read(&data, sizeof(data)) && chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < 100)
	{
		Sleep(1);	//Remove this for higher speeds, but it will pin 1 CPU to 100% laod
	}
	return data == 1;
}