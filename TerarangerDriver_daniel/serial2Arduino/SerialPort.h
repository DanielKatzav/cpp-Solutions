#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 50
#define MAX_DATA_LENGTH 127

#include <windows.h>
#include <string>
#include <iostream>

class SerialPort
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	SerialPort(char *portName); // Constructor
	~SerialPort(); // De-structor

	int readSerialPort(char *buffer, unsigned int buf_size);
	bool writeSerialPort(char *buffer, unsigned int buf_size);
	bool isConnected();
};

#endif // SERIALPORT_H