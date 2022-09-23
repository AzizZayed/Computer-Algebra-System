#!/bin/bash

# This script is used to build the project.

cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build-debug
cmake --build build-debug

cmake -DCMAKE_BUILD_TYPE=Release -S . -B build-release
cmake --build build-release