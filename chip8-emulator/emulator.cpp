#include "emulator.h"

namespace chip8
{

   emulator::emulator() : m_draw_flag(false)
   {
   }

   void emulator::load_program(std::filesystem::path path)
   {
      m_chip.load_program(path);
   }

   void emulator::run_cycle()
   {
      m_draw_flag = m_chip.execute_opcode();
      m_chip.update_timers();
   }

   bool emulator::should_draw()
   {
      return m_draw_flag;
   }

   void emulator::set_keys()
   {
   }

   graphics_t emulator::display_data()
   {
      return m_chip.display_data();
   }
}
