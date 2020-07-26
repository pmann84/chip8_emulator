#include "emulator.h"

chip8::emulator::emulator() : m_draw_flag(false)
{
}

void chip8::emulator::load_program(std::filesystem::path path)
{
   m_chip.load_program(path);
}

void chip8::emulator::run_cycle()
{
   m_draw_flag = m_chip.execute_opcode();
   m_chip.update_timers();
}

bool chip8::emulator::should_draw()
{
   return m_draw_flag;
}

void chip8::emulator::set_keys()
{
}

chip8::chip8::graphics_t chip8::emulator::display_data()
{
   return m_chip.display_data();
}
