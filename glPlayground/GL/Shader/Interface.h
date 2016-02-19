#pragma once
#include <string>
#include <GL/glew.h>

namespace GL
{
  namespace Shader
  {
    enum class EType
    {
      Vertex,
      Fragment,
      TessControl,
      TessEvaluation,
      GeometryShader
    };

    class IObject
    {
    public:
      virtual ~IObject() = default;

      virtual GLuint GetID() const = 0;
      virtual void Delete() = 0;
      virtual bool IsReady() const = 0;

    protected:
      IObject() = default;
    };

    class IShader
    {
    public:
      virtual ~IShader() = default;

      virtual EType GetType() const = 0;
      virtual const std::string& GetFilename() const = 0;

    protected:
      IShader() = default;
    };
  }
}
