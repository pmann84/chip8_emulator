#include "emulator.h"

#include <chrono>
#include <thread>

namespace chip8
{

   emulator::emulator() 
      : m_draw_flag(false)
      , m_cpu_clock(CPU_SPEED)
      , m_delay_timer_clock(REFRESH_RATE)
      , m_sound_timer_clock(REFRESH_RATE)
   {
   }

   bool emulator::load_program(std::filesystem::path path)
   {
      m_last_loaded_rom = path;
      return m_cpu.load_program(path);
   }

   void emulator::run_cycle()
   {
      if (m_cpu_clock.tick() && m_cpu.execute_opcode())
      {
         m_draw_flag = true;
      }
   }

   void emulator::update_timers()
   {
      if (m_delay_timer_clock.tick())
      {
         m_cpu.cycle_delay_timer();
      }
      if (m_sound_timer_clock.tick())
      {
         m_cpu.cycle_sound_timer();
      }
   }

   bool emulator::should_draw()
   {
      return m_draw_flag;
   }

   void emulator::reset_draw_flag()
   {
      m_draw_flag = false;
   }

   void emulator::set_keys(byte_t index, bool pressed)
   {
      m_cpu.set_key(index, pressed ? 1 : 0);
   }

   const graphics_t& emulator::display_data()
   {
      return m_cpu.display_data();
   }

   void emulator::reload()
   {
      m_cpu.reload();
      m_cpu.load_program(m_last_loaded_rom);
      m_draw_flag = true;
   }
}
