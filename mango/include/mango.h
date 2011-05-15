#include "config.h"
#include "core/core.h"
#include "core/triangle.h"
#include "draw/draw.h"
#include <stdio.h>

#ifndef MANGO
#define MANGO 

namespace Mango{  
  char *full_version_string();
	
  namespace Core{
  }

  /**
   * Initialize the Mango environment. This should be called at the
   * beginning of every Mango simulation. Normally it populates the globals
   * GlobalFrame, Engine, Keyboard, Mouse, Camera and View, as well as
   * setting their properties. If setup_default_environment is false
   * these globals will not be instantiated, and it is the developer's
   * responsibility to do so.
   */
  void initialize(bool setup_default_environment = true);

  /**
   * Tears down the Mango environment. Normally, it destroys the
   * globals GlobalFrame, Engine, Keyboard, Mouse, Camera and View. If
   * teardown_default_environment is false these globals will not be
   * destroyed, and it is the developer's responsibility to make sure
   * no memory is leaked as a result.
   */
  void finalize(bool teardown_default_environment = true);

  typedef Core::Vector Vector;
}

#endif // MANGO

