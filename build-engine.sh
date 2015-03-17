#!/bin/sh

mkdir -p build
cd build
cmake ../
make

time ./console-app/console -e".c" -e".h" --input-path ../repos/ --V1 "(?P<v1>.*strcpy.*)"
cd ../server
python2 server.py
