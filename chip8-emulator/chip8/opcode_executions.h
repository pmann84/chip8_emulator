#pragma once

#include <functional>
#include <iostream>
#include <iomanip>

namespace chip8
{
   class cpu;
   class opcode;
   class keyboard;
   class memory;
   class gfx_memory;

   using opcode_execution_func_t = std::function<bool(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys)>;

   bool opcode_not_implemented(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_0nnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_00e0(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_00ee(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_1nnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_2nnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_3xnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_4xnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_5xy0(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_6xnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_7xnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_8xyn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy0(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy1(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy2(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy3(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy4(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy5(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy6(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xy7(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_8xye(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_9xy0(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_annn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_bnnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_cxnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_dxyn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   
   bool opcode_exnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_ex9e(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_exa1(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_fxnn(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_fx0n(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx07(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx0a(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_fx1n(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx1e(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx15(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx18(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   bool opcode_fx29(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx33(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx55(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);
   bool opcode_fx65(const opcode& code, cpu& cpu, memory& ram, gfx_memory& gfx, keyboard& keys);

   // Chip table - defines functions for executing opcode instructions based on the first
   // half of the first byte of the opcode e.g. DXYN is keyed off D etc. Some codes that 
   // have more than one instruction per first half byte are delegated to their own function
   // tables e.g. 8XYN
   static opcode_execution_func_t chip_table[16] = {
      opcode_0nnn, opcode_1nnn, opcode_2nnn, opcode_3xnn, 
      opcode_4xnn, opcode_5xy0, opcode_6xnn, opcode_7xnn, 
      opcode_8xyn, opcode_9xy0, opcode_annn, opcode_bnnn,
      opcode_cxnn, opcode_dxyn, opcode_exnn, opcode_fxnn
   };

   // Display chip table
   static opcode_execution_func_t display_chip_table[16] = {
      opcode_00e0           , opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, 
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, 
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_00ee           , opcode_not_implemented
   };

   // Arithmetic chip table
   // Only has operations defined for 0-7, E.
   static opcode_execution_func_t arithmetic_chip_table[16] = {
      opcode_8xy0           , opcode_8xy1           , opcode_8xy2           , opcode_8xy3,
      opcode_8xy4           , opcode_8xy5           , opcode_8xy6           , opcode_8xy7,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_8xye           , opcode_not_implemented
   };

   // Key chip table
   // Only two key opcodes, keyed off the upper half of the last byte
   static opcode_execution_func_t key_chip_table[16] = {
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_ex9e           , opcode_exa1           , opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented
   };
   
   // Misc chip table
   static opcode_execution_func_t misc_chip_table[16] = {
      opcode_fx0n           , opcode_fx1n           , opcode_fx29           , opcode_fx33,
      opcode_not_implemented, opcode_fx55           , opcode_fx65           , opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented
   };

   // Misc chip sub table - 0 index
   static opcode_execution_func_t misc_chip_sub_table_zero[16] = {
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_fx07,
      opcode_not_implemented, opcode_not_implemented, opcode_fx0a           , opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented
   };

   // Misc chip sub table - 1 index
   static opcode_execution_func_t misc_chip_sub_table_one[16] = {
      opcode_not_implemented, opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_fx15           , opcode_not_implemented, opcode_not_implemented,
      opcode_fx18           , opcode_not_implemented, opcode_not_implemented, opcode_not_implemented,
      opcode_not_implemented, opcode_not_implemented, opcode_fx1e           , opcode_not_implemented
   };
}