#include "core.h"


#ifndef MANGO_CORE_GROUP
#define MANGO_CORE_GROUP



namespace Mango{
  namespace Core{
    
    class Group: public Object, public ObjectContainer{
    public:
      Group();
      ~Group();
      
      virtual const char *objectType() const{
	return "Group";
      }
      
      std::vector<Object*> members;
      
      bool add(Object *new_member);
      bool remove(Object* bad_member);
      void removeAt(int index);
      bool includes(Object* suspect_member);
      
      
      inline Object* operator[](int i){
	if (i < 0 || i > size()){
	  throw IndexError(objectType(), "[]", "Index out of bounds");
	}
	return members[i];
      }
      
      int size();
      
      virtual void removeBasicObject(Object *object_to_remove, int BOCT_ID);
      
      virtual void executeRenderEvents();
      virtual void executeDrawEvents();
      virtual void executePreStepEvents();
      virtual void executeStepEvents();
      virtual void executePostStepEvents();		        
      virtual void executeInputEvents(inputEvent &event);
      
    protected:
      static int BOC_TYPE_ID;
      virtual void render();
      virtual void draw();
      virtual void pre_step();
      virtual void step();
      virtual void post_step();
      virtual void input(inputEvent &event);
      
    };
    
  } // Core
} // Mango

#endif // MANGO_CORE_GROUP


