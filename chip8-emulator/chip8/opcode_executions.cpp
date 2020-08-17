#include "opcode_executions.h"

#include "opcode.h"
#include "chip8.h"

namespace chip8
{
   bool opcode_not_implemented(const opcode& code, cpu& cpu) 
   {
      std::cout << "Opcode [" << code << "] not implemented! Skipping! Warning: program may not run correctly." << std::endl;
      cpu.set_program_counter(2);
      return false; 
   }
   
   bool opcode_0nnn(const opcode& code, cpu& cpu)
   {
      return display_chip_table[code.lower_half_of_last_byte()](code, cpu);
   }

   bool opcode_00e0(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 00E0
      // Clears the screen.
      cpu.clear_graphics_memory();
      cpu.increment_program_counter(2);
      return true;
   }

   bool opcode_00ee(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 00EE
      // Returns from a subroutine.
      cpu.set_program_counter_from_stack();
      cpu.increment_program_counter(2);
      return false;
   }

   bool opcode_1nnn(const opcode& code, cpu& cpu)
   { 
      // Opcode: 1NNN
      // Jumps to address NNN.
      program_counter_t addr = code.get_last_12_bits();
      cpu.set_program_counter(addr);
      return false; 
   }

   bool opcode_2nnn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 2NNN
      // Calls subroutine at NNN.
      program_counter_t addr = code.get_last_12_bits();
      cpu.store_program_counter_in_stack();
      cpu.set_program_counter(addr);
      return false;
   }

   bool opcode_3xnn(const opcode& code, cpu& cpu)
   { 
      // Opcode: 3XNN
      // Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
      auto reg = code.lower_half_of_first_byte();
      auto value = code.last_byte();
      cpu.increment_program_counter(cpu.get_register(reg) == value ? 4 : 2);
      return false; 
   }

   bool opcode_4xnn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 4XNN
      // Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
      auto reg = code.lower_half_of_first_byte();
      auto value = code.last_byte();
      cpu.increment_program_counter(cpu.get_register(reg) != value ? 4 : 2);
      return false; 
   }

   bool opcode_5xy0(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 5XY0
      // Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.increment_program_counter(cpu.get_register(first_reg) == cpu.get_register(last_reg) ? 4 : 2);
      return false; 
   }

   bool opcode_6xnn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 6XNN
      // Sets VX to NN.
      auto reg = code.lower_half_of_first_byte();
      auto value = code.last_byte();
      cpu.set_register(reg, value);
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_7xnn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 7XNN
      // Adds NN to VX. (Carry flag is not changed)
      auto reg = code.lower_half_of_first_byte();
      auto value = code.last_byte();
      cpu.set_register(reg, cpu.get_register(reg) + value);
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xyn(const opcode& code, cpu& cpu) 
   { 
      return arithmetic_chip_table[code.lower_half_of_last_byte()](code, cpu);
   }

   bool opcode_8xy0(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XY0
      // Sets VX to the value of VY.
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.set_register(first_reg, cpu.get_register(last_reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xy1(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XY1
      // Sets VX to VX or VY. (Bitwise OR operation)
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.set_register(first_reg, cpu.get_register(first_reg) | cpu.get_register(last_reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xy2(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XY2
      // Sets VX to VX and VY. (Bitwise AND operation)
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.set_register(first_reg, cpu.get_register(first_reg) & cpu.get_register(last_reg));
      cpu.increment_program_counter(2);
      return false;
   }

   bool opcode_8xy3(const opcode& code, cpu& cpu) 
   {
      // Opcode: 8XY3
      // Sets VX to VX xor VY.
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.set_register(first_reg, cpu.get_register(first_reg) ^ cpu.get_register(last_reg));
      cpu.increment_program_counter(2);
      return false;
   }

   bool opcode_8xy4(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XY4
      // Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      if (cpu.get_register(last_reg) > (0xFF - cpu.get_register(first_reg)))
         cpu.set_register(0xF, 1); //carry
      else
         cpu.set_register(0xF, 0);
      cpu.set_register(first_reg, cpu.get_register(first_reg) + cpu.get_register(last_reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xy5(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XY5
      // VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      if (cpu.get_register(last_reg) > cpu.get_register(first_reg))
         cpu.set_register(0xF, 1); //carry
      else
         cpu.set_register(0xF, 0);
      cpu.set_register(first_reg, cpu.get_register(first_reg) - cpu.get_register(last_reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xy6(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XY6
      // Stores the least significant bit of VX in VF and then shifts VX to the right by 1
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.set_register(0xF, cpu.get_register(first_reg) & 0x1);
      cpu.set_register(first_reg, cpu.get_register(first_reg) >> 1);
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xy7(const opcode& code, cpu& cpu) 
   {
      // Opcode: 8XY7
      // Sets VX to VY minus VX.VF is set to 0 when there's a borrow, and 1 when there isn't.
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      if (cpu.get_register(first_reg) > cpu.get_register(last_reg))	// VY-VX
         cpu.set_register(0xF, 0); // there is a borrow
      else
         cpu.set_register(0xF, 1);
      cpu.set_register(first_reg, cpu.get_register(last_reg) - cpu.get_register(first_reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_8xye(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 8XYE
      // Stores the most significant bit of VX in VF and then shifts VX to the left by 1
      uint8_t first_reg = code.lower_half_of_first_byte();
      cpu.set_register(0xF, cpu.get_register(first_reg) >> 7);
      cpu.set_register(first_reg, cpu.get_register(first_reg) << 1);
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_9xy0(const opcode& code, cpu& cpu) 
   { 
      // Opcode: 9XY0
      // Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      cpu.increment_program_counter(cpu.get_register(first_reg) != cpu.get_register(last_reg) ? 4 : 2);
      return false; 
   }

   bool opcode_annn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: ANNN
      // Sets I to the address NNN.
      cpu.set_index_register(code.get_last_12_bits());
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_bnnn(const opcode& code, cpu& cpu)
   { 
      // Opcode: BNNN
      // Jumps to the address NNN plus V0.
      program_counter_t addr = code.get_last_12_bits();
      cpu.set_program_counter(addr + cpu.get_register(0));
      return false; 
   }

   bool opcode_cxnn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: CXNN 
      // Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
      uint8_t reg = code.lower_half_of_first_byte();
      auto mask = code.last_byte();
      cpu.set_register(reg, (rand() % (0xFF + 1)) & mask);
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_dxyn(const opcode& code, cpu& cpu) 
   { 
      // Opcode: DXYN 
      // Draws a sprite at coordinate(VX, VY) that has a width of 8 pixels 
      // and a height of N pixels.Each row of 8 pixels is read as bit - coded 
      // starting from memory location I; I value doesn’t change after the 
      // execution of this instruction.As described above, VF is set to 1 
      // if any screen pixels are flipped from set to unset when the sprite 
      // is drawn, and to 0 if that doesn’t happen

      uint8_t first_reg = code.lower_half_of_first_byte();
      uint8_t last_reg = code.upper_half_of_last_byte();
      auto x_loc = cpu.get_register(first_reg);
      auto y_loc = cpu.get_register(last_reg);
      uint8_t height = code.lower_half_of_last_byte();
      uint8_t pixel;

      cpu.set_register(0xf, 0);

      for (int y = 0; y < height; ++y)
      {
         pixel = cpu.get_value_of_memory_at_location(cpu.get_index_register() + y);
         for (int x = 0; x < 8; ++x)
         {
            if ((pixel & (0x80 >> x)) != 0)
            {
               auto gfx_mem_idx = x_loc + x + ((y_loc + y) * 64);
               if (cpu.get_value_of_gfx_memory_at_location(gfx_mem_idx) == 1)
               {
                  cpu.set_register(0xf, 1);
               }
               cpu.set_value_of_gfx_memory_at_location(gfx_mem_idx, cpu.get_value_of_gfx_memory_at_location(gfx_mem_idx) ^ 1);
            }
         }
      }

      cpu.increment_program_counter(2);
      return true;
   }

   bool opcode_exnn(const opcode& code, cpu& cpu) 
   { 
      return key_chip_table[code.upper_half_of_last_byte()](code, cpu);
   }

   bool opcode_ex9e(const opcode& code, cpu& cpu) 
   { 
      // Opcode: EX9E
      // Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
      auto reg = code.lower_half_of_first_byte();
      cpu.increment_program_counter(cpu.is_key_in_register_pressed(reg) ? 4 : 2);
      return false; 
   }

   bool opcode_exa1(const opcode& code, cpu& cpu) 
   { 
      // Opcode: EXA1
      // Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
      auto reg = code.lower_half_of_first_byte();
      cpu.increment_program_counter(!cpu.is_key_in_register_pressed(reg) ? 4 : 2);
      return false; 
   }

   bool opcode_fxnn(const opcode& code, cpu& cpu) 
   { 
      auto idx = code.upper_half_of_last_byte();
      return misc_chip_table[code.upper_half_of_last_byte()](code, cpu);
   }

   bool opcode_fx0n(const opcode& code, cpu& cpu) 
   { 
      return misc_chip_sub_table_zero[code.lower_half_of_last_byte()](code, cpu);
   }

   bool opcode_fx07(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX07
      // Sets VX to the value of the delay timer.
      uint8_t reg = code.lower_half_of_first_byte();
      cpu.set_register(reg, cpu.get_delay_timer());
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_fx0a(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX0A
      // A key press is awaited, and then stored in VX. (Blocking Operation.All instruction halted until next key event)
      uint8_t reg = code.lower_half_of_first_byte();

      if (!cpu.check_for_key_press(reg))
         return false; // Try again until a key is pressed

      cpu.increment_program_counter(2);
      return false;
   }

   bool opcode_fx1n(const opcode& code, cpu& cpu) 
   {
      return misc_chip_sub_table_one[code.lower_half_of_last_byte()](code, cpu);
   }

   bool opcode_fx1e(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX1E
      // Adds VX to I.VF is not affected.
      uint8_t reg = code.lower_half_of_first_byte();
      cpu.set_index_register(cpu.get_index_register() + cpu.get_register(reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_fx15(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX15
      // Sets the delay timer to VX.
      uint8_t reg = code.lower_half_of_first_byte();
      cpu.set_delay_timer(cpu.get_register(reg));
      cpu.increment_program_counter(2);
      return false;
   }

   bool opcode_fx18(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX18
      // Sets the sound timer to VX.
      uint8_t reg = code.lower_half_of_first_byte();
      cpu.set_sound_timer(cpu.get_register(reg));
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_fx29(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX29
      // Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
      uint8_t reg = code.lower_half_of_first_byte();
      cpu.set_index_register(cpu.get_register(reg) * 0x5);
      cpu.increment_program_counter(2);
      return false; 
   }

   bool opcode_fx33(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX33
      // Stores the binary-coded decimal representation of VX, with the most significant of three digits 
      // at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. 
      // (In other words, take the decimal representation of VX, place the hundreds digit in memory at 
      // location in I, the tens digit at location I+1, and the ones digit at location I+2.)
      uint8_t reg = code.lower_half_of_first_byte();
      auto idx = cpu.get_index_register();
      auto value_at_reg = cpu.get_register(reg);
      cpu.set_value_of_memory_at_location(idx, value_at_reg / 100);
      cpu.set_value_of_memory_at_location(idx + 1, (value_at_reg / 10) % 10);
      cpu.set_value_of_memory_at_location(idx + 2, (value_at_reg % 100) % 10);
      cpu.increment_program_counter(2);
      return false; 
   }
   bool opcode_fx55(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX55
      // Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 
      // 1 for each value written, but I itself is left unmodified.
      uint8_t reg = code.lower_half_of_first_byte();
      auto idx = cpu.get_index_register();
      for (int i = 0; i <= reg; ++i)
      {
         cpu.set_value_of_memory_at_location(idx + i, cpu.get_register(i));
      }
      cpu.increment_program_counter(2);
      return false;
   }
   
   bool opcode_fx65(const opcode& code, cpu& cpu) 
   { 
      // Opcode: FX65
      // Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is 
      // increased by 1 for each value written, but I itself is left unmodified.
      uint8_t reg = code.lower_half_of_first_byte();
      auto idx = cpu.get_index_register();
      for (int i = 0; i <= reg; ++i)
      {
         cpu.set_register(i, cpu.get_value_of_memory_at_location(idx + i));
      }
      cpu.increment_program_counter(2);
      return false;
   }

}