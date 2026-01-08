#!/usr/bin/env bash
cp src/glsl/ build/Debug/ -r
mkdir -p build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
