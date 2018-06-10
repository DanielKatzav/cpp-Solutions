#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include "SerialPort.h"
#include "teraranger_evo.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>

using std::cout;
using std::endl;

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM12";

// String for incoming data
char ReadFromSensor[7];
char ENABLE_CMD[5] = { (char)0x00, (char)0x52, (char)0x02, (char)0x01, (char)0xDF };
char TEXT_MODE[4] = { (char)0x00, (char)0x11, (char)0x01, (char)0x45 };
char BINARY_MODE[4] = { (char)0x00, (char)0x11, (char)0x02, (char)0x4C };


int main()
{
	char cRFS[7];
	SerialPort arduino(port_name);
	if (arduino.isConnected()) cout << "Connection Established" << endl;
	else cout << "ERROR, check port name\n";


	arduino.writeSerialPort(TEXT_MODE, 4);
	//arduino.writeSerialPort(ENABLE_CMD, 5);
	while (arduino.isConnected())
	{
	// read data
		arduino.readSerialPort(ReadFromSensor, 7);

		std::cout << ReadFromSensor << std::endl;

		Sleep(1000/40);
	// Sample Rate
	
	}


}
