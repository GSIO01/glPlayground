#pragma once
#include "../../Tools/Singleton.h"
#include <cstdint>
#include <chrono>

namespace GL
{
  namespace Statistics
  {
    class FPSCounter : public Tools::Singleton<FPSCounter>
    {
      friend class Tools::Singleton<FPSCounter>;

      FPSCounter()
        : _frames(0)
        , _averagsFPS(0.0)
        , _firstRun(true)
        , _liveLogging(false)
      {        
      }

    public:
      static void AddFrame();
      static void LogStatistics();
      static void EnableLiveStatistics(bool Enable = true);

    protected:
      ~FPSCounter() = default;

      uint32_t _frames;
      double _averagsFPS;
      std::chrono::time_point<std::chrono::steady_clock> _lastTimePoint;
      bool _firstRun;
      bool _liveLogging;
    };
  }
}
