/*************************************************************************
    > File Name: main.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Feb 23 9:03:57 2020
 ************************************************************************/

/* 
* MIT License
* 
* Copyright (c) 2020 Joker2770
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

#include "port_control.h"

void print_usage()
{
	printf("===================command===================\n");
	printf("\tOPEN\n");
	printf("\tCLOSE\n");
	printf("\tSHOWSET\n");
	printf("\tSHOWPORT\n");
	printf("\texit\n");
	printf("\tquit\n");
	printf("\tq\n");
	printf("\tSETPORT:<PORT>\n");
	printf("\tSETBAUDRATE:<BAUDRATE>\n");
	printf("\tSETTIMEOUT:<TIMEOUT>\n");
	printf("\tSETBYTESIZE:<BYTESIZE>\n");
	printf("\tSETPARITY:<PARITY>\n");
	printf("\tSETSTOPBITS:<STOPBITS>\n");
	printf("\tSETFLOWCONTROL:<FLOWCONTROL>\n");
	printf("\tWRITE:<DATA>\n");
	printf("\tREAD:<DATALENGTH>\n");
	printf("\tWRITEHEX:<DATA>\n");
	printf("\tREADHEX:<DATALENGTH>\n");
	printf("\tSETRTS:<0|1>\n");
	printf("\tSETDTR:<0|1>\n");
	printf("\tSETCD:<0|1>\n");
	printf("\n(TIMEOUT:\n\tinter_byte_timeout, \n\tread_timeout_constant, \n\tread_timeout_multiplier, \n\twrite_timeout_constant, \n\twrite_timeout_multiplier\n)\n");
	printf("(parity_none = 0, parity_odd = 1, parity_even = 2, parity_mark = 3, parity_space = 4)\n");
	printf("(flowcontrol_none = 0, flowcontrol_software = 1, flowcontrol_hardware = 2)\n");
	printf("===================command===================\n");
}

int main(int argc, char *argv[])
{
	my_serial_ctrl *pS = new my_serial_ctrl();

	if (1 < argc)
	{
		if (2 == argc && 0 == my_stricmp(argv[1], "--version"))
		{
			printf("20.20.02\n");
			return 0;
		}
		else
			print_usage();
	}
	else
	{
		pS->enumerate_ports();
		pS->show_port_set();
		printf("You can type 'HELP' to show usable commands!\n");
	}


	int iret = 0;
	while (true)
	{
		printf(">>");
		char szCommend[128] = "";
		memset(szCommend, 0, sizeof(szCommend));

		try
		{
			#if defined(_WIN32) && !defined(__MINGW32__)
				iret = scanf_s("%s", szCommend, 128);
			#else
				iret = scanf("%s", szCommend);
			#endif
		}
		catch (exception &e) {
			printf("Unhandled Exception: %s\n", e.what());
		}

		STRVECTOR vDest;
		AUX_split_str(string(szCommend), vDest, ':');
		if (1 == vDest.size())
		{
			if (0 == my_stricmp(vDest[0].c_str(), "OPEN"))
				iret = pS->open_port();
			else if (0 == my_stricmp(vDest[0].c_str(), "ClOSE"))
				iret = pS->close_port();
			else if (0 == my_stricmp(vDest[0].c_str(), "SHOWSET"))
				pS->show_port_set();
			else if (0 == my_stricmp(vDest[0].c_str(), "SHOWPORT"))
				pS->enumerate_ports();
			else if (0 == my_stricmp(vDest[0].c_str(), "HELP"))
				print_usage();
			else if (0 == my_stricmp(vDest[0].c_str(), "exit") || 0 == my_stricmp(vDest[0].c_str(), "q") || 0 == my_stricmp(vDest[0].c_str(), "quit"))
				break;
			else if (0 == my_stricmp(vDest[0].c_str(), "SETTIMEOUT"))
			{
				printf("e.g.: SETTIMEOUT:10000,250,0,250,0\n");
				continue;
			}
			else
			{
				printf("Command error!");
				printf("\n");
			}
		}
		else if (2 == vDest.size() && 0 != my_stricmp(vDest[0].c_str(), "") && 0 != my_stricmp(vDest[1].c_str(), ""))
		{
			if ((nullptr != strstr(vDest[0].c_str(), "SET")) || (nullptr != strstr(vDest[0].c_str(), "set")))
				iret = pS->port_set(vDest[0].c_str(), vDest[1].c_str());
			else if (0 == my_stricmp(vDest[0].c_str(), "WRITE"))
				iret = pS->send_data(vDest[1].c_str());
			else if (0 == my_stricmp(vDest[0].c_str(), "READ"))
				iret = pS->receive_data(atol(vDest[1].c_str()));
			else if (0 == my_stricmp(vDest[0].c_str(), "WRITEHEX"))
				iret = pS->send_data(vDest[1].c_str(), true);
			else if (0 == my_stricmp(vDest[0].c_str(), "READHEX"))
				iret = pS->receive_data(atol(vDest[1].c_str()), true);
			else
			{
				printf("Command error!");
				printf("\n");
			}
		}
		else
		{
			printf("Command error!");
			printf("\n");
		}

	}

	if (nullptr != pS) delete pS;

	return 0;
}
