#pragma once

#include "opcode_executions.h"
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
   class cpu
   {
   public:
      cpu();
      void load_fontset();
      void load_program(std::filesystem::path path);

      opcode get_next_opcode();
      bool execute_opcode();           // Returns true for redraw

      // Convenience functions for opcode implementation
      void set_program_counter(program_counter_t ctr);
      void increment_program_counter(program_counter_t increment_amount);
      void store_program_counter_in_stack();
      void set_program_counter_from_stack();
      void set_index_register(index_register_t idx_reg);
      index_register_t get_index_register() const;
      byte_t get_register(byte_t index) const;
      void set_register(byte_t index, byte_t value);
      bool is_key_in_register_pressed(byte_t index);
      bool check_for_key_press(byte_t reg_idx);

      byte_t get_value_of_memory_at_location(uint16_t index) const;
      void set_value_of_memory_at_location(uint16_t index, byte_t value);

      byte_t get_value_of_gfx_memory_at_location(uint16_t index) const;
      void set_value_of_gfx_memory_at_location(uint16_t index, byte_t value);

      byte_t get_delay_timer() const;
      void set_delay_timer(byte_t value);
      byte_t get_sound_timer() const;
      void set_sound_timer(byte_t value);

      void update_timers();

      void clear_graphics_memory();
      void clear_memory();
      void clear_registers();
      void clear_keys();

      graphics_t display_data() { return m_gfx_memory; }

   private:
      byte_t               m_registers[16];                         // 15 Registers + 16th for carry flag
      index_register_t     m_idx_register = 0;                      // Index register
      uint16_t             m_stack[16];                             // program stack
      stack_ptr_t          m_stack_ptr = 0;
      program_counter_t    m_program_ctr = CHIP8_MEMORY_START;      // Program counter that can range from 0x000 -> 0xFFF (0-4095)
      byte_t               m_delay_timer = 0;
      byte_t               m_sound_timer = 0;
      memory_t             m_memory;                                // 4k chip memory
      graphics_t           m_gfx_memory;                            // 64*32 gfx memory
      byte_t               m_keys[16];                              // track key presses
   };
}