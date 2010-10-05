#include "utils.h"

namespace Mango{
  namespace Core{
    int elapsed_time_in_milliseconds(){
#ifdef WINDOWS
#error elapsed_time_in_milliseconds not implemented
#else
      struct timeval current_time;
      gettimeofday(&current_time, NULL);
      return  ((current_time.tv_sec) * 1000 + current_time.tv_usec/1000.0) + 0.5;
#endif
    }

    void seconds_sleep(float seconds){
#ifdef WINDOWS
      Sleep(seconds);
#error millisecond_sleep implementation needs to be verified
#else
      usleep((int)(seconds * 1000));
#endif
    }
  }
}
