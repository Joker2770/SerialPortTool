/*************************************************************************
    > File Name: port_control.h
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Feb 23 19:22:43 2020
 ************************************************************************/

/* 
* MIT License
* 
* Copyright (c) 2020-2023 Joker2770
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
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

// OS Specific sleep
#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#include <string.h>
#endif

#include <string.h>
#include <stdlib.h>

using namespace std;
typedef vector<string> STRVECTOR;
typedef string::size_type STRPOS;

class my_serial_ctrl
{
public:
	my_serial_ctrl();
	my_serial_ctrl(const my_serial_ctrl &msc);
	my_serial_ctrl& operator=(const my_serial_ctrl &msc);
	~my_serial_ctrl();

	void enumerate_ports(void);
	int open_port(void);
	int close_port(void);
	void show_port_set(void);
	int show_port_more_set(void);
	int port_set(const char *sArg1, const char *sArg2);
	int send_data(const char *sData, bool bHex = false);
	int receive_data(uint32_t sData, bool bHex = false);

private:
	serial::Serial *m_serial;
};

int AUX_split_str(string strSrc, STRVECTOR &vecDest, char cSep);
int my_stricmp(const char *, const char *);
//void my_sleep(unsigned long milliseconds);

/*
	comment: HexToAscii, e.g.: 0x12 0xAC 0x0D -> "12AC0D"
	para: 
		pSrc(in): source string. 
		pDest(out): destination string. 
		nlen(in): count of characters of source string that you will deal with. 
	caution: none. 
*/
void HexToAscii(unsigned char *pSrc, unsigned char *pDest, unsigned int nLen);

/*
comment: StringToHex, e.g.: "12AC0D" -> 0x12 0xAC 0x0D
para:
	pSrc(in): source string. 
	pDest(out): destination string. 
	uilen(out): count of characters of destination string. 
return: uilen. 
caution: The source string only '0-9 a-z A-Z' include, that is can not include '~%$#.,/][\*...', etc. inside the source string. 
*/
int StringToHex(char *pSrc, unsigned char *pDest, unsigned int *uilen);

#endif // __PORT_CONTROL_H__
