#include "core/core.h"
#include "core/triangle.h"
#include "draw/draw.h"
#include <stdio.h>

#ifndef MANGO
#define MANGO 

namespace Mango{  
  double version();
  char *version_string();
	
  namespace Core{
  }
	
  void initialize(bool setup_default_environment = true);
  void finalize(bool teardown_default_environment = true);

  typedef Core::Vector Vector;
}

#endif // MANGO

