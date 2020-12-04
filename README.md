# SerialPortTool
A Cross-platform serial test tool.

## Dependencies
Required:
* [cmake](http://www.cmake.org) - buildsystem
* g++ (>= 7.4.0 recommended)
* gcc (>= 7.4.0 recommended)

## Build on Linux
~~~
git clone https://github.com/Joker2770/SerialPortTool.git
cd SerialPortTool
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
./SerialPortTool
~~~

## Build on windows
~~~
git clone https://github.com/Joker2770/SerialPortTool.git
cd SerialPortTool
git submodule update --init --recursive
~~~
build with cmake-gui.
