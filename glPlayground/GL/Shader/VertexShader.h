#pragma once
#include "Interface.h"
#include <string>
#include <GL/glew.h>

namespace GL
{
  namespace Shader
  {
    class VertexShader : public IShader, public IObject
    {
    public:
      explicit VertexShader(const std::string& Path);
      virtual ~VertexShader();

      EType GetType() const override { return EType::Vertex; }
      bool IsReady() const override { return _shader != 0; }
      const std::string& GetFilename() const override { return _filename; }
      GLuint GetID() const override { return _shader; }
      void Delete() override;

    private:
      GLuint _shader;
      std::string _filename;
    };
  }
}
