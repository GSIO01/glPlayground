#include "DebugOutput.h"

#ifdef _MSC_VER

#include <windows.h>
#include <WinBase.h>

namespace Tools
{
  namespace Log
  {
    namespace Target
    {
      void DebugOutput::Log(const std::string& msg)
      {
        auto copy = msg;
        copy += "\n";

        OutputDebugString(copy.c_str());
      }
    }
  }
}

#endif /* _MSC_VER */
