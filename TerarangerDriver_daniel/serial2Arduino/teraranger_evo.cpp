#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teraranger_evo.h"
#include "SerialPort.h"


teraranger::TerarangerEvo::TerarangerEvo()
{
}

teraranger::TerarangerEvo::~TerarangerEvo()
{
}

void teraranger::TerarangerEvo::serialDataCallback(uint8_t data)
{
}

bool teraranger::TerarangerEvo::loadParameters()
{
	return false;
}

void teraranger::TerarangerEvo::setMode(const char *c, int length)
{
	if (!serial_port_.write((uint8_t*)c, length))
	{
		cout << "Timeout or error while writing serial\n";
	}
	serial_port_.flushOutput();
}