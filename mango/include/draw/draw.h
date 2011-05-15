#include "../core/core.h"
#include <vector>
#include "raw_character_data.h"

#ifndef MANGO_DRAW
#define MANGO_DRAW

namespace Mango{
  namespace Draw{

    void line(Mango::Core::Vector &v1, Mango::Core::Vector &v2);
    void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    void line(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);

    void rectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, bool filled = false);
    void rectangle(Mango::Core::Vector &v1, Mango::Core::Vector &v2, bool filled = false);

    void circle(GLfloat x, GLfloat y, double r, bool filled = false, int sides = 48);
    void circle(Mango::Core::Vector &v1, double r, bool filled = false, int sides = 48);

    /**
     * Draw the given letter at letter at (0, 0).
     */
    void letter(char letter);

    /**
     * Draw str at (x, y) with the given scale and character
     * spacing. At the moment Mango supports drawing only a subset of
     * the printable characters in the English language. 
     */
    void text(GLfloat x, GLfloat y, const char *str, GLfloat scale = 1.0, GLfloat character_spacing = 0.1);

    /**
     * Calculate the dimensions of str if it were to be drawn at the
     * given scale and character spacing, and assign it to width,
     * min_height and max_height. min_height and max_height are the
     * greatest distances below and above the point at which the text
     * is rendered that str will reach.
     */
    void textDimensions(const char *str, GLfloat *width, GLfloat *min_height = NULL, GLfloat *max_height = NULL, GLfloat scale = 1.0, GLfloat character_spacing = 0.1); 
  } // Draw
} // Mango

#endif // MANGO_DRAW

