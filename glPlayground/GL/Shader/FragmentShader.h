#pragma once
#include "VertexShader.h"

namespace GL
{
  namespace Shader
  {
    class FragmentShader : public IShader, public IObject
    {
    public:
      explicit FragmentShader(const std::string& path);
      virtual ~FragmentShader();

      GLuint GetID() const override { return _shader; }
      void Delete() override;
      bool IsReady() const override { return _shader != 0; }
      EType GetType() const override { return EType::Fragment; }
      const std::string& GetFilename() const override { return _filename; }

    private:
      GLuint _shader;
      std::string _filename;
    };
  }
}
