#include "emulator.h"

#include <chrono>
#include <thread>

namespace chip8
{

   emulator::emulator() : m_draw_flag(false), m_speed(16)
   {
   }

   bool emulator::load_program(std::filesystem::path path)
   {
      m_last_loaded_rom = path;
      return m_chip.load_program(path);
   }

   void emulator::run_cycle()
   {
      if (m_chip.execute_opcode())
      {
         m_draw_flag = true;
      }
   }

   void emulator::update_timers()
   {
      m_chip.update_timers();
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
      m_chip.set_key(index, pressed ? 1 : 0);
   }

   graphics_t emulator::display_data()
   {
      return m_chip.display_data();
   }

   void emulator::sleep()
   {
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(m_speed)));
   }

   void emulator::increase_speed()
   {
      m_speed -= 5;
      if (m_speed <= 0)
      {
         m_speed = 1;
      }
   }

   void emulator::decrease_speed()
   {
      m_speed += 5;
   }
   void emulator::reload()
   {
      m_chip.reload();
      m_chip.load_program(m_last_loaded_rom);
      m_draw_flag = true;
   }
}
