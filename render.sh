#!/bin/sh
cd build/
make
./softrender
cd ..
feh build/test.ppm
