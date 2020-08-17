#pragma once

#include <chrono>

namespace chip8
{
   class clock
   {
   public:
      clock(float frequency_hz);
      bool tick();
      void reset();
      void reset(float frequency_hz);

   private:
      std::chrono::duration<uint64_t, std::nano> m_duration;
      std::chrono::high_resolution_clock::time_point m_offset;
   };
}