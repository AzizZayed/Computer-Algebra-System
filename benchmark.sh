#!/bin/bash

# This script is used to benchmark the project.

# Build the project.
./build.sh || exit

# Run the benchmark.
cd build-release/cas/bench || exit
./bench --benchmark_out=../../../cas/bench/history/benchmark-"$(date +'%m-%d-%Y')".json --benchmark_out_format=json
