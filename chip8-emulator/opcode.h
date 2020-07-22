#pragma once

#include "constants.h"

#include <iostream>
#include <iomanip>

namespace chip8
{
   class opcode
   {
   public:
      using opcode_t = uint16_t; // Opcode - 2 bytes

      opcode(byte_t first, byte_t last);

      // TODO: Useful bit operations
      // Get first bits, get last 8 bits, get last 12 bits
      byte_t upper_half_of_first_byte();
      byte_t lower_half_of_first_byte();
      byte_t last_byte();
      uint16_t get_last_12_bits();

      friend std::ostream& operator<<(std::ostream& out, const opcode& code);

      opcode_t code();

   private:
      opcode_t m_code;
   };

   inline std::ostream& operator<<(std::ostream& out, const opcode& code)
   {
      std::ios_base::fmtflags f(out.flags());
      out << std::hex << std::setw(4) << std::setfill('0') << int(code.m_code);
      out.flags(f);
      return out;
   }
}