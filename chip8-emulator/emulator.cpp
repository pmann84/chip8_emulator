#include "emulator.h"

#include "chip8/opcode_executions.h"

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
      return m_memory.load_program(path);
   }

   void emulator::run_cycle()
   {
      if (m_cpu_clock.tick() && execute_next_opcode())
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
      m_keyboard.set(index, pressed ? 1 : 0);
   }

   const graphics_t& emulator::display_data()
   {
      return m_gfx_memory.pixels();
   }

   void emulator::reload()
   {
      m_cpu.clear();
      m_gfx_memory.clear();
      m_keyboard.clear();
      m_delay_timer_clock.reset();
      m_sound_timer_clock.reset();
      m_cpu_clock.reset();
      m_memory.clear();
      m_memory.load_program(m_last_loaded_rom);
      m_draw_flag = true;
   }

   opcode chip8::emulator::get_next_opcode(cpu& cpu, memory& ram)
   {
      return m_memory.read(m_cpu.get_program_counter());
   }

   bool emulator::execute_next_opcode()
   {
      opcode code = get_next_opcode(m_cpu, m_memory);
      return chip_table[code.upper_half_of_first_byte()](code, m_cpu, m_memory, m_gfx_memory, m_keyboard);
   }
}
