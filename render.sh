#!/bin/sh
cd build/
rm softrender
rm test.ppm
make
./src/softrender ../teapot.obj test.ppm 2000 2000
cd ..
feh --force-aliasing build/test.ppm
