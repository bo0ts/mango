#include "Python.h"
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
