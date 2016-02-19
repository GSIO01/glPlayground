#pragma once

#include <string>
#include "DataBuffer.h"

namespace Tools
{
  class FileLoader
  {
  public:
    FileLoader() = delete;

    static DataBuffer Load(const std::string& path);
  };
}
