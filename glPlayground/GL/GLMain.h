#pragma once

#include "../Tools/Singleton.h"
#include <functional>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../Tools/ScreenResolution.h"

namespace GL
{
  class GLMain : public Tools::Singleton<GLMain>
  {
    friend class Tools::Singleton<GLMain>;

    GLMain() = default;

  public:
    static bool Init(int argc, char* argv[]);

    static void SetResolution(const Tools::ScreenResolution& Resolution);

    static std::function<void()> Display;
    static std::function<void()> StartUp;
    static std::function<void()> ShutDown;
    static std::function<void()> Idle;

  protected:
    ~GLMain() = default;

    static void DisplayFunctionInternal();
    static void IdleFunctionInternal();
    static Tools::ScreenResolution s_Resolution;
  };
}
