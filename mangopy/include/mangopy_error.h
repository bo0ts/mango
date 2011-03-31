#include "mango.h"
#include "core/error.h"

#ifndef MANGOPY_ERROR
#define MANGOPY_ERROR

namespace MangoPy {
  class ScriptError  : public Mango::Core::Error{
  public:
    ScriptError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Mango::Core::Error(origObjectType, originatingMethodName, m){
    }

        
    virtual const char *objectType() const{
      return "PythonScriptError";
    }
    
    //virtual void trace() const throw();
  };
}

#endif // MANGOPY_ERROR




