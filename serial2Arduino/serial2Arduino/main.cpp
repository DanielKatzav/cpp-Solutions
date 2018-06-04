#include <iostream>
#include <string>
#include "SerialPort.h"
#include "teraranger_evo.h"
#include <sstream>

using std::cout;
using std::endl;

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM3";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];
char input[MAX_DATA_LENGTH];

int main()
{

	SerialPort arduino(port_name);
	if (arduino.isConnected()) cout << "Connection Established" << endl;
	else cout << "ERROR, check port name\n";

	
	// Convert 1114437 to Hex == 00 11 01 45
	int NumToHex = 97;
	std::stringstream sstream;
	sstream << "0x" << std::hex << NumToHex;
	std::string result(sstream.str());
	char *WriteText = new char[result.length() + 1];
	strcpy(WriteText, result.c_str());

	/*
	int NumToHex = 99;
	std::stringstream sstream;
	sstream << "0x" << std::hex << NumToHex;
	std::string result(sstream.str());
	char *ReadText = new char[result.length() + 1];
	strcpy(ReadText, result.c_str());*/

	//cout << SetText << endl;

	arduino.writeSerialPort(WriteText, 7);
	//arduino.writeSerialPort(ReadText, MAX_DATA_LENGTH);

	while (arduino.isConnected())
	{

		// Check if data has been read or not
		arduino.readSerialPort(incomingData, 7);
		// prints out data
		long bin, dec = 0, rem, num, base = 1;
		num = atoi(incomingData);
		bin = num;
		while (num > 0)
		{
			rem = num % 10;
			dec = dec + rem * base;
			base = base * 2;
			num = num / 10;
		}
		//cout << dec << endl;
		cout << incomingData << endl;

		// Sample Rate
		Sleep(100);
	}
}