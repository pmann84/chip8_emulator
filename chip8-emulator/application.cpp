#include "application.h"

app::app() : m_is_running(false)
{
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      log_sdl_error(std::cout, "SDL_Init");
      // TODO: Improve this
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

app::~app()
{
   SDL_Quit();
}

void app::load_program(std::filesystem::path program_filepath)
{
   m_emulator.load_program(program_filepath);
}

void app::run()
{
   m_is_running = true;
   // TODO: Make this only execute at 60Hz, so 60 cycle executions per second
   while (m_is_running)
   {
      // Run a cycle of the chip8 cpu - executes a single opcode
      m_emulator.run_cycle();

      // Check for any input and set any key presses here
      while (SDL_PollEvent(&m_poll_event) != 0)
      {
         m_is_running = !(m_poll_event.type == SDL_QUIT);

         if (m_poll_event.type == SDL_KEYDOWN)
         {
            for (uint8_t i = 0; i < 16; ++i)
            {
               if (m_poll_event.key.keysym.sym == key_map[i])
               {
                  m_emulator.set_keys(i, true);
               }
            }
         }
         if (m_poll_event.type == SDL_KEYUP)
         {
            for (uint8_t i = 0; i < 16; ++i)
            {
               if (m_poll_event.key.keysym.sym == key_map[i])
               {
                  m_emulator.set_keys(i, false);
               }
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
      }
   }
}
