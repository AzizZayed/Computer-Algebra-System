#!/bin/bash

# This script is used to build the project.

# Check if the user specified a build type
if [ $# -eq 0 ]; then
  # No build type specified, build both debug and release versions
  build_debug=1
  build_release=1
else
  # Build type specified, check if it is -d or -r
  case $1 in
    "-d")
      build_debug=1
      build_release=0
      ;;
    "-r")
      build_debug=0
      build_release=1
      ;;
    *)
      # Invalid build type specified
      echo "Invalid build type specified. Valid options are '-d' for debug or '-r' for release."
      exit 1
      ;;
  esac
fi

# Build the debug version if specified
if [ $build_debug -eq 1 ]; then
  cmake -DCMAKE_BUILD_TYPE=Debug -S . -B builds/debug
  cmake --build builds/debug
fi

# Build the release version if specified
if [ $build_release -eq 1 ]; then
  cmake -DCMAKE_BUILD_TYPE=Release -S . -B builds/release
  cmake --build builds/release
fi