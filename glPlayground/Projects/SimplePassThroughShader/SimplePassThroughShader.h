#pragma once

#include "../../GL/GLMain.h"

namespace Projects
{
  namespace SimplePassThroughShader
  {
    class SimplePassThroughShader
    {
    public:
      void Run(int argc, char* argv[]);

    private:
      enum VAO_IDs { Triangles, NumVAOs };
      enum BUffer_IDs { ArrayBuffer, NumBuffers };
      enum Attrib_IDs { vPosition = 0 };

      GLuint _VAOs[NumVAOs];
      GLuint _Buffers[NumBuffers];
      
      static const GLuint NUM_VERTICES = 6;
      static const char* VERTEX_SHADER;
      static const char* FRAGMENT_SHADER;

      const GLfloat _Vertices[NUM_VERTICES][2] =
      {
        { -0.9f , -0.9f  },
        {  0.85f, -0.9f  },
        { -0.9f ,  0.85f },
        {  0.9f , -0.85f },
        {  0.9f ,  0.9f  },
        { -0.85f,  0.9f  }
      };

      void StartUp();
      void ShutDown();
      void Display();
      void Idle();
    };
  }
}
