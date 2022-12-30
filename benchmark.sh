#!/bin/bash

# This script is used to benchmark the project.

# Build the project.
./build.sh || exit

# Run the benchmark.
cd build-release/cas/benchmark || exit
./bench --benchmark_out=../../../cas/benchmark/history/benchmark-"$(date +'%m-%d-%Y')".json --benchmark_out_format=json
