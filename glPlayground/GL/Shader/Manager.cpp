#include "Manager.h"
#include <algorithm>

namespace GL
{
  namespace Shader
  {
    std::shared_ptr<Program>Manager::GetProgram(const std::string& name)
    {
      if(s_Instance._programs.find(name) != s_Instance._programs.end())
      {
        return s_Instance._programs[name];
      }

      return std::shared_ptr<Program>();
    }

    std::shared_ptr<Program> Manager::GetProgram(GLuint id)
    {
      auto res = std::find_if(s_Instance._programs.begin(), s_Instance._programs.end(), [&id](const auto& pr) -> bool { return id == pr.second->GetID(); });
      if(res == s_Instance._programs.end())
      {
        return std::shared_ptr<Program>();
      }

      return res->second;
    }

    void Manager::DeleteProgram(const std::string& name)
    {
      auto it = s_Instance._programs.find(name);
      if(it != s_Instance._programs.end())
      {
        s_Instance._programs.erase(it);
      }
    }

    void Manager::DeleteProgram(GLuint id)
    {
      auto it = std::find_if(s_Instance._programs.begin(), s_Instance._programs.end(), [&id](const auto& pr) -> bool { return id == pr.second->GetID(); });
      if(it != s_Instance._programs.end())
      {
        s_Instance._programs.erase(it);
      }
    }

    void Manager::UseProgram(const std::string& name)
    {
      if(s_Instance._programs.find(name) != s_Instance._programs.end())
      {
        s_Instance._programs[name]->Use();
      }
    }

    void Manager::UseProgram(GLuint id)
    {
      auto it = std::find_if(s_Instance._programs.begin(), s_Instance._programs.end(), [&id](const auto& pr) -> bool { return id == pr.second->GetID(); });
      if(it != s_Instance._programs.end())
      {
        it->second->Use();
      }
    }

    Manager::~Manager()
    {
      for(const auto& program : _programs)
      {
        program.second->Delete();
      }
    }
  }
}
