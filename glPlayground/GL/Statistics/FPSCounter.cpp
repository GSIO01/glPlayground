#include "FPSCounter.h"
#include "../../Tools/Log/Logger.h"

namespace GL
{
  namespace Statistics
  {
    void FPSCounter::AddFrame()
    {
      s_Instance._frames++;

      if(s_Instance._firstRun)
      {
        s_Instance._lastTimePoint = std::chrono::steady_clock::now();
        s_Instance._firstRun = false;
        return;
      }

      auto TimeElapsed = std::chrono::steady_clock::now() - s_Instance._lastTimePoint;
      if(std::chrono::duration_cast<std::chrono::milliseconds>(TimeElapsed).count() >= 1000)
      {
        if(s_Instance._liveLogging)
        {
          LOG_INFO(std::to_string(s_Instance._frames) + " FPS");
        }

        s_Instance._averagsFPS = (s_Instance._averagsFPS + double(s_Instance._frames)) / 2;

        s_Instance._frames = 0;
        s_Instance._lastTimePoint = std::chrono::steady_clock::now();
      }
    }

    void FPSCounter::LogStatistics()
    {
      LOG_INFO("Average FPS: " + std::to_string(s_Instance._averagsFPS));
    }

    void FPSCounter::EnableLiveStatistics(bool Enable)
    {
      s_Instance._liveLogging = Enable;
    }
  }
}
