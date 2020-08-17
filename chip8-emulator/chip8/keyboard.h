#pragma once

#include "constants.h"

namespace chip8
{
   class keyboard
   {
   public:
      keyboard();

      void set(uint8_t key, uint8_t value);

      void clear();

   private:
      byte_t m_keys[16];
   };
}