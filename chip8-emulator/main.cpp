
#include <iostream>
#include <fstream>
#include <string>

#include "application.h"


//void decode_chip8_ops(chip8::buffer_t buffer)
//{
//   for (uint16_t i = 0; i < buffer.size(); i+=2)
//   {
//      auto first_byte = buffer[i];
//      auto second_byte = buffer[i + 1];
//      decode(first_byte, second_byte);
//   }
//}

int main(int argc, char* argv[])
{
   std::filesystem::path program_filepath("C:\\Projects\\chip8-emulator\\programs\\tetris.ch8");
   
   app a;
   a.load_program(program_filepath);
   a.run();

   return 0;
}