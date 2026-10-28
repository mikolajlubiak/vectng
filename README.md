# VectNG
## 2D platformer engine prototype in C++20 with SDL2

An SDL2 side-scroller built on an entity-component architecture: entities hold transform, sprite, collider, gravity, keyboard, scroll and tile components, and the game loop runs a fixed-timestep update at 100 Hz, independent of rendering. It loads tile maps from a sprite sheet, plays named idle/walk/jump animations parsed from a texture atlas, caches textures, and draws in layers (map, players, enemies) with a horizontally scrolling camera.

Art is Kenney's [Platformer Art Deluxe](https://kenney.nl/) (CC0).

# Requirements:
* CMake and a C++20 compiler
* SDL2 and SDL2\_image development packages
# Install:
* Arch:
	`pacman -S cmake sdl2 sdl2_image`
* Debian, Ubuntu:
	`apt install cmake pkg-config libsdl2-dev libsdl2-image-dev`
* Fedora:
	`dnf install cmake SDL2-devel SDL2_image-devel`
* Windows:
https://www.matsson.com/prog/sdl2-mingw-w64-tutorial

# Compiling:
* `mkdir build`
* `cd build`
* `cmake ..`
* `cmake --build .`
* `ctest` runs the unit tests

# Controls:
* `A` / `D`: walk left / right
* `Space`: jump
* `Esc`: quit
