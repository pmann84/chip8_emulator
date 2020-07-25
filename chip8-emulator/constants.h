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

   namespace opcode_defs
   {
      constexpr byte_t SPECIAL = 0x0;
      constexpr uint16_t CLS = 0x00e0;
      constexpr uint16_t RTS = 0x00ee;

      constexpr byte_t JUMP = 0x1;
      constexpr byte_t CALL = 0x2;
      constexpr byte_t SKIP_EQ = 0x3;
      constexpr byte_t SKIP_NEQ = 0x4;
      constexpr byte_t SKIP_EQ_V = 0x5;

      constexpr byte_t MVI_V = 0x6;
      constexpr byte_t ADD_V = 0x7;

      constexpr byte_t COMP = 0x8;
      namespace comp
      {
         constexpr byte_t MOV_V = 0x00;
         constexpr byte_t OR_V = 0x01;
         constexpr byte_t AND_V = 0x02;
         constexpr byte_t XOR_V = 0x03;
         constexpr byte_t ADD_C_V = 0x04;
         constexpr byte_t SUB_C_V = 0x05;
         constexpr byte_t SHR_C_V = 0x06;
         constexpr byte_t SUBB_C_V = 0x07;
         constexpr byte_t SHL_C_V = 0x0e;
      }
      constexpr byte_t SKIP_NEQ_V = 0x9;
      constexpr byte_t MVI_I = 0xa;
      constexpr byte_t SPRITE_V = 0xd;
      constexpr byte_t MISC = 0xf;
      namespace misc
      {
         constexpr byte_t MOV_V_DELAY = 0x07;
         constexpr byte_t WAITKEY_V = 0x0a;
         constexpr byte_t MOV_DELAY_V = 0x15;
         constexpr byte_t MOV_SOUND_V = 0x18;
         constexpr byte_t ADD_I_V = 0x1e;
         constexpr byte_t SPRITECHAR_V = 0x29;
         constexpr byte_t MOVBCD_V = 0x33;
         constexpr byte_t MOVM_I = 0x55;
         constexpr byte_t MOVM = 0x65;
      }
   }

   //// Miscellaneous structures - TODO: decide if these are needed
   //using buffer_t = std::vector<byte_t>; // A buffer of bytes read in from a file
   //using program_t = std::vector<chip8::chip8::opcode_t>; // A program represented by a series of opcodes

}