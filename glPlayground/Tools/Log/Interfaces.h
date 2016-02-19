#pragma once
#include <string>
#include <memory>


namespace Tools
{
  namespace Log
  {
    enum class ELevel : int8_t
    {
      Debug,
      Info,
      Warn,
      Error,
      Critical
    };

    static const char* LEVEL_STRINGS[] =
    {
      "DEBUG",
      "INFO",
      "WARN",
      "ERROR",
      "CRITICAL",
      nullptr
    };

    class ITarget
    {
    public:
      virtual ~ITarget() = default;

      virtual void Log(const std::string& msg) = 0;
      virtual int8_t GetID() const = 0;
      virtual void SetID(int8_t id) = 0;

    protected:
      ITarget() = default;
    };

    class ILogger
    {
    public:
      virtual ~ILogger() = default;

      virtual ELevel GetLevel() const = 0;
      virtual void SetLevel(ELevel level) = 0;
      virtual void Log(const std::string& file, const std::string& function, int32_t line, ELevel level, const std::string msg) = 0;
      virtual int8_t RegisterTarget(const std::shared_ptr<ITarget>& target) = 0;
      virtual void RemoveTarget(int8_t id) = 0;

    protected:
      ILogger() = default;
    };
  }
}
