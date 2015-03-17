#!/bin/sh

mkdir -p build
cd build
cmake ../engine/
make

time ./console-app/console -e".c" -e".h" --input-path ../repos/httpd/ --V1 "(?P<v1>.*strcpy.*)"
