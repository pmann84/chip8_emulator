#include "chip8.h"

#include <fstream>

chip8::chip8::chip8()
{
   clear_graphics_memory();
   clear_memory();
   clear_registers();
   // TODO: Load fontset into memory
}

void chip8::chip8::load_program(std::filesystem::path path)
{
   std::basic_ifstream<unsigned char> program(path, std::ios::out | std::ios::binary);
   // Get the file size
   program.seekg(0, program.end);
   uint16_t program_size = program.tellg();
   program.seekg(0, program.beg);
   program.read(&m_memory[CHIP8_MEMORY_START], program_size);
   program.close();
   std::cout << "Program Loaded. Size: " << program_size << "b" << std::endl;
}

chip8::opcode chip8::chip8::get_next_opcode()
{
   // Gets the next opcode from memory that should be executed
   return opcode(m_memory[m_program_ctr], m_memory[m_program_ctr + 1]);
}

bool chip8::chip8::execute_opcode()
{
   // Fetch and decode
   opcode code = get_next_opcode();
   // TODO: Execute - including setting program counter correctly
   switch (code.upper_half_of_first_byte())
   {
      case opcode_defs::SPECIAL:
      {
         switch (code.code())
         {
         case opcode_defs::CLS:
            clear_graphics_memory();
            m_program_ctr += 2;
            return true;
         case opcode_defs::RTS:
            return false;
         default:
            return false; // Code not needed
         }
      }
      case opcode_defs::JUMP:
      {
         program_counter_t addr = code.get_last_12_bits();
         m_program_ctr = addr;
         return false;
      }
      case opcode_defs::SKIP_NEQ_V:
      {
         auto reg = code.lower_half_of_first_byte();
         auto value = code.last_byte();
         m_program_ctr += m_registers[reg] != value ? 4 : 2;
         return false;
      }
      case opcode_defs::MVI_V:
      {
         auto reg = code.lower_half_of_first_byte();
         auto value = code.last_byte();
         m_registers[reg] = value;
         m_program_ctr += 2;
         return false;
      }
      case opcode_defs::ADD_V:
      {
         auto reg = code.lower_half_of_first_byte();
         auto value = code.last_byte();
         auto& rregister = m_registers[reg];
         rregister += value;
         m_program_ctr += 2;
         return false;
      }
      case opcode_defs::MVI_I:
      {
         m_idx_register = code.get_last_12_bits();
         m_program_ctr += 2;
         return true;
      }
      default:
      {
         std::cout << "Opcode " << code << " not supported!" << std::endl;
         return false;
      }
   }


   //case 0x00:
      //   {
      //      switch (instruction)
      //      {
      //      case 0x00E0:
      //         std::cout << "CLS" << std::endl;
      //         break;
      //      case 0x00EE:
      //         std::cout << "RTS" << std::endl;
      //         break;
      //      default:
      //         std::cout << "Not needed." << std::endl;
      //         break;
      //      }
      //      break;
      //   }
      //   case 0x02:
      //   {
      //      uint16_t addr = instruction & 0x0fff;
      //      std::cout << "CALL ";
      //      output_hex(addr, 3);
      //      std::cout << std::endl;
      //      break;
      //   }
      //   case 0x03:
      //   {
      //      uint8_t reg = first & 0x0f;
      //      std::cout << "SKIP.EQ V";
      //      output_hex(reg, 1);
      //      std::cout << ",";
      //      output_hex(last);
      //      std::cout << std::endl;
      //      break;
      //   }

      //   case 0x05:
      //   {
      //      uint8_t first_reg = first & 0x0f;
      //      uint8_t last_reg = last >> 4;
      //      std::cout << "SKIP.EQ V";
      //      output_hex(first_reg, 1);
      //      std::cout << ",V";
      //      output_hex(last_reg, 1);
      //      std::cout << std::endl;
      //      break;
      //   }
      //   case 0x08:
      //   {
      //      // Get the last bit to get the operation
      //      uint8_t final_bit_of_last = last & 0x0f;
      //      // get registers
      //      uint8_t first_reg = first & 0x0f;
      //      uint8_t last_reg = last >> 4;
      //      switch (final_bit_of_last)
      //      {
      //      case 0x00:
      //         std::cout << "MOV V";
      //         break;
      //      case 0x01:
      //         std::cout << "OR V";
      //         break;
      //      case 0x02:
      //         std::cout << "AND V";
      //         break;
      //      case 0x03:
      //         std::cout << "XOR V";
      //         break;
      //      case 0x04:
      //         std::cout << "ADD. V";
      //         break;
      //      case 0x05:
      //         std::cout << "SUB. V";
      //         break;
      //      case 0x06:
      //         std::cout << "SHR. V";
      //         break;
      //      case 0x07:
      //         std::cout << "SUBB. V";
      //         break;
      //      case 0x0E:
      //         std::cout << "SHL. V";
      //         break;
      //      default:
      //         std::cout << "Not supported!" << std::endl;
      //         break;
      //      }
      //      output_hex(first_reg, 1);
      //      std::cout << ",V";
      //      output_hex(last_reg, 1);
      //      std::cout << std::endl;
      //      break;
      //   }
      //   case 0x09:
      //   {
      //      uint8_t first_reg = first & 0x0f;
      //      uint8_t last_reg = last >> 4;
      //      std::cout << "SKIP.NEQ V";
      //      output_hex(first_reg, 1);
      //      std::cout << ",V";
      //      output_hex(last_reg, 1);
      //      std::cout << std::endl;
      //      break;
      //   }
 
      //   case 0x0b:
      //   {
      //      uint16_t addr = instruction & 0x0fff;
      //      std::cout << "JUMP ";
      //      output_hex(addr, 3);
      //      std::cout << "(V0)" << std::endl;
      //      break;
      //   }
      //   case 0x0c:
      //   {
      //      uint8_t reg = first & 0x0f;
      //      std::cout << "RAND V";
      //      output_hex(reg, 1);
      //      std::cout << ",";
      //      output_hex(last);
      //      std::cout << std::endl;
      //      break;
      //   }
      //   case 0x0d:
      //   {
      //      uint8_t first_reg = first & 0x0f;
      //      uint8_t last_reg = last >> 4;
      //      uint8_t height= last & 0x0f;
      //      std::cout << "SPRITE V";
      //      output_hex(first_reg, 1);
      //      std::cout << ",V";
      //      output_hex(last_reg, 1);
      //      std::cout << ", ";
      //      output_hex(height, 1);
      //      std::cout << std::endl;
      //      break;
      //   }
      //   case 0x0e:
      //   {
      //      uint8_t reg = first & 0x0f;
      //      switch (last)
      //      {
      //         case 0x9e:
      //         {
      //            std::cout << "SKIP.KEY V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0xa1:
      //         {
      //            std::cout << "SKIP.NOKEY V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //      }
      //      std::cout << std::endl;
      //      break;
      //   }
      //   case 0x0f:
      //   {
      //      uint8_t reg = first & 0x0f;
      //      switch (last)
      //      {
      //         case 0x07:
      //         {
      //            std::cout << "MOV V";
      //            output_hex(reg, 1);
      //            std::cout << ", DELAY";
      //            break;
      //         }
      //         case 0x0a:
      //         {
      //            std::cout << "WAITKEY V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x15:
      //         {
      //            std::cout << "MOV DELAY, V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x18:
      //         {
      //            std::cout << "MOV SOUND, V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x1e:
      //         {
      //            std::cout << "ADD I, V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x29:
      //         {
      //            std::cout << "SPRITECHAR V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x33:
      //         {
      //            std::cout << "MOVBCD V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x55:
      //         {
      //            std::cout << "MOVM (I), V0-V";
      //            output_hex(reg, 1);
      //            break;
      //         }
      //         case 0x65:
      //         {
      //            std::cout << "MOVM V0-V";
      //            output_hex(reg, 1);
      //            std::cout << ", (I)";
      //            break;
      //         }
      //         default:
      //            std::cout << "Not supported!";
      //            break;
      //      }
      //      std::cout << std::endl;
      //      break;
      //   }
      //   default:
      //      std::cout << "Not supported!" << std::endl;
      //      break;
      //   }
}

void chip8::chip8::clear_graphics_memory()
{
   std::fill(std::begin(m_gfx_memory), std::end(m_gfx_memory), 0);
}

void chip8::chip8::clear_memory()
{
   std::fill(std::begin(m_memory), std::end(m_memory), 0);
}

void chip8::chip8::clear_registers()
{
   for (uint8_t i = 0; i < 16; i++)
   {
      m_registers[i] = 0;
   }
}
