#include "SimplePassThroughShader.h"
#include "../../Tools/Log/Logger.h"
#include "../../GL/Shader/VertexShader.h"
#include "../../GL/Shader/FragmentShader.h"
#include "../../GL/Shader/Program.h"
#include "../../GL/Shader/Manager.h"
#include "../../GL/Statistics/FPSCounter.h"
#include "Helper.h"

namespace Projects
{
  namespace SimplePassThroughShader
  {
    const char* SimplePassThroughShader::VERTEX_SHADER = "..\\..\\..\\glPlayground\\Data\\shaders\\vertex\\triangles.vertex";
    const char* SimplePassThroughShader::FRAGMENT_SHADER = "..\\..\\..\\glPlayground\\Data\\shaders\\fragment\\triangles.fragment";

    void SimplePassThroughShader::Run(int argc, char* argv[])
    {
      //GL::Statistics::FPSCounter::EnableLiveStatistics();
      GL::GLMain::StartUp = std::bind(&SimplePassThroughShader::StartUp, this);
      GL::GLMain::ShutDown = std::bind(&SimplePassThroughShader::ShutDown, this);
      GL::GLMain::Display = std::bind(&SimplePassThroughShader::Display, this);
      GL::GLMain::Idle = std::bind(&SimplePassThroughShader::Idle, this);
      GL::GLMain::SetResolution(Tools::ScreenResolution(768, 768));
      GL::GLMain::Init(argc, argv);
    }

    void SimplePassThroughShader::StartUp()
    {
      LOG_INFO("Initializing Scene");

      glGenVertexArrays(NumVAOs, _VAOs);
      glBindVertexArray(_VAOs[Triangles]);

      glGenBuffers(NumBuffers, _Buffers);
      glBindBuffer(GL_ARRAY_BUFFER, _Buffers[ArrayBuffer]);
      glBufferData(GL_ARRAY_BUFFER, sizeof _Vertices, _Vertices, GL_STATIC_DRAW);

      auto vertexShader = std::make_shared<GL::Shader::VertexShader>(VERTEX_SHADER);
      auto fragmentShader = std::make_shared<GL::Shader::FragmentShader>(FRAGMENT_SHADER);
      auto ShaderProgram = std::make_shared<GL::Shader::Program>("Triangles");

      ShaderProgram->AddShader(vertexShader);
      ShaderProgram->AddShader(fragmentShader);
      ShaderProgram->Use();
      GL::Shader::Manager::RegisterProgram(ShaderProgram);

      glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
      glEnableVertexAttribArray(vPosition);
    }

    void SimplePassThroughShader::ShutDown()
    {
      LOG_INFO("Shutdown");
    }

    void SimplePassThroughShader::Display()
    {
      glClear(GL_COLOR_BUFFER_BIT);

      glBindVertexArray(_VAOs[Triangles]);
      glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);

      glFlush();

      GL::Statistics::FPSCounter::AddFrame();
    }

    void SimplePassThroughShader::Idle()
    {
      static auto then = std::chrono::steady_clock::now();
      static auto then2 = std::chrono::steady_clock::now();

      auto now = std::chrono::steady_clock::now();
      if (std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() >= 1)
      {
        then = std::chrono::steady_clock::now();
        glutPostRedisplay();
      }

      if(std::chrono::duration_cast<std::chrono::seconds>(now - then2).count() >= 5)
      {
        then2 = std::chrono::steady_clock::now();
        GL::Statistics::FPSCounter::LogStatistics();
      }
    }
  }
}
