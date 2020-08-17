#include "application.h"

application::application() : m_is_running(false)
{
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      log_sdl_error(std::cout, "SDL_Init");
      return;
   }

   m_window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
   if (m_window == nullptr)
   {
      log_sdl_error(std::cout, "SDL_CreateWindow");
      SDL_Quit();
      return;
   }

   m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (m_renderer == nullptr)
   {
      SDL_DestroyWindow(m_window);
      log_sdl_error(std::cout, "SDL_CreateRenderer");
      SDL_Quit();
      return;
   }

   m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 64, 32);
}

application::~application()
{
   SDL_Quit();
}

bool application::load_program(std::filesystem::path program_filepath)
{
   return m_emulator.load_program(program_filepath);
}

void application::run()
{
   m_is_running = true;
   while (m_is_running)
   {
      m_emulator.run_cycle();

      // Check for any input and set any key presses here
      while (SDL_PollEvent(&m_poll_event) != 0)
      {
         switch (m_poll_event.type)
         {
            case SDL_QUIT:
            {
               m_is_running = false;
               break;
            }
            case SDL_KEYDOWN:
            {
               switch (m_poll_event.key.keysym.sym)
               {
                  case SDLK_F5:
                  {
                     m_emulator.reload();
                     break;
                  }
               }
               auto key_it = key_map.find(m_poll_event.key.keysym.sym);
               if (key_it != key_map.end())
               {
                  m_emulator.set_keys(key_it->second, true);
               }
               break;
            }
            case SDL_KEYUP:
            {
               auto key_it = key_map.find(m_poll_event.key.keysym.sym);
               if (key_it != key_map.end())
               {
                  m_emulator.set_keys(key_it->second, false);
               }
               break;
            }
         }
      }

      if (m_emulator.should_draw())
      {
         // Draw to the screen
         auto pixel_data = m_emulator.display_data();
         Uint32 pixels[64 * 32];
         for (int i = 0; i < (64 * 32); i++)
         {
            pixels[i] = pixel_data[i] ? SCREEN_COLOUR : BACKGROUND_COLOUR;
         }
         SDL_UpdateTexture(m_texture, NULL, &pixels[0], 64 * 4);
         SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         SDL_RenderClear(m_renderer);
         SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
         SDL_RenderPresent(m_renderer);
         m_emulator.reset_draw_flag();
      }

      m_emulator.update_timers();
   }
}