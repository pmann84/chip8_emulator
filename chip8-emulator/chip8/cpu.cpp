#include "cpu.h"

#include <fstream>

#include "opcode_executions.h"

namespace chip8
{

   cpu::cpu()
   {
      reload();
   }

   bool cpu::execute_opcode(const opcode& code)
   {
      return chip_table[code.upper_half_of_first_byte()](code, *this);
   }

   void cpu::set_program_counter(program_counter_t ctr)
   {
      m_program_ctr = ctr;
   }

   void cpu::increment_program_counter(program_counter_t increment_amount)
   {
      m_program_ctr += increment_amount;
   }

   void cpu::store_program_counter_in_stack()
   {
      m_stack[m_stack_ptr++] = m_program_ctr;
   }

   void cpu::set_program_counter_from_stack()
   {
      --m_stack_ptr;
      m_program_ctr = m_stack[m_stack_ptr];
   }

   void cpu::set_index_register(index_register_t idx_reg)
   {
      m_idx_register = idx_reg;
   }

   index_register_t cpu::get_index_register() const
   {
      return m_idx_register;
   }

   byte_t cpu::get_register(byte_t index) const
   {
      return m_registers[index];
   }

   void cpu::set_register(byte_t index, byte_t value)
   {
      m_registers[index] = value;
   }

   bool cpu::is_key_in_register_pressed(byte_t index)
   {
      return  m_keys[m_registers[index]] != 0;
   }

   bool cpu::check_for_key_press(byte_t reg_idx)
   {
      bool key_pressed = false;
      for (int i = 0; i < 16; ++i)
      {
         if (m_keys[i] != 0)
         {
            m_registers[reg_idx] = i;
            key_pressed = true;
         }
      }
      return key_pressed;
   }

   byte_t cpu::get_delay_timer() const
   {
      return m_delay_timer;
   }

   void cpu::set_delay_timer(byte_t value)
   {
      m_delay_timer = value;
   }

   byte_t cpu::get_sound_timer() const
   {
      return m_sound_timer;
   }

   void cpu::set_sound_timer(byte_t value)
   {
      m_sound_timer = value;
   }

   void cpu::cycle_delay_timer()
   {
      if (m_delay_timer > 0)
      {
         --m_delay_timer;
      }
   }

   void cpu::cycle_sound_timer()
   {
      if (m_sound_timer > 0)
      {
         if (m_sound_timer == 1)
         {
            //std::cout << "BEEP!" << std::endl;
         }
         --m_sound_timer;
      }
   }

   void cpu::clear()
   {
      clear_registers();
      clear_stack();
      reset_counters();
   }

   void cpu::clear_registers()
   {
      for (uint8_t i = 0; i < 16; i++)
      {
         m_registers[i] = 0;
      }
   }

   void cpu::clear_stack()
   {
      for (uint8_t i = 0; i < 16; i++)
      {
         m_stack[i] = 0;
      }
   }

   void cpu::reset_counters()
   {
      m_idx_register = 0;
      m_stack_ptr = 0;
      m_program_ctr = CHIP8_MEMORY_START;
      m_delay_timer = 0;
      m_sound_timer = 0;
   }
}