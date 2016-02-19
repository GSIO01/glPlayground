#include "FragmentShader.h"
#include <filesystem>
#include "../../Tools/FileLoader.h"
#include "../../Tools/Log/Logger.h"

namespace GL
{
  namespace Shader
  {
    FragmentShader::FragmentShader(const std::string& path)
      : _shader(0)
      , _filename(path)
    {
      std::experimental::filesystem::path filePath = path;

      if(!exists(filePath) || !is_regular_file(filePath))
      {
        LOG_ERROR(path + " does not or exist or is not a regular file");
        return;
      }

      auto buffer = Tools::FileLoader::Load(path);
      if(buffer.GetSize() == 0)
      {
        return;
      }

      _shader = glCreateShader(GL_FRAGMENT_SHADER);

      if(_shader == 0)
      {
        LOG_ERROR("Shader object creation failed for: " + path);
        return;
      }
      LOG_INFO("Created shader object: " + std::to_string(_shader) + " (" + path + ")");

      LOG_INFO("Compiling fragment shader: " + std::to_string(_shader));
      auto* src = static_cast<GLchar*>(buffer.GetData());
      glShaderSource(_shader, 1, &src, nullptr);
      glCompileShader(_shader);

      GLint result;
      glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);
      if(result != GL_TRUE)
      {
        char infoLog[1204];
        GLsizei lenght;
        glGetShaderInfoLog(_shader, 1024, &lenght, infoLog);
        LOG_ERROR("Shader compilation failed for: " + std::to_string(_shader));
        LOG_ERROR(infoLog);

        glDeleteShader(_shader);
        _shader = 0;
        return;
      }
    }

    FragmentShader::~FragmentShader()
    {
      FragmentShader::Delete();
    }
    
    void FragmentShader::Delete()
    {
      if(_shader != 0)
      {
        LOG_INFO("Deleting shader object for: " + std::to_string(_shader));
        glDeleteShader(_shader);
        _shader = 0;
      }
    }
  }
}
