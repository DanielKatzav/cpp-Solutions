#include "SerialPort.h"
#include <iostream>


SerialPort::SerialPort(char *portName)
{
	this->connected = false;

	this->handler = CreateFileA(static_cast<LPCSTR>(portName),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (this->handler == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
		}
		else
		{
			printf("ERROR!!!");
		}
	}
	else {
		DCB dcbSerialParameters = { 0 };
		_COMMTIMEOUTS dcsTimeOuts = { 0 };

		if (!GetCommState(this->handler, &dcbSerialParameters)) {
			printf("failed to get current serial parameters");
		}
		else {
			dcbSerialParameters.BaudRate = CBR_115200;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			//dcbSerialParameters.fDtrControl = DTR_CONTROL_DISABLE;
			dcbSerialParameters.fOutxCtsFlow = FALSE;
			dcbSerialParameters.fOutxDsrFlow = FALSE;


			dcsTimeOuts.ReadIntervalTimeout = 1000;

			if (!SetCommState(handler, &dcbSerialParameters))
			{
				printf("ALERT: could not set Serial port parameters\n");
			}
			else {
				this->connected = true;
				PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);

				if (!SetCommTimeouts(handler, &dcsTimeOuts))
				{
					printf("ALERT: could not set Serial port Timeouts\n");
				}
			}
		}
	}
}

SerialPort::~SerialPort()
{
	if (this->connected) {
		this->connected = false;
		CloseHandle(this->handler);
	}
}

int SerialPort::readSerialPort(char *buffer, unsigned int buf_size)
{
	DWORD bytesRead;
	unsigned int toRead;
	
	ClearCommError(this->handler, &this->errors, &this->status);

	if (this->status.cbInQue > 0) {
		if (this->status.cbInQue > buf_size) {
			toRead = buf_size;
		}
		else toRead = this->status.cbInQue;
	}

	if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL))
	{
		return bytesRead;
	}
	return 0;
}

bool SerialPort::writeSerialPort(char *buffer, unsigned int buf_size)
{
	DWORD bytesSend;

	if (!WriteFile(this->handler, buffer, buf_size, &bytesSend, 0))
	{
		std::cout << "Couldn't write to sensor, error code " << GetLastError()<< std::endl;
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else
	{
		return true;
	}
}

bool SerialPort::isConnected()
{
	return this->connected;
}



