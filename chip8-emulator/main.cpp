
#include <iostream>
#include <fstream>
#include <string>

#include "application.h"


int main(int argc, char* argv[])
{
   std::filesystem::path program_filepath("C:\\Projects\\chip8-emulator\\programs\\fishie.ch8");
   
   app a;
   a.load_program(program_filepath);
   a.run();

   return 0;
}