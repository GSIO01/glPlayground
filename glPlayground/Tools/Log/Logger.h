#pragma once

#include "Interfaces.h"
#include "../Singleton.h"
#include <vector>
#include <filesystem>

#ifdef _DEBUG
#include "Target/DebugOutput.h"
#endif

#define LOG_DEBUG(MSG) Tools::Log::Logger::GetInstance().Log(__FILE__, __FUNCSIG__, __LINE__,  Tools::Log::ELevel::Debug, MSG)
#define LOG_INFO(MSG) Tools::Log::Logger::GetInstance().Log(__FILE__, __FUNCSIG__, __LINE__,  Tools::Log::ELevel::Info, MSG)
#define LOG_WARN(MSG) Tools::Log::Logger::GetInstance().Log(__FILE__, __FUNCSIG__, __LINE__,  Tools::Log::ELevel::Warn, MSG)
#define LOG_ERROR(MSG) Tools::Log::Logger::GetInstance().Log(__FILE__, __FUNCSIG__, __LINE__,  Tools::Log::ELevel::Error, MSG)
#define LOG_CRITICAL(MSG) Tools::Log::Logger::GetInstance().Log(__FILE__, __FUNCSIG__, __LINE__,  Tools::Log::ELevel::Critical, MSG)

namespace Tools
{
  namespace Log
  {
    class Logger final : public ILogger, public Singleton<Logger>
    {
      Logger()
        : _level(ELevel::Warn)
        , _idCounter(0)
        , _binaryPath(SOURCE_ROOT)
      {
#ifdef _DEBUG
        RegisterTarget(std::make_shared<Target::DebugOutput>());
        _level = ELevel::Debug;
#endif
      }

      friend class Singleton<Logger>;

    public:

      ELevel GetLevel() const override { return _level; }
      void SetLevel(ELevel level) override { _level = level; }
      void Log(const std::string& file, const std::string& function, int32_t line, ELevel level, const std::string msg) override;
      int8_t RegisterTarget(const std::shared_ptr<ITarget>& target) override;
      void RemoveTarget(int8_t id) override;

    private:
      ELevel _level;
      std::vector<std::shared_ptr<ITarget> > _targets;
      int8_t _idCounter;
      std::experimental::filesystem::path _binaryPath;
    };
  }
}
