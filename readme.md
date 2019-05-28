# Kiln
A 2d game engine built on top of SDL2 using C++.

## Broad Overview
### NOTE: This document has not been updated to reflect changes since it was created.
![img](https://i.imgur.com/H0O1yod.png)

## Engine Features
* Asset Manager
  * Load images, music, sound, and fonts.
  * Unloads assets and frees the memory.
  * Assets are loaded into a map and can be fetched with a key supplied when loading.
* Window Manager
  * Contains renderer and window along with associated metadata.
  * Handles updating the window state at runtime.
* Input Manager
  * Detects user input state.
  * All instantiated input components are registered automatically on init behind the scenes.
  * Input states are mapped to input component "action" lamdas.
  * WIP: click and drag, multi-click, and other modified input detection and handling.
* Module System
  * Games are created externally to the engine code using a "KilnModule".
  * KilnModules can stack multiple submodules, useful for opening an in-game menu while keeping the game state active or paused.
* TOML config loader
  * Engine configuration loaded easily using a TOML file.
* ECS
  * An entity-component system for easily creating functionality.
  * Easily bind components with a binding constructor or the "bind" method.
* Custom math library
  * Includes a templated Vector class, interpolation, normalization, and various other operations
  * Still growing as needs arise!
  
## Building
Currently only tested in Linux.
1. Ensure you have SDL2, SDL_image, SDL_ttf, and SDL_mixer. (these libs will be included in the future).
1. Clone and cd into cloned dir, making sure to aquire git submodules.
1. $ cmake .
1. $ make
1. $ ./Kiln
