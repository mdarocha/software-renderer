# software-renderer
A toy program which renders 3D models in a similar way to OpenGL, but purely in software.
Inspired by [tinyrender](https://github.com/ssloy/tinyrenderer)
## Getting Started
### Prerequisites
software-renderer uses the SDL2 library for realtime viewing and [Catch2](https://github.com/catchorg/Catch2) for tests.

Install them using your distribution's package manager.

```
$ pacman -S sdl2 catch2 #Arch Linux
```

### Installing
Start by cloning the repo
```
$ git clone https://github.com/mdarocha/software-renderer.git
```
Enter the repository and create a build directory
```
$ cd software-renderer
$ mkdir build
$ cd build/
```
Generate CMake files and compile the program
```
$ cmake ..
$ make
```
You can easily run the program using the render.sh script
```
$ ./render.sh assets/test.obj
```
Make sure you have `feh` or another image viewer to view .ppm images.
## Running the tests
Compile the program, enter the build directory and run `make test`.
## Usage
```
softrender model.obj [output.ppm] [--realtime] [width] [height]
```
You can use the `--realtime` flag to view the model in real time.
```
softrender model.obj --realtime
```
