#pragma once

#include <filesystem>

#include "chip8.h"

namespace chip8
{
   class emulator
   {
   public:
      emulator();

      bool load_program(std::filesystem::path path);
      void run_cycle();
      void update_timers();
      bool should_draw();
      void reset_draw_flag();
      void set_keys(byte_t index, bool pressed);
      graphics_t display_data();
      void reload();

   private:
      cpu m_chip;
      bool m_draw_flag;
      clock m_cpu_clock;
      clock m_delay_timer_clock;
      clock m_sound_timer_clock;
      std::filesystem::path m_last_loaded_rom;
   };
}