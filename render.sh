#!/bin/sh
cd build/
rm src/softrender
rm test.ppm
make
./src/softrender ../$1 test.ppm 2000 2000
cd ..
feh --force-aliasing build/test.ppm
