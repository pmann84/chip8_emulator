#include "opcode.h"

namespace chip8
{
   opcode::opcode(chip8::byte_t first, chip8::byte_t last)
   {
      m_code = (first << 8) | last;
   }

   byte_t opcode::upper_half_of_first_byte() const
   {
      return m_code >> 12;
   }

   byte_t opcode::lower_half_of_first_byte() const
   {
      return (m_code >> 8) & 0x0f;
   }

   byte_t opcode::upper_half_of_last_byte() const
   {
      return last_byte() >> 4;
   }

   byte_t opcode::lower_half_of_last_byte() const
   {
      return last_byte() & 0x0f;
   }

   byte_t opcode::last_byte() const
   {
      return m_code & 0x00ff;
   }

   uint16_t opcode::get_last_12_bits() const
   {
      return m_code & 0x0fff;
   }

   opcode::opcode_t opcode::code() const
   {
      return m_code;
   }
}