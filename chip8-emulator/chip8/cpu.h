#pragma once

#include "opcode_executions.h"
#include "constants.h"
#include "opcode.h"
#include "clock.h"

#include <array>

namespace chip8
{
   class cpu
   {
   public:
      cpu();
      bool execute_opcode(const opcode& code); // Returns true for redraw

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

      byte_t get_delay_timer() const;
      void set_delay_timer(byte_t value);
      byte_t get_sound_timer() const;
      void set_sound_timer(byte_t value);

      void cycle_delay_timer();
      void cycle_sound_timer();

      void clear_registers();
      void clear_stack();
      void reset_counters();

      void reload();

   private:
      byte_t               m_registers[16];                         // 15 Registers + 16th for carry flag
      index_register_t     m_idx_register = 0;                      // Index register
      uint16_t             m_stack[16];                             // program stack
      stack_ptr_t          m_stack_ptr = 0;
      program_counter_t    m_program_ctr = CHIP8_MEMORY_START;      // Program counter that can range from 0x000 -> 0xFFF (0-4095)
      byte_t               m_delay_timer = 0;
      byte_t               m_sound_timer = 0;
   };
}