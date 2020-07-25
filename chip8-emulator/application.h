#pragma once

#include <string>
#include <ostream>
#include <SDL.h>

#include "emulator.h"

constexpr uint32_t WIDTH = 640;
constexpr uint32_t HEIGHT = 320;
constexpr uint32_t SCREEN_COLOUR = 0x008f11;
constexpr uint32_t BACKGROUND_COLOUR = 0x0;

inline void log_sdl_error(std::ostream& os, const std::string& message)
{
   os << message << " error: " << SDL_GetError() << std::endl;
}

class app
{
public:
   app();
   ~app();

   void load_program(std::filesystem::path program_filepath);
   void run();

private:
   chip8::emulator m_emulator;
   SDL_Window* m_window;
   SDL_Renderer* m_renderer;
   SDL_Texture* m_texture;
   SDL_Event m_poll_event;
   bool m_is_running;
};