#include "core.h"

#ifndef MANGO_CORE_TRIANGLE
#define MANGO_CORE_TRIANGLE

namespace Mango{
  namespace Core{
		
    /**
     * A simple triangle object.
     * A simple object that derives from basicObject and renders an equilateral triangle
     * of a given size. It is the only core class that implements a render event and is
     * intended for testing purposes.
     */
    class Triangle : public Object{
    public:
      Triangle();
      ~Triangle();
		
      virtual const char *objectType() const{
	return "Triangle";
      }
		
      void setSize(GLfloat size);
		
      GLfloat size();
		
      virtual void render();
    protected:
      GLfloat tsize;		
    };
		
  } // Core
} // Mango

#endif // MANGO_CORE_TRIANGLE

