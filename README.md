# A-star-Pathfinding
![A* Pathfinding GIF](preview/Pathfinding.gif)

This demo shows how the A* Pathfinding Algorithm can be used for finding the sub-optimal path from one point to another. You can also toggle some settings for viewing experience.

# Controls
* RSHIFT - Frame rate limiter. Due to how I coded it, you can only cap the frame rate lower than your monitor's refresh rate.
* TAB - Current FPS.
* LCLICK - Add walls.
* RCLICK - Erase walls.


# Compiling on Linux
## Requirements
This project uses CMake in order to generate a make file. Install CMake through whatever means necessary, though the easiest would be using `sudo apt-get install cmake` on the command line. 

## Compiling
To compile this project simply run `installDependencies.bash` to download the required dependencies then `compile.bash` to compile an executable into `executable/`. It's as easy as that! 

NOTE: Even if you have SDL installed on your system via `sudo apt-get install libsdl2-2.0`, you still have to run `installSDL.bash` as this project installs SDL only in its root directory, not the system. 

# Compiling on Windows
## Requirements
Installing prerequisites on Windows is a bit more complicated. First, download the binary executable of [CMake](https://cmake.org/) and install it. Be sure to install the executable that matches your system architecture.

After that, create a folder named `Dependencies`. In that folder, create a folder titles `SDL_FULL` and put two folders named `include` and `x86` inside it; Here is where you put the header files of SDL2, SDL2_image, and SDL_tff in `include` and their x86 .lib files into `x86`. If you plan on using Visual Studio for this, you can follow these steps:
* Get the SDL2.zip archive from [here](https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip)
* Get the SDL2_image.zip archive from [here](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip)
* Get the SDL2_ttf.zip archive from [here](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip)
* For each archive, unzip the contents of their `include` folder into `Dependencies/SDL_FULL/include` and `lib/x86` folder into `SDL_FULL/x86`
* Move all the .dll files into a separate folder at the root of the project; This is where your executable will run. 

This project also requires the use of just one open-source library, [Tessil/hopscotch-map](https://github.com/Tessil/hopscotch-map). Clone / download the source code of [Tessil/hopscotch-map](https://github.com/Tessil/hopscotch-map) and rename the folder for the project as `hopscotch-map` and put it in `Dependencies/`. After that, you're all set!

## Compiling
To compile this project, you need to use CMake and your prefered compiler to generate a x86 version of your solution / executable. In some compilers and IDE's more work is needed, such as in Visual Studio where you have to manually specify the library path of SDL as being `SDL_FULL/x86` with an architecture of `Win32`.

After this, the compiled executable must be put into ANY folder in the root directory of the project along with the aforementioned .dll files of SDL2. After this, you can run the game :)
