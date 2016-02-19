#include "GLMain.h"
#include "../Tools/Log/Logger.h"

namespace GL
{

  std::function<void()> GLMain::Display;
  std::function<void()> GLMain::StartUp;
  std::function<void()> GLMain::ShutDown;
  std::function<void()> GLMain::Idle;

  Tools::ScreenResolution GLMain::s_Resolution;

  bool GLMain::Init(int argc, char* argv[])
  {
    LOG_INFO("Initializing GL");

    glutInit(&argc, argv);
    glutInitWindowSize(s_Instance.s_Resolution.Width, s_Instance.s_Resolution.Heigth);
    glutCreateWindow(argv[0]);

    glewExperimental = GL_TRUE;
    GLuint err;
    if ((err = glewInit()) != GLEW_OK)
    {
      std::string msg = "glewInit Failed: ";
      msg += reinterpret_cast<char*>(const_cast<GLubyte*>(glewGetErrorString(err)));
      LOG_CRITICAL(msg);
      return false;
    }

    GLint MajorVersion = 0;
    GLint MinorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);

    if (MajorVersion < 4 || (MajorVersion == 4 && MinorVersion < 5))
    {
      std::string msg = "Required version: 4.5. Actual version: ";
      msg += std::to_string(int32_t(MajorVersion)) + "." + std::to_string(int32_t(MinorVersion));
      LOG_CRITICAL("GL version not supported");
      LOG_CRITICAL(msg);
      return false;
    }

    LOG_INFO("GL version: " + std::to_string(MajorVersion) + "." + std::to_string(MinorVersion));

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitContextVersion(4, 5);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    if(!s_Instance.StartUp)
    {
      LOG_CRITICAL("No Init function was set");
      return false;
    }

    s_Instance.StartUp();

    if(!s_Instance.Display)
    {
      LOG_CRITICAL("No Display function was set");
      return false;
    }

    glutIdleFunc(IdleFunctionInternal);
    glutDisplayFunc(DisplayFunctionInternal);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();

    if(s_Instance.ShutDown)
    {
      s_Instance.ShutDown();
    }
    
    return true;
  }

  void GLMain::SetResolution(const Tools::ScreenResolution& ScreenResolution)
  {
    s_Instance.s_Resolution = ScreenResolution;
  }

  void GLMain::DisplayFunctionInternal()
  {
    if(s_Instance.Display)
    {
      s_Instance.Display();
    }
  }

  void GLMain::IdleFunctionInternal()
  {
    if(s_Instance.Idle)
    {
      s_Instance.Idle();
    }
  }
}
