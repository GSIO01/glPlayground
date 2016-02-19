#include "FileOutput.h"

namespace Tools
{
  namespace Log
  {
    namespace Target
    {
      FileOutput::FileOutput(const std::string& path)
        : _file(nullptr)
      {
        Init(path);
      }

      FileOutput::~FileOutput()
      {
        if(_file != nullptr)
        {
          fclose(_file);
        }
      }

      void FileOutput::Log(const std::string& msg)
      {
        if(_file == nullptr)
        {
          return;
        }

        fputs(msg.c_str(), _file);
      }

      void FileOutput::Init(const std::string& path)
      {
#ifdef _MSC_VER
        fopen_s(&_file, path.c_str(), "a");
#else
        _file = fopen(path.c_str(), "a");
#endif
      }
    }
  }
}
