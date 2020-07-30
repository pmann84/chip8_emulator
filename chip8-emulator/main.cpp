
#include <iostream>
#include <fstream>
#include <string>

#include "application.h"

// TODO: Add timer code
// TODO: Add specification of program path via commandline


int main(int argc, char* argv[])
{
   std::filesystem::path program_filepath("C:\\Projects\\chip8-emulator\\programs\\tetris.ch8");
   
   app a;
   a.load_program(program_filepath);
   a.run();

   return 0;
}