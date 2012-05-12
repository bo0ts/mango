/*
 Copyright (c) 2011 Amos Joshua
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#include <mango/draw/draw.h>
#include "math.h"

namespace Mango{
  namespace Draw{
    void line(Mango::Core::Vector &v1, Mango::Core::Vector &v2){
      glBegin(GL_LINES);
      glVertex3f(v1[0], v1[1], v1[2]);
      glVertex3f(v2[0], v2[1], v2[2]);
      glEnd();
    }

    void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
      glBegin(GL_LINES);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
      glEnd();
    }

    void line(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2){
      glBegin(GL_LINES);
      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);
      glEnd();
    }

    void rectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, bool filled){
      int style = (filled ? GL_POLYGON : GL_LINE_LOOP);
      
      glBegin(style);
      glVertex2f(x1, y1);
      glVertex2f(x1, y2);
      glVertex2f(x2, y2);
      glVertex2f(x2, y1);      
      glEnd();

      if (filled){
	glBegin(style);
	glVertex2f(x2, y1);      
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);
	glEnd();
      }
    }

    void rectangle(Mango::Core::Vector &v1, Mango::Core::Vector &v2, bool filled){
      rectangle(v1[0], v1[1], v2[0], v2[1], filled);
    }

    void circle(GLfloat x, GLfloat y, double r, bool filled, int sides){
      int style = (filled ? GL_POLYGON : GL_LINE_LOOP);
      int i;

      glBegin(style);
      for (i = 0; i < sides; i += 1){
	glVertex2f(x + r*cos(2*3.14159*((float)i)/sides), y + r*sin(2*3.14159*((float)i)/sides));
      }
      glEnd();

      if (filled){
	glBegin(style);
	for (i = sides; i > 0; i -= 1){
	  glVertex2f(x + r*cos(2*3.14159*((float)i)/sides), y + r*sin(2*3.14159*((float)i)/sides));
	}
	glEnd();
      }
    }

    void circle(Mango::Core::Vector &v1, double r, bool filled, int sides){
      circle(v1[0], v1[1], r, filled, sides);
    }

    void letter(char letter){
      int i, letter_index, letter_start, letter_length, v_index;
      GLfloat letter_width, xoffset, yoffset;
      
      letter_index = (int)letter;
      if ( (letter_index < 0) || (letter_index > 127)){
	return;
      }

      //ord_map(letter_index, letter_start, letter_length);
      letter_start = ord_map[letter_index][0];
      letter_length = ord_map[letter_index][1];
      letter_width = (float)ord_map[letter_index][2] / 1000.0;
      //      std::cout << "drawing letter " << letter << "that starts at with length: " << letter_start << ", " << letter_length << std::endl;
      if (letter_start == -1){
	return;
      }

      xoffset = -0.9;
      yoffset = 0;
      if (letter == '1'){
	xoffset += -0.2;
      }
      else if (letter == 'q'){
	xoffset += 0.87;
	yoffset = -0.555;
      }
      else if (letter == '*'){
	xoffset += 0.43;
	yoffset = -0.95;      
      }
      
      glBegin(GL_TRIANGLES);
      for (i = 0; i < letter_length; i += 6){
	v_index = letter_start + i;
	//std::cout << "rendering v" << i << " at " << raw_vertices[v_index] << ", " <<  raw_vertices[v_index+1] << std::endl;
	//std::cout << "rendering v" << i + 1 << " at " << raw_vertices[v_index+2] << ", " <<  raw_vertices[v_index+3] << std::endl;
	//std::cout << "rendering v" << i + 2 << " at " << raw_vertices[v_index+4] << ", " <<  raw_vertices[v_index+5] << std::endl;

	glVertex2f(raw_vertices[v_index] + xoffset, raw_vertices[v_index+1] + yoffset);
	glVertex2f(raw_vertices[v_index+2] + xoffset, raw_vertices[v_index+3] + yoffset);
	glVertex2f(raw_vertices[v_index+4] + xoffset, raw_vertices[v_index+5] + yoffset);

	glVertex2f(raw_vertices[v_index+4] + xoffset, raw_vertices[v_index+5] + yoffset);
	glVertex2f(raw_vertices[v_index+2] + xoffset, raw_vertices[v_index+3] + yoffset);
	glVertex2f(raw_vertices[v_index] + xoffset, raw_vertices[v_index+1] + yoffset);
      }
      glEnd();
      glTranslated(letter_width, 0, 0);
    }

    void text(GLfloat x, GLfloat y, const char *str, GLfloat scale, GLfloat character_spacing){
      int i, slen;
      if (scale == 0){
	throw Mango::Core::ValueError("Mango::Draw", "text", "scale cannot be zero");
      }

      glPushMatrix();      
      glTranslated(x, y, 0);
      glScaled(scale, scale, scale);      
      for (i = 0; true; i += 1){
	if (str[i] == '\0'){
	  break;
	}
	Draw::letter(str[i]);
	glTranslated(character_spacing, 0, 0);
      }
      glPopMatrix();
    }

    void textDimensions(const char *str, GLfloat *width, GLfloat *min_height, GLfloat *max_height, GLfloat scale, GLfloat character_spacing){
      int i, letter_index;
      GLfloat w, letter_width;
	    
      if (width != NULL){
	w = 0;
	for (i = 0; true; i += 1){
	  if (str[i] == '\0'){
	    break;
	  }
	  
	  letter_index = (int)str[i];
	  if ( (letter_index < 0) || (letter_index > 127) || (ord_map[letter_index][0] == -1)){
	    continue;
	  }	  
	  
	  letter_width = (GLfloat)ord_map[letter_index][2] / 1000.0;
	  w += letter_width + character_spacing;
	}
	*width = w;
      }

      if (min_height != NULL){
	*min_height = row_min_height;
      }
      
      if (max_height != NULL){
	*max_height = row_max_height;
      }      
    }
  } // Draw	
} // Mango


