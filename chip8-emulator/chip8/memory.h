#pragma once

#include "constants.h"
#include "opcode.h"

#include <filesystem>

namespace chip8
{
   // Memory structure
   // 0x000 - 0x1FF - Chip 8 interpreter(contains font set in emu)
   // 0x050 - 0x0A0 - Used for the built in 4x5 pixel font set(0 - F)
   // 0x200 - 0xFFF - Program ROM and work RAM
   class memory
   {
   public:
      memory();

      opcode read(program_counter_t ctr) const;
      byte_t get(program_counter_t ctr) const;
      void set(program_counter_t ctr, byte_t value);
      void clear();

      bool load_program(std::filesystem::path path);

   private: // Functions
      void load_fontset();

   private: // Members
      memory_t m_memory;  // 4k chip memory
   };
}