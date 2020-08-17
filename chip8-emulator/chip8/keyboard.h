#pragma once

#include "constants.h"

namespace chip8
{
   class keyboard
   {
   public:
      keyboard();

      void set(uint8_t key, uint8_t value);
      bool is_pressed(uint8_t key) const;
      void clear();

   private:
      uint8_t get(uint8_t key) const;

   private:
      byte_t m_keys[16];
   };
}