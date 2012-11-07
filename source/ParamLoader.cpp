#include "../headers/ParamLoader.h"

ParamLoader* ParamLoader::Instance()
{
  static ParamLoader instance;

  return &instance;
}