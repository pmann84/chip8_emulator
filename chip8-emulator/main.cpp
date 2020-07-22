
#include <iostream>
#include <fstream>
#include <string>

#include "emulator.h"

//template<typename T>
//void output_hex(T v, uint8_t padding=2)
//{
//   std::ios_base::fmtflags f(std::cout.flags());
//   std::cout << std::hex << std::setw(padding) << std::setfill('0') << int(v);
//   std::cout.flags(f);
//}
//
//void decode_chip8_ops(chip8::buffer_t buffer)
//{
//   for (uint16_t i = 0; i < buffer.size(); i+=2)
//   {
//      auto first_byte = buffer[i];
//      auto second_byte = buffer[i + 1];
//      decode(first_byte, second_byte);
//   }
//}
//
//chip8::buffer_t read_chip8_program_from_file(std::filesystem::path filepath)
//{
//   std::basic_ifstream<unsigned char> program(filepath, std::ios::out | std::ios::binary);
//   // Get the file size
//   program.seekg(0, program.end);
//   uint16_t program_size = program.tellg();
//   program.seekg(0, program.beg);
//   std::cout << "Program size: " << program_size << "b" << std::endl;
//   chip8::buffer_t buffer(chip8::CHIP8_MEMORY_START + program_size);
//   program.read(&buffer[chip8::CHIP8_MEMORY_START], program_size);
//   program.close();
//   std::cout << "Read " << buffer.size() << "b" << std::endl;
//   return buffer;
//}



int main()
{
   std::filesystem::path program_filepath("C:\\Projects\\chip8-emulator\\programs\\fishie.ch8");

   chip8::emulator emu;
   emu.load_program(program_filepath);

   // TODO: Make this only execute at 60Hz, so 60 cycle executions per second
   while (true)
   {
      // Run a cycle of the chip8 cpu - executes a single opcode
      emu.run_cycle();

      if (emu.should_draw())
      {
         // TODO: Draw to the screen
      }

      // TODO: Set any key presses here
      emu.set_keys();
   }

   //buffer_t program_buffer = read_chip8_program_from_file(program_filepath);
   //decode_chip8_ops(program_buffer);

   //chip8 chip_state;

   //std::cin.get();
   return 0;
}