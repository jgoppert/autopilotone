#!/bin/bash
rm -rf arduino-cmake-tmp Platform ArduinoToolchain.cmake
git clone https://github.com/jgoppert/arduino-cmake.git arduino-cmake-tmp
mv arduino-cmake-tmp/cmake/Platform Platform
mv arduino-cmake-tmp/cmake/ArduinoToolchain.cmake ArduinoToolchain.cmake
rm -rf arduino-cmake-tmp
