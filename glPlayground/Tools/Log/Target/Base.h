#pragma once

#include "../Interfaces.h"

namespace Tools
{
  namespace Log
  {
    namespace Target
    {
      class Base : public ITarget
      {
      public:
        Base() = default;
        ~Base() = default;

        void Log(const std::string&) override { }
        int8_t GetID() const override { return _id; }
        void SetID(int8_t id) override { _id = id; }

      protected:
        int8_t _id;
      };
    }
  }
}
