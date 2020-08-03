#include "chip8.h"

#include <fstream>

#include "opcode_executions.h"

namespace chip8
{

   cpu::cpu()
   {
      reload();
   }

   void cpu::load_fontset()
   {
      // Load fontset
      for (int i = 0; i < 80; ++i)
      {
         m_memory[i] = fontset[i];
      }
   }

   bool cpu::load_program(std::filesystem::path path)
   {
      if (!std::filesystem::exists(path))
      {
         return false;
      }
      std::basic_ifstream<unsigned char> program(path, std::ios::out | std::ios::binary);
      // Get the file size
      program.seekg(0, program.end);
      uint16_t program_size = program.tellg();
      program.seekg(0, program.beg);
      program.read(&m_memory[CHIP8_MEMORY_START], program_size);
      program.close();
      return true;
   }

   opcode cpu::get_next_opcode()
   {
      // Gets the next opcode from memory that should be executed
      return opcode(m_memory[m_program_ctr], m_memory[m_program_ctr + 1]);
   }

   bool cpu::execute_opcode()
   {
      // Fetch and decode
      opcode code = get_next_opcode();
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

   void cpu::set_key(uint8_t key, uint8_t value)
   {
      m_keys[key] = value;
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

   byte_t cpu::get_value_of_memory_at_location(uint16_t index) const 
   {
      return m_memory[index];
   }

   void cpu::set_value_of_memory_at_location(uint16_t index, byte_t value)
   {
      m_memory[index] = value;
   }

   byte_t cpu::get_value_of_gfx_memory_at_location(uint16_t index) const
   {
      return m_gfx_memory[index];
   }

   void cpu::set_value_of_gfx_memory_at_location(uint16_t index, byte_t value)
   {
      m_gfx_memory[index] = value;
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

   void cpu::update_timers()
   {
      if (m_delay_timer > 0)
      {
         --m_delay_timer;
      }

      if (m_sound_timer > 0)
      {
         if (m_sound_timer == 1)
         {
            //std::cout << "BEEP!" << std::endl;
         }
         --m_sound_timer;
      }
   }

   void cpu::clear_graphics_memory()
   {
      std::fill(std::begin(m_gfx_memory), std::end(m_gfx_memory), 0);
   }

   void cpu::clear_memory()
   {
      std::fill(std::begin(m_memory), std::end(m_memory), 0);
   }

   void cpu::clear_registers()
   {
      for (uint8_t i = 0; i < 16; i++)
      {
         m_registers[i] = 0;
      }
   }

   void cpu::clear_keys()
   {
      for (uint8_t i = 0; i < 16; i++)
      {
         m_keys[i] = 0;
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

   void cpu::reload()
   {
      clear_graphics_memory();
      clear_memory();
      clear_registers();
      clear_stack();
      clear_keys();
      reset_counters();
      load_fontset();
   }
}