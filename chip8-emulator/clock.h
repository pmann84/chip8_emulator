#pragma once

#include <chrono>

namespace chip8
{
   class clock
   {
   public:
      clock(float frequency_hz)
      {
         m_duration = std::chrono::nanoseconds(1000000000 / (uint64_t)frequency_hz);
         m_offset = std::chrono::high_resolution_clock::now();
      }

      bool tick()
      {
         auto now = std::chrono::high_resolution_clock::now();
         if (now - m_offset >= m_duration)
         {
            m_offset += m_duration;
            return true;
         }
         else
         {
            return false;
         }
      }

   private:
      std::chrono::duration<uint64_t, std::nano> m_duration;
      std::chrono::high_resolution_clock::time_point m_offset;
   };
}