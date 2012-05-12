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
#include "mangopy_python.h"
#include "mangopy.h"
#include "pygeometry_colorful_object.h"
#include "pygeometry_box.h"
#include "pygeometry_sphere.h"
#include "pygeometry_cylinder.h"
#include "pygeometry_shell.h"
#include "pygeometry_arrow.h"
#include "pygeometry_coordinate_system.h"
#include "pygeometry_vertex_array.h"
#include "pygeometry_circle.h"
#include "pygeometry_ngon.h"
#include "pygeometry_rectangle.h"

#ifndef MANGOPY_GEOMETRY
#define MANGOPY_GEOMETRY

static PyModuleDef geometry_module_def = {
    PyModuleDef_HEAD_INIT,
    "Geometry",
    "Mango geometry",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_Geometry(void);

#endif // MANGOPY_GEOMETRY
