#include "FileLoader.h"
#include <cstdio>
#include "Log/Logger.h"

namespace Tools
{
  DataBuffer FileLoader::Load(const std::string& path)
  {
    FILE* file = nullptr;

    fopen_s(&file, path.c_str(), "r");
    if(!file)
    {
      LOG_ERROR("Failed to open file: " + path);
      return DataBuffer();
    }

    fseek(file, 0, SEEK_END);
    auto len = ftell(file);
    fseek(file, 0, SEEK_SET);

    DataBuffer buffer(len+1);

    fread(buffer.GetWriteableData(), len, 1, file);
    fclose(file);

    static_cast<char*>(buffer.GetWriteableData())[len] = 0;

    return buffer;
  }
}
