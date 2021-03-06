#pragma once

#include <array>
#include <cinttypes>

namespace chip8
{
   // Static constants
   constexpr uint16_t MAX_MEMORY = 4096;
   constexpr uint16_t MAX_GFX_MEMORY = 64 * 32;
   constexpr uint16_t CHIP8_MEMORY_START = 0x200;
   constexpr uint16_t CHIP8_MEMORY_END = 0xFFF;
   constexpr uint16_t OPCODE_SIZE = 2;
   constexpr float REFRESH_RATE = 60.0f; // Hz
   constexpr float CPU_SPEED = 540.0f; // Hz

   // Common Typedefs
   using byte_t = unsigned char; // Represents 1 byte of memory
   // Chipset typedefs
   using memory_t = std::array<byte_t, MAX_MEMORY>;         // represents memory structure
   using graphics_t = std::array<byte_t, MAX_GFX_MEMORY>;   // graphics memory structure
   using index_register_t = uint16_t;                       // Index register base type
   using program_counter_t = uint16_t;                      // Base type for program counter must be able to hold 4096 entries
   using stack_ptr_t = uint16_t;                            // Base type for stack pointer

   constexpr byte_t fontset[80] =
   {
       0xF0, 0x90, 0x90, 0x90, 0xF0, //0
       0x20, 0x60, 0x20, 0x20, 0x70, //1
       0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
       0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
       0x90, 0x90, 0xF0, 0x10, 0x10, //4
       0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
       0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
       0xF0, 0x10, 0x20, 0x40, 0x40, //7
       0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
       0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
       0xF0, 0x90, 0xF0, 0x90, 0x90, //A
       0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
       0xF0, 0x80, 0x80, 0x80, 0xF0, //C
       0xE0, 0x90, 0x90, 0x90, 0xE0, //D
       0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
       0xF0, 0x80, 0xF0, 0x80, 0x80  //F
   };
}