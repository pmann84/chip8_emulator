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
      void set_keys(uint8_t index, bool pressed);
      graphics_t display_data();

   private:
      cpu m_chip;
      bool m_draw_flag;
   };
}