# Chip8 Emulator

## Description
This is a basic Chip8 emulator written in C++ with simple graphical output using SDL.

## Dependencies
* SDL
* C++

## Installing dependencies and running the program
You need to download the SDL2 development libraries from [here]http://libsdl.org/download-2.0.php) and extract them into a folder in the root directory called `vendor`.

When you build the chip8 project you must copy the `SDL2.dll` to the build output folder for the program to run.

## Keypad
The keypad maps the hex keypad to modern keyboards as follows

```
    +---+---+---+---+           +---+---+---+---+
    | 1 | 2 | 3 | C |           | 1 | 2 | 3 | 4 |
    +---+---+---+---+           +---+---+---+---+
    | 4 | 5 | 6 | D |           | Q | W | E | R |           
    +---+---+---+---+    ->     +---+---+---+---+
    | 7 | 8 | 9 | E |           | A | S | D | F |
    +---+---+---+---+           +---+---+---+---+
    | A | 0 | B | F |           | Z | X | C | V |
    +---+---+---+---+           +---+---+---+---+
```

## Example Tetris ROM

![alt text](../media/tetris.gif?raw=true)

## ROMs Tested
* Tetris
* Space Invaders
* Chip8 Logo
* Clock
* Lakeidoscope
* Keypad Test Program
* Life 
* Lunar Lander
* Maze
* Tank