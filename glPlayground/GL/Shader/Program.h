#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "VertexShader.h"
#include <memory>

namespace GL
{
  namespace Shader
  {
    class Program : public IObject
    {
    public:
      explicit Program(const std::string& name);
      ~Program();

      void AddShader(const std::shared_ptr<IShader>& shader);
      void Use();

      GLuint GetID() const override { return _program; }
      void Delete() override;
      bool IsReady() const override { return _program != 0 && _linked; }
      const std::string& GetName() const { return _name; }

    private:
      GLuint _program;
      std::string _name;
      std::vector<std::shared_ptr<IShader> > _shaders;
      bool _linked;
    };
  }
}
