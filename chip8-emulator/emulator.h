#pragma once

#include "chip8/clock.h"
#include "chip8/cpu.h"
#include "chip8/memory.h"

#include <filesystem>


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
      memory m_memory;
      clock m_cpu_clock;
      clock m_delay_timer_clock;
      clock m_sound_timer_clock;
      bool m_draw_flag;
      std::filesystem::path m_last_loaded_rom;
   };
}