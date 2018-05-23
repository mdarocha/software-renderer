#!/bin/sh
cd build/
make
./softrender ../teapot.obj test.ppm 2000 2000
cd ..
feh --force-aliasing build/test.ppm
