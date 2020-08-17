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

   bool keyboard::is_pressed(uint8_t key) const
   {
      return get(key) != 0;
   }

   void keyboard::clear()
   {
      for (uint8_t i = 0; i < 16; i++)
      {
         m_keys[i] = 0;
      }
   }

   uint8_t keyboard::get(uint8_t key) const
   {
      return m_keys[key];
   }
}