#!/bin/bash
rm -rf arduino-cmake-tmp
git clone https://github.com/queezythegreat/arduino-cmake.git arduino-cmake-tmp
mv arduino-cmake-tmp/cmake/Platform Platform
mv arduino-cmake-tmp/cmake/ArduinoToolchain.cmake ArduinoToolchain.cmake
rm -rf arduino-cmake-tmp
