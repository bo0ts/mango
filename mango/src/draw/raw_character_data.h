#include "../core/mango_opengl.h"

#ifndef MANGO_RAW_CHARACTER_DATA
#define MANGO_RAW_CHARACTER_DATA

namespace Mango{
  namespace Draw{
    extern GLfloat raw_vertices[];
    extern int ord_map[][3];

    extern GLfloat row_min_height;
    extern GLfloat row_max_height;
// define RAW_VERTICES_SIZE 33760

  } // Draw
} // Mango

#endif // MANGO_RAW_CHARACTER_DATA
