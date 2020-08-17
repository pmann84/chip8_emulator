#include "keyboard.h"

namespace chip8
{
   keyboard::keyboard()
   {
      clear();
   }

   void keyboard::set(uint8_t key, uint8_t value)
   {
      m_keys[key] = value;
   }

   void keyboard::clear()
   {
      for (uint8_t i = 0; i < 16; i++)
      {
         m_keys[i] = 0;
      }
   }
}