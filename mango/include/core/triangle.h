#include "core.h"

#ifndef MANGO_CORE_TRIANGLE
#define MANGO_CORE_TRIANGLE

namespace Mango{
  namespace Core{
		
    /**
     * A colorful, equilateral triangle. This is the only object in
     * the core library that implements a render event, and as such is
     * useful to test Mango independently of other modules like
     * Geometry.
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

