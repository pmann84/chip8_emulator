#pragma once

#include <string>
#include <ostream>
#include <SDL.h>

#include "emulator.h"

constexpr uint32_t WIDTH = 640;
constexpr uint32_t HEIGHT = 320;
constexpr uint32_t SCREEN_COLOUR = 0x008f11;
constexpr uint32_t BACKGROUND_COLOUR = 0x0;

constexpr chip8::byte_t key_map[16] = {
   SDLK_x, SDLK_1, SDLK_2, SDLK_3, // 1, 2, 3, C
   SDLK_q, SDLK_w, SDLK_e, SDLK_a, // 4, 5, 6, D
   SDLK_s, SDLK_d, SDLK_z, SDLK_c, // 7, 8, 9, E
   SDLK_4, SDLK_r, SDLK_f, SDLK_v  // A, 0, B, F
};

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