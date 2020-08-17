#include "gfx_memory.h"

namespace chip8
{
   gfx_memory::gfx_memory()
   {
      clear();
   }

   byte_t gfx_memory::get(uint16_t index) const
   {
      return m_memory[index];
   }

   void gfx_memory::set(uint16_t index, byte_t value)
   {
      m_memory[index] = value;
   }

   void gfx_memory::clear()
   {
      std::fill(std::begin(m_memory), std::end(m_memory), 0);
   }

   const graphics_t& gfx_memory::pixels() const
   {
      return m_memory;
   }
}