#include "chip8.h"

#include <fstream>

chip8::chip8::chip8()
{
   clear_graphics_memory();
   clear_memory();
   clear_registers();
   clear_keys();
   load_fontset();
}

void chip8::chip8::load_fontset()
{
   // Load fontset
   for (int i = 0; i < 80; ++i)
   {
      m_memory[i] = fontset[i];
   }
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
            --m_stack_ptr;
            m_program_ctr = m_stack[m_stack_ptr];
            m_program_ctr += 2;
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
      case opcode_defs::CALL:
      {
         program_counter_t addr = code.get_last_12_bits();
         m_stack[m_stack_ptr++] = m_program_ctr;
         m_program_ctr = addr;
         return false;
      }
      case opcode_defs::SKIP_EQ:
      {
         auto reg = code.lower_half_of_first_byte();
         auto value = code.last_byte();
         m_program_ctr += m_registers[reg] == value ? 4 : 2;
         return false;
      }
      case opcode_defs::SKIP_NEQ:
      {
         auto reg = code.lower_half_of_first_byte();
         auto value = code.last_byte();
         m_program_ctr += m_registers[reg] != value ? 4 : 2;
         return false;
      }
      case opcode_defs::SKIP_EQ_V:
      {
         uint8_t first_reg = code.lower_half_of_first_byte();
         uint8_t last_reg = code.upper_half_of_last_byte();
         m_program_ctr += m_registers[first_reg] == m_registers[last_reg] ? 4 : 2;
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
      case opcode_defs::COMP:
      {
         // Get the last bit to get the operation
         uint8_t operation = code.lower_half_of_last_byte();
         // get registers
         uint8_t first_reg = code.lower_half_of_first_byte();
         uint8_t last_reg = code.upper_half_of_last_byte();
         switch (operation)
         {
         case opcode_defs::comp::MOV_V:
            m_registers[first_reg] = m_registers[last_reg];
            return false;
         case opcode_defs::comp::OR_V:
            m_registers[first_reg] |= m_registers[last_reg];
            return false;
         case opcode_defs::comp::AND_V:
            m_registers[first_reg] &= m_registers[last_reg];
            return false;
         case opcode_defs::comp::XOR_V:
            m_registers[first_reg] ^= m_registers[last_reg];
            return false;
         case opcode_defs::comp::ADD_C_V:
            if (m_registers[last_reg] > (0xFF - m_registers[first_reg]))
               m_registers[0xF] = 1; //carry
            else
               m_registers[0xF] = 0;
            m_registers[first_reg] += m_registers[last_reg];
            return false;
         case opcode_defs::comp::SUB_C_V:
            if (m_registers[last_reg] > m_registers[first_reg])
               m_registers[0xF] = 1; //carry
            else
               m_registers[0xF] = 0;
            m_registers[first_reg] -= m_registers[last_reg];
            return false;
         case opcode_defs::comp::SHR_C_V:
            m_registers[0xF] = m_registers[first_reg] & 0x1;
            m_registers[first_reg] >>= 1;
            return false;
         case opcode_defs::comp::SUBB_C_V:
            if (m_registers[first_reg] > m_registers[last_reg])	// VY-VX
               m_registers[0xF] = 0; // there is a borrow
            else
               m_registers[0xF] = 1;
            m_registers[first_reg] = m_registers[last_reg] - m_registers[first_reg];
            return false;
         case opcode_defs::comp::SHL_C_V:
            m_registers[0xF] = m_registers[first_reg] >> 7;
            m_registers[first_reg] <<= 1;
            return false;
         default:
            std::cout << "Not supported!" << std::endl;
            return false;
         }
         m_program_ctr += 2;
      }
      case opcode_defs::SKIP_NEQ_V:
      {
         uint8_t first_reg = code.lower_half_of_first_byte();
         uint8_t last_reg = code.upper_half_of_last_byte();
         m_program_ctr += m_registers[first_reg] != m_registers[last_reg] ? 4 : 2;
         return false;
      }
      case opcode_defs::MVI_I:
      {
         m_idx_register = code.get_last_12_bits();
         m_program_ctr += 2;
         return true;
      }
      case opcode_defs::SPRITE_V:
      {
         // TODO: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
         // Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
         // Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
         uint8_t first_reg = code.lower_half_of_first_byte();
         uint8_t last_reg = code.upper_half_of_last_byte();
         uint8_t height = code.lower_half_of_last_byte();
         uint8_t pixel;

         m_registers[0xf] = 0;

         for (int y = 0; y < height; ++y)
         {
            pixel = m_memory[m_idx_register + y];
            for (int x = 0; x < 8; ++x)
            {
               if (pixel & (0x80 >> x) != 0)
               {
                  auto gfx_mem_idx = first_reg + x + ((last_reg + y) * 64);
                  if (m_gfx_memory[gfx_mem_idx] == 1)
                  {
                     m_registers[0xf] = 1;
                  }
                  m_gfx_memory[gfx_mem_idx] ^= 1;
               }
            }
         }

         m_program_ctr += 2;
         return true;
      }
      case opcode_defs::MISC:
      {
         uint8_t reg = code.lower_half_of_first_byte();
         auto last_byte = code.last_byte();
         switch (last_byte)
         {
            case opcode_defs::misc::MOV_V_DELAY:
            {
               m_registers[reg] = m_delay_timer;
               m_program_ctr += 2;
               return false;
            }
            case opcode_defs::misc::WAITKEY_V:
            {
               // Blocking on key press
               bool key_press = false;

               for (int i = 0; i < 16; ++i)
               {
                  if (m_keys[i] != 0)
                  {
                     m_registers[reg] = i;
                     key_press = true;
                  }
               }

               if (!key_press)
                  return false; // Try again until a key is pressed

               m_program_ctr += 2;
               //std::cout << "WAITKEY V";
               //output_hex(reg, 1);
               return false;
            }
            case opcode_defs::misc::MOV_DELAY_V:
            {
               m_delay_timer = m_registers[reg];
               m_program_ctr += 2;
               return false;
            }
            case opcode_defs::misc::MOV_SOUND_V:
            {
               m_sound_timer = m_registers[reg];
               m_program_ctr += 2;
               return false;
            }
            case opcode_defs::misc::ADD_I_V:
            {
               m_idx_register = m_registers[reg];
               m_program_ctr += 2;
               return false;
            }
            case opcode_defs::misc::SPRITECHAR_V:
            {
               m_idx_register = m_registers[reg] * 0x5;
               m_program_ctr += 2;
               return false;
            }
            case opcode_defs::misc::MOVBCD_V:
            {
               m_memory[m_idx_register] = m_registers[reg] / 100;
               m_memory[m_idx_register + 1] = (m_registers[reg] / 10) % 10;
               m_memory[m_idx_register + 2] = (m_registers[reg] % 100) % 10;
               m_program_ctr += 2;
            }
            case opcode_defs::misc::MOVM_I:
            {
               for (int i = 0; i <= reg; ++i)
               {
                  m_memory[m_idx_register + i] = m_registers[i];
               }
               m_program_ctr += 2;
               return false;
            }
            case opcode_defs::misc::MOVM:
            {
               for (int i = 0; i <= reg; ++i)
               {
                  m_registers[i] = m_memory[m_idx_register + i];
               }
               m_program_ctr += 2;
               return false;
            }
            default:
               return false; // Not supported
         }
         return false;
      }
      default:
      {
         std::cout << "Opcode " << code << " not supported!" << std::endl;
         return false;
      }
   }


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

void chip8::chip8::clear_keys()
{
   for (uint8_t i = 0; i < 16; i++)
   {
      m_keys[i] = 0;
   }
}
