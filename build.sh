#!/usr/bin/env bash
mkdir -p build
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
