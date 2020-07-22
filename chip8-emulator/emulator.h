#pragma once

#include <filesystem>

#include "chip8.h"

namespace chip8
{
   class emulator
   {
   public:
      emulator();

      void load_program(std::filesystem::path path);
      void run_cycle();
      bool should_draw();
      void set_keys();

   private:
      chip8 m_chip;
      bool m_draw_flag;
   };
}