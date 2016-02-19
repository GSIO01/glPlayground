#pragma once

#ifdef _MSC_VER

#include "Base.h"

namespace Tools
{
  namespace Log
  {
    namespace Target
    {
      class DebugOutput final : public Base
      {
      public:
        explicit DebugOutput() = default;
        ~DebugOutput() = default;

        void Log(const std::string& msg) override;
      };
    }
  }
}

#endif /* _MSC_VER */
