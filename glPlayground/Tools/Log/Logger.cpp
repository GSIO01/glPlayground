#include "Logger.h"
#include <algorithm>
#include <filesystem>
#include "../ExtFilesystem.h"

namespace Tools
{
  namespace Log
  {
    void Logger::Log(const std::string& file, const std::string& function, int32_t line, ELevel level, const std::string msg)
    {
      if(level < _level)
      {
        return;
      }

      std::experimental::filesystem::path filepath(file);
      std::string message;
      message += LEVEL_STRINGS[int8_t(level)];
      message += " - " + make_relative(_binaryPath, filepath).string() + ":" + function + ":" + std::to_string(line) + " - " + msg;

      for(const auto& target : _targets)
      {
        target->Log(message);
      }
    }

    int8_t Logger::RegisterTarget(const std::shared_ptr<ITarget>& target)
    {
      for(const auto& t : _targets)
      {
        if(target == t)
        {
          return t->GetID();
        }
      }

      target->SetID(_idCounter);
      _idCounter++;
      _targets.push_back(target);

      return target->GetID();
    }

    void Logger::RemoveTarget(int8_t id)
    {
      std::remove_if(_targets.begin(), _targets.end(), [&id](const std::shared_ptr<ITarget>& target) -> bool { return id == target->GetID(); });
    }

  }
}
