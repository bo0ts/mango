#ifndef WINDOWS
#include <sys/time.h>
#include <unistd.h>
#endif

#ifndef MANGO_CORE_UTILS
#define MANGO_CORE_UTILS

namespace Mango{
  namespace Core{
    int elapsed_time_in_milliseconds();
    void seconds_sleep(float seconds);
  }
}

#endif // MANGO_CORE_UTILS
