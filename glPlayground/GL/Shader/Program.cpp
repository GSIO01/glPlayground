#include "Program.h"
#include "../../Tools/Log/Logger.h"

namespace GL
{
  namespace Shader
  {
    Program::Program(const std::string& name)
      : _program(0)
      , _name(name)
      , _linked(false)
    {
      _program = glCreateProgram();

      if(_program == 0)
      { 
        LOG_ERROR("Failed to create shader program");
        return;
      }

      LOG_INFO("Created shader program: " + std::to_string(_program));
    }

    Program::~Program()
    {
      Program::Delete();
    }

    void Program::AddShader(const std::shared_ptr<IShader>& shader)
    {
      LOG_INFO("Attaching shader: " + shader->GetFilename());
      _shaders.push_back(shader);
      glAttachShader(_program, std::dynamic_pointer_cast<IObject>(shader)->GetID());
    }

    void Program::Use()
    {
      if(_program == 0)
      {
        LOG_WARN("No program was created");
        return;
      }

      if(!_linked)
      {
        LOG_INFO("Linking shader program: " + std::to_string(_program));
        glLinkProgram(_program);

        GLint result;
        glGetProgramiv(_program, GL_LINK_STATUS, &result);
        if(result != GL_TRUE)
        {
          char buffer[1024];
          GLsizei length;
          glGetProgramInfoLog(_program, 1024, &length, buffer);
          LOG_ERROR("Failed to link shader program:");
          LOG_ERROR(buffer);

          glDeleteProgram(_program);
          _program = 0;
          return;
        }

        LOG_INFO("Using shader program: " + std::to_string(_program));
        _linked = true;
      }

      glUseProgram(_program);
    }

    void Program::Delete()
    {
      for (auto& shader : _shaders)
      {
        auto obj = std::dynamic_pointer_cast<IObject>(shader);
        LOG_INFO("Detaching shader object: " + std::to_string(obj->GetID()));
        glDetachShader(_program, obj->GetID());
        obj->Delete();
      }

      if (_program != 0)
      {
        LOG_INFO("Deleting shader program: " + std::to_string(_program));
        glDeleteProgram(_program);
        _program = 0;
      }

      _shaders.clear();
    }
  }
}
