/*************************************************************************
    > File Name: main.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Feb 23 9:03:57 2020
 ************************************************************************/

#include "port_control.h"

int main(int argc, char *argv[])
{
	enumerate_ports();

	// port, baudrate, timeout in milliseconds
	//serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));

	return 0;
}
