/*************************************************************************
    > File Name: main.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Feb 23 9:03:57 2020
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

#include "port_control.h"

void print_usage()
{
	printf("===================command===================\n");
	printf("\tOPEN\n");
	printf("\tCLOSE\n");
	printf("\tSHOWSET\n");
	printf("\tSHOWMORESET\n");
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
	printf("\tSETRTS:<0|1> (e.g.: SETRTS:1)\n");
	printf("\tSETDTR:<0|1>\n");
	printf("\tSETBREAK:<0|1>\n");
	printf("\tWRITE:<DATA>\n");
	printf("\tREAD:<DATALENGTH>\n");
	printf("\tWRITEHEX:<DATA> (e.g.: WRITEHEX:313233)\n");
	printf("\tREADHEX:<DATALENGTH>\n");
	printf("\n[<TIMEOUT>:\n\tinter_byte_timeout, \n\tread_timeout_constant, \n\tread_timeout_multiplier, \n\twrite_timeout_constant, \n\twrite_timeout_multiplier\ne.g.: SETTIMEOUT:10000,1000,0,1000,0\n]\n");
	printf("[<BYTESIZE>(5~8): fivebits = 5, sixbits = 6, sevenbits = 7, eightbits = 8]\n");
	printf("[<PARITY>(0~4): parity_none = 0, parity_odd = 1, parity_even = 2, parity_mark = 3, parity_space = 4]\n");
	printf("[<STOPBITS>(1~3): stopbits_one = 1, stopbits_two = 2, stopbits_one_point_five = 3]\n");
	printf("[<FLOWCONTROL>(0~2): flowcontrol_none = 0, flowcontrol_software = 1, flowcontrol_hardware = 2]\n");
	printf("===================command===================\n");
}

int main(int argc, char *argv[])
{
	my_serial_ctrl *pS = new my_serial_ctrl();

	if (1 < argc)
	{
		if (2 == argc && (0 == my_stricmp(argv[1], "--version") || 0 == my_stricmp(argv[1], "-V")))
		{
			printf("20.22.05\n");
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
		char szCommand[128] = "";
		memset(szCommand, 0, sizeof(szCommand));

		try
		{
#ifdef _MSC_VER
			iret = scanf_s("%s", szCommand, 128);
#else
			iret = scanf("%s", szCommand);
#endif
		}
		catch (exception &e)
		{
			printf("Unhandled Exception: %s\n", e.what());
		}

		STRVECTOR vDest;
		AUX_split_str(string(szCommand), vDest, ':');
		if (1 == vDest.size())
		{
			if (0 == my_stricmp(vDest[0].c_str(), "OPEN"))
				iret = pS->open_port();
			else if (0 == my_stricmp(vDest[0].c_str(), "ClOSE"))
				iret = pS->close_port();
			else if (0 == my_stricmp(vDest[0].c_str(), "SHOWMORESET"))
				pS->show_port_more_set();
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
				printf("Command error!\n");
		}
		else if (2 == vDest.size() && 0 != my_stricmp(vDest[0].c_str(), "") && 0 != my_stricmp(vDest[1].c_str(), ""))
		{
			if ((NULL != strstr(vDest[0].c_str(), "SET")) || (NULL != strstr(vDest[0].c_str(), "set")))
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
				printf("Command error!\n");
		}
		else
			printf("Command error!\n");
	}

	if (NULL != pS)
	{
		delete pS;
		pS = NULL;
	}

	return 0;
}
