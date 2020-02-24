/************************************************************************
    > File Name: port_control.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Feb 23 19:22:50 2020
 ************************************************************************/

/* 
* MIT License
* 
* Copyright (c) 2020 Joker2770
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and assvciated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/


#include "port_control.h"

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using std::vector;
using std::exception;

my_serial_ctrl::my_serial_ctrl()
{
	this->my_serial = new serial::Serial();
}

my_serial_ctrl::~my_serial_ctrl()
{
	if (nullptr != this->my_serial) delete this->my_serial;
}

void my_serial_ctrl::my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds); // 100 ms
#else
	usleep(milliseconds * 1000); // 100 ms
#endif
}


void my_serial_ctrl::enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	int i = 0;
	while (iter != devices_found.end())
	{
		serial::PortInfo device = *iter++;
		i++; 
		printf("%d. Port - <%s>\n\tDescription: %s\n\tHardware_id: %s\n\n", i, device.port.c_str(), device.description.c_str(), device.hardware_id.c_str());
	}
}

int my_serial_ctrl::open_port(const char* cszPort, unsigned int iBaud)
{
	this->my_serial->setPort(cszPort);
	this->my_serial->setBaudrate(iBaud);
	if (!my_serial->isOpen())
	{
		printf("[%s] is not open!\n", cszPort);

		try {
			this->my_serial->open();
			printf("Open ...\n");
		}
		catch (exception &e) {
			printf("Unhandled Exception: %s\n", e.what());
		}

		if (!this->my_serial->isOpen())
		{
			printf("[%s] open failed!\n", cszPort);
			return -1;
		}
	}
	printf("[%s] open succeed!\n", cszPort);
	return 0;
}

int my_serial_ctrl::close_port()
{
	if (this->my_serial->isOpen())
	{
		printf("Port is open!\n");

		try {
			this->my_serial->close();
			printf("Close ...\n");
		}
		catch (exception &e) {
			printf("Unhandled Exception: %s\n", e.what());
		}

		if (this->my_serial->isOpen())
		{
			printf("Close port failed!\n");
			return -1;
		}
	}
	printf("Close port succeed!\n");
	return 0;
}

