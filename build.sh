#!/bin/bash

BUILD_TITLE="Epizeuxis"
BUILD_DIR="build"

echo -e "\033[1;36m$BUILD_TITLE\033[0m"

if [[ "$*" == *"--windows"* ]]; then
  echo -e "\033[1;35mOperating system: Windows (MinGW)\033[0m"
  BUILD_FOR_WINDOWS="ON"
else
  echo -e "\033[1;35mOperating system: *NIX\033[0m"
  BUILD_FOR_WINDOWS="OFF"
fi

if [[ "$*" == *"--release"* ]]; then
  BUILD_TYPE="Release"
  echo -e "\033[1;32mBuild mode: Release\033[0m"
else
  BUILD_TYPE="Debug"
  echo -e "\033[1;34mBuilding mode: Debug\033[0m"
fi

mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DBUILD_FOR_WINDOWS=$BUILD_FOR_WINDOWS
cmake --build .
