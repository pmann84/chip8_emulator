# Chip8 Emulator

## Description
This is a basic Chip8 emulator written in C++ with simple graphical output using SDL.

## Dependencies
* SDL
 - Download the SDL2 development libraries from http://libsdl.org/download-2.0.php and extract them into the `vendor` folder.
* C++

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
