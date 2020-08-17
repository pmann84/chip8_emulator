#pragma once

#include "constants.h"

namespace chip8
{
   class gfx_memory
   {
   public:
      gfx_memory();

      byte_t get(uint16_t index) const;
      void set(uint16_t index, byte_t value);
      void clear();

      const graphics_t& pixels() const;

   private:
      graphics_t m_memory; // 64*32 gfx memory
   };
}