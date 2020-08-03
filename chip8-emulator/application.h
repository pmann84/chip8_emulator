#pragma once

#include <string>
#include <ostream>
#include <map>
#include <SDL.h>

#include "emulator.h"

constexpr uint32_t WIDTH = 640;
constexpr uint32_t HEIGHT = 320;
constexpr uint32_t SCREEN_COLOUR = 0x008f11;
constexpr uint32_t BACKGROUND_COLOUR = 0x0;

const std::map<SDL_Keycode, chip8::byte_t> key_map = { 
   {SDLK_x, 0x0}, {SDLK_1, 0x1}, {SDLK_2, 0x2}, {SDLK_3, 0x3},
   {SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_a, 0x7},
   {SDLK_s, 0x8}, {SDLK_d, 0x9}, {SDLK_z, 0xa}, {SDLK_c, 0xb},
   {SDLK_4, 0xc}, {SDLK_r, 0xd}, {SDLK_f, 0xe}, {SDLK_v, 0xf}
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

   bool load_program(std::filesystem::path program_filepath);
   void run();

private:
   chip8::emulator m_emulator;
   SDL_Window* m_window;
   SDL_Renderer* m_renderer;
   SDL_Texture* m_texture;
   SDL_Event m_poll_event;
   bool m_is_running;
};