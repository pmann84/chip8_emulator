
#include <iostream>
#include <fstream>
#include <string>

#include "application.h"

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      std::cerr << "Incorrect arguments: <ROM PATH>" << std::endl;
      return 1;
   }
   std::filesystem::path program_filepath(argv[1]);
   
   application app;
   if (!app.load_program(program_filepath))
   {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot load program.", "File does not exist!", NULL);
      return 0;
   }
   app.run();

   return 0;
}