/*************************************************************************
    > File Name: port_control.h
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Feb 23 19:22:43 2020
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

#ifndef __PORT_CONTROL_H__
#define __PORT_CONTROL_H__

#include "serial/serial.h"

class my_serial_ctrl {
public:
	my_serial_ctrl();
	~my_serial_ctrl();

	void enumerate_ports();
	int open_port(const char* sPort, unsigned int iBaudrate);
	int close_port();
	void my_sleep(unsigned long milliseconds);

private:
	serial::Serial *my_serial;

};

#endif // __PORT_CONTROL_H__

