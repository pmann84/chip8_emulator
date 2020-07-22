#pragma once

#include <cinttypes>

namespace chip8
{
   // Static constants
   constexpr uint16_t MAX_MEMORY = 4096;
   constexpr uint16_t MAX_GFX_MEMORY = 64 * 32;
   constexpr uint16_t CHIP8_MEMORY_START = 0x200;
   constexpr uint16_t CHIP8_MEMORY_END = 0xFFF;
   constexpr uint16_t OPCODE_SIZE = 2;

   // Typedefs
   using byte_t = unsigned char; // Represents 1 byte of memory

   namespace opcode_defs
   {
      constexpr byte_t SPECIAL = 0x0;
      constexpr uint16_t CLS = 0x00e0;
      constexpr uint16_t RTS = 0x00ee;

      constexpr byte_t JUMP = 0x1;

      constexpr byte_t SKIP_NEQ_V = 0x4;

      constexpr byte_t MVI_V = 0x6;
      constexpr byte_t ADD_V = 0x7;

      constexpr byte_t MVI_I = 0xa;
   }

   //// Miscellaneous structures - TODO: decide if these are needed
   //using buffer_t = std::vector<byte_t>; // A buffer of bytes read in from a file
   //using program_t = std::vector<chip8::chip8::opcode_t>; // A program represented by a series of opcodes

}