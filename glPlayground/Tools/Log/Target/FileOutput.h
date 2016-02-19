#pragma once

#include <cstdio>

#include "Base.h"

namespace Tools
{
  namespace Log
  {
    namespace Target
    {
      class FileOutput final : public Base
      {
      public:
        explicit FileOutput(const std::string& path);
        ~FileOutput();

        void Log(const std::string& msg) override;

      private:
        FILE* _file;

        void Init(const std::string& path);
      };
    }
  }
}
