#include "opcode.h"

chip8::opcode::opcode(chip8::byte_t first, chip8::byte_t last)
{
   m_code = (first << 8) | last;
}

chip8::byte_t chip8::opcode::upper_half_of_first_byte()
{
   return m_code >> 12;
}

chip8::byte_t chip8::opcode::lower_half_of_first_byte()
{
   return (m_code >> 8) & 0x0f;
}

chip8::byte_t chip8::opcode::last_byte()
{
   return m_code & 0x00ff;
}

uint16_t chip8::opcode::get_last_12_bits()
{
   return m_code & 0x0fff;
}

chip8::opcode::opcode_t chip8::opcode::code()
{
   return m_code;
}