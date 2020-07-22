#pragma once

#include "constants.h"
#include "opcode.h"

#include <array>
#include <filesystem>

namespace chip8
{
   // Memory structure
   // 0x000 - 0x1FF - Chip 8 interpreter(contains font set in emu)
   // 0x050 - 0x0A0 - Used for the built in 4x5 pixel font set(0 - F)
   // 0x200 - 0xFFF - Program ROM and work RAM
   class chip8
   {
   public:
      // Chipset typedefs
      using memory_t = std::array<byte_t, MAX_MEMORY>;         // represents memory structure
      using graphics_t = std::array<byte_t, MAX_GFX_MEMORY>;   // graphics memory structure
      using index_register_t = uint16_t;                       // Index register base type
      using program_counter_t = uint16_t;                      // Base type for program counter must be able to hold 4096 entries
      using stack_ptr_t = uint16_t;                            // Base type for stack pointer

      chip8();
      void load_program(std::filesystem::path path);
      opcode get_next_opcode();
      bool execute_opcode();           // Returns true for redraw
      void clear_graphics_memory();
      void clear_memory();
      void clear_registers();

   private:
      byte_t               m_registers[16];                         // 15 Registers + 16th for carry flag
      index_register_t     m_idx_register = 0;                      // Index register
      stack_ptr_t          m_stack_ptr = 0xfa0;
      program_counter_t    m_program_ctr = CHIP8_MEMORY_START;      // Program counter that can range from 0x000 -> 0xFFF (0-4095)
      byte_t               m_delay_timer = 0;
      byte_t               m_sound_timer = 0;
      memory_t             m_memory;                                // 4k chip memory
      graphics_t           m_gfx_memory;                            // 64*32 gfx memory
   };
}