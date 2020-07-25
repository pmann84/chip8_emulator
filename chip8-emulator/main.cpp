
#include <iostream>
#include <fstream>
#include <string>

#include "application.h"

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

int WinMain()
{
   std::filesystem::path program_filepath("C:\\Projects\\chip8-emulator\\programs\\fishie.ch8");
   
   app a;
   a.load_program(program_filepath);
   a.run();

   return 0;
}