#include <cstdlib>
#include <cstdint>

#include "Tools/Log/Logger.h"
#include "Projects/SimplePassThroughShader/SimplePassThroughShader.h"

int32_t main(int32_t argc, char* argv[])
{
  LOG_INFO("Initializing glPlayground");

  Projects::SimplePassThroughShader::SimplePassThroughShader Project;
  Project.Run(argc, argv);

  return EXIT_SUCCESS;
}
