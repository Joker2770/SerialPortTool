# SerialPortTool

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/240f61b50b64431896d1db3ee11c1cb1)](https://app.codacy.com/gh/Joker2770/SerialPortTool?utm_source=github.com&utm_medium=referral&utm_content=Joker2770/SerialPortTool&utm_campaign=Badge_Grade_Settings)
[![serialporttool](https://snapcraft.io/serialporttool/badge.svg)](https://snapcraft.io/serialporttool)

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
