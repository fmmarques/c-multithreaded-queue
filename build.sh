#!/usr/bin/env bash

mkdir -p build
cd build

if [[ "$#" -gt "1" ]]; then 
  cmake .. -DCMAKE_BUILD_TYPE=$1 && make $2
else 
  cmake .. -DCMAKE_BUILD_TYPE=Release && make
fi;
cd -
echo -e "\n\nSee build/"
