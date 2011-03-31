#include "mangopy_python.h"
#include <vector>
#include "mango.h"
#include "mangopy_vector.h"


#ifndef MANGOPY_PYENGINE
#define MANGOPY_PYENGINE

#include "mangopy_core.h"

typedef std::pair<Mango::Core::Object *, PyObject *> ObjectPythonEventRecord;



class PythonScriptError : public Mango::Core::Error{
    public:
      PythonScriptError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
      }

      virtual const char *objectType() const{
          return "PythonScriptError";
      }
      //virtual void trace() const throw();
};




class PyEngine : public Mango::Core::CoreEngine, public Mango::Core::ObjectContainer{
    public:
        PyEngine();
        ~PyEngine();

        virtual const char *objectType() const{
            return "PyEngine";
        }

        const char *getObjectEventMethodName(int event_type);

        virtual bool setScriptedEvent(mpy_Object* object, int event_mask);
    	virtual bool removeScriptedEvent(mpy_Object* object, int event_mask);
        virtual bool toggleScriptedEvent(mpy_Object* object, int event_mask);
        virtual bool objectHasScriptedEvent(mpy_Object *object, int event_mask);        

        virtual void removeObject(Mango::Core::Object* object_to_remove, int BOCT_ID);
        
        /*
        virtual bool setEvent(Object* object, int event_type);
        virtual bool removeEvent(Object* object, int event_type);
        */
        
        virtual void executeCallback(mpy_Object *obj, int event_type);


        // Debugging

        void __printPythonEvents(int event_type){
            int size = python_events[event_type].size();
            std::cout << std::endl << "----------------------------------------------------------------" << std::endl;
		    std::cout << "python_events[" << event_type << "] with " << size << "events " << std::endl;
		    for (int i = 0; i < size; i += 1){
		        std::cout << "  " << i << ") python_events[" << event_type << "][ " << i << "] = " << &(python_events[event_type][i]) << std::endl;
		        std::cout << "  " << i << ") python_events[" << event_type << "][ " << i << "].first = " << python_events[event_type][i].first << std::endl;
		        std::cout << "  " << i << ") python_events[" << event_type << "][ " << i << "].second = " << python_events[event_type][i].second << std::endl;
		    }     
		    std::cout << std::endl << "----------------------------------------------------------------" << std::endl;
        }

    protected:

        virtual void evt_render();
        virtual void evt_draw();
        //virtual void evt_pre_step();
        virtual void evt_step();
        //virtual void evt_post_step();
        virtual void evt_input();

        std::vector<ObjectPythonEventRecord> python_events[ENGINE_MAX_EVENT_TYPES];
        static int BOC_TYPE_IDS[ENGINE_MAX_EVENT_TYPES];
};










#endif // MANGOPY_PYENGINE
