#pragma once
#include "../../Tools/Singleton.h"
#include <unordered_map>
#include "Program.h"

namespace GL
{
  namespace Shader
  {
    class Manager : public Tools::Singleton<Manager>
    {
      friend Singleton<Manager>;

      Manager()
      {        
      }

    public:
      static void RegisterProgram(const std::shared_ptr<Program>& Program) { s_Instance._programs[Program->GetName()] = Program; }
      static std::shared_ptr<Program>GetProgram(const std::string& name);
      static std::shared_ptr<Program> GetProgram(GLuint id);
      static void DeleteProgram(const std::string& name);
      static void DeleteProgram(GLuint id);
      static void UseProgram(const std::string& name);
      static void UseProgram(GLuint id);

      ~Manager();

    private:
      std::unordered_map<std::string, std::shared_ptr<Program> > _programs;
    };
  }
}
