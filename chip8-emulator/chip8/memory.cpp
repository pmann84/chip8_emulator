#include "memory.h"

#include <fstream>

namespace chip8
{
   memory::memory()
   {
      clear();
      load_fontset();
   }

   opcode memory::read(program_counter_t ctr) const
   {
      // Gets the next opcode from memory that should be executed
      return opcode(m_memory[ctr], m_memory[ctr + 1]);
   }

   byte_t memory::get(program_counter_t ctr) const
   {
      return m_memory[ctr];
   }

   void memory::set(program_counter_t ctr, byte_t value)
   {
      m_memory[ctr] = value;
   }

   void memory::clear()
   {
      std::fill(std::begin(m_memory), std::end(m_memory), 0);
   }

   bool memory::load_program(std::filesystem::path path)
   {
      if (!std::filesystem::exists(path))
      {
         return false;
      }
      std::basic_ifstream<unsigned char> program(path, std::ios::out | std::ios::binary);
      // Get the file size
      program.seekg(0, program.end);
      auto program_size = program.tellg();
      program.seekg(0, program.beg);
      program.read(&m_memory[CHIP8_MEMORY_START], program_size);
      program.close();
      return true;
   }

   void memory::load_fontset()
   {
      // Load fontset
      for (int i = 0; i < 80; ++i)
      {
         m_memory[i] = fontset[i];
      }
   }
}