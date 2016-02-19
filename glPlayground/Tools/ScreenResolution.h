#pragma once

#include "Size.h"

namespace Tools
{
  class ScreenResolution : public Size<int>
  {
  public:
    ScreenResolution()
      : Size<int>(512, 512)
    {
    }

    ScreenResolution(int width, int height)
      : Size<int>(width, height)
    {
    }
  };
}
