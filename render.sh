#!/bin/sh
cd build/
make
rm test.ppm
./softrender ../teapot.obj test.ppm 2000 2000
cd ..
feh --force-aliasing build/test.ppm
