@echo off

IF "%#%" "-eq" "0" (
  SET build_debug=1
  SET build_release=1
) ELSE (
  IF "%~1"=="-d" (
    SET build_debug=1
    SET build_release=0
  ) ELSE IF "%~1"=="-r" (
    SET build_debug=0
    SET build_release=1
  ) ELSE (
    echo "Invalid build type specified. Valid options are '-d' for debug or '-r' for release."
    exit "1"
  )
)

IF "%build_debug%" "-eq" "1" (
  cmake "-DCMAKE_BUILD_TYPE=Debug" "-S" "." "-B" "build-debug"
  cmake "--build" "build-debug"
)
IF "%build_release%" "-eq" "1" (
  cmake "-DCMAKE_BUILD_TYPE=Release" "-S" "." "-B" "build-release"
  cmake "--build" "build-release"
)