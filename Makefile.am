## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
#AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = 
bin_PROGRAMS = 
noinst_PROGRAMS = 
noinst_LTLIBRARIES =

if BUILD_MANGO
  lib_LTLIBRARIES += libmango.la
  libmango_la_SOURCES = mango/include/mango.h mango/src/mango.cpp \
                     mango/include/core/core.h mango/src/core/core.cpp \
		     mango/src/core/vector.h \
	             mango/src/core/matrix.h \
		     mango/src/core/constants.h \
		     mango/include/core/error.h mango/src/core/error.cpp \
	             mango/include/core/input.h mango/src/core/input.cpp \
                     mango/include/core/triangle.h mango/src/core/triangle.cpp \
	             mango/include/core/utils.h mango/src/core/utils.cpp \
                     mango/include/core/frame.h mango/src/core/frame.cpp \
	             mango/include/draw/draw.h mango/src/draw/draw.cpp \
		     mango/include/draw/raw_character_data.h mango/src/draw/raw_character_data.cpp

  libmango_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libmango_la_CXXFLAGS = "-I@MANGODIR@/include"
endif

if BUILD_MANGO_ON_GLUT
  lib_LTLIBRARIES += libmong.la
  libmong_la_SOURCES = mango_on_glut/include/mango_on_glut.h mango_on_glut/src/mango_on_glut.cpp

  libmong_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libmong_la_CXXFLAGS = -I@MANGODIR@/include -I@MANGO_ON_GLUTDIR@/include
endif

if BUILD_GEOMETRY
  lib_LTLIBRARIES += libgeometry.la
  libgeometry_la_SOURCES = geometry/include/geometry.h geometry/src/geometry.cpp

  libgeometry_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libgeometry_la_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include
endif

if BUILD_SAMPLES
  noinst_PROGRAMS += bouncing_ball
  bouncing_ball_SOURCES = @MANGO_ON_GLUTDIR@/sample/hello_bouncing_ball.cpp
  bouncing_ball_LDFLAGS = -L.libs -lmango -lgeometry -lmong $(GL_FRAMEWORK) $(GLUT_FRAMEWORK)
  bouncing_ball_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include -I@MANGO_ON_GLUTDIR@/include
endif

if BUILD_MANGOPY
  lib_LTLIBRARIES += libmangopy.la
  libmangopy_la_SOURCES = mangopy/src/mangopy.cpp \
	                  mangopy/src/mangopy_core.cpp \
	                  mangopy/src/mangopy_frame.cpp \
	                  mangopy/src/mangopy_vector.cpp \
	                  mangopy/src/mangopy_matrix.cpp \
	                  mangopy/src/mangopy_pyengine.cpp \
	                  mangopy/src/mangopy_triangle.cpp \
	                  mangopy/src/mangopy_camera.cpp \
	                  mangopy/src/mangopy_keyboard.cpp \
	                  mangopy/src/mangopy_mouse.cpp \
	                  mangopy/src/mangopy_input_event.cpp \
	                  mangopy/src/mangopy_opengl.cpp \
	                  mangopy/src/mangopy_draw.cpp \
	                  mangopy/src/mangopy_core_module.cpp \
	                  mangopy/src/mangopy_pyengine_wrapper.cpp 
  libmangopy_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libmangopy_la_CXXFLAGS = -I@MANGODIR@/include -I@MANGOPYDIR@/include
endif

if BUILD_PYGEOMETRY
  noinst_LTLIBRARIES += Geometry.la
  Geometry_la_SOURCES = pygeometry/src/pygeometry.cpp \
	                     pygeometry/src/pygeometry_colorful_object.cpp \
	                     pygeometry/src/pygeometry_box.cpp \
	                     pygeometry/src/pygeometry_sphere.cpp \
	                     pygeometry/src/pygeometry_cylinder.cpp \
	                     pygeometry/src/pygeometry_shell.cpp \
	                     pygeometry/src/pygeometry_arrow.cpp \
	                     pygeometry/src/pygeometry_coordinate_system.cpp \
	                     pygeometry/src/pygeometry_vertex_array.cpp \
	                     pygeometry/src/pygeometry_circle.cpp \
	                     pygeometry/src/pygeometry_ngon.cpp \
	                     pygeometry/src/pygeometry_rectangle.cpp
  Geometry_la_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include -I@MANGOPYDIR@/include -fpic 
  Geometry_la_LDFLAGS = -module -L.libs -lmangopy -lgeometry -lmango  $(GL_FRAMEWORK) $(PYTHON_FRAMEWORK) $(OPENGL_LINK) -shared -no-undefined
endif

if BUILD_MANGOPY_ON_GLUT
  bin_PROGRAMS += mango
  mango_SOURCES = @MANGOPY_ON_GLUTDIR@/src/mangopy_on_glut.cpp
  mango_LDFLAGS = -L.libs -lmong -lmangopy -lmango $(GL_FRAMEWORK) $(GLUT_FRAMEWORK) $(PYTHON_FRAMEWORK)
  mango_CXXFLAGS = -I@MANGODIR@/include -I@MANGO_ON_GLUTDIR@/include -I@MANGOPYDIR@/include
endif


install-data-hook:
	mkdir -p $(DESTDIR)$(docdir)/
	mkdir -p $(DESTDIR)$(scriptdir)/
	mkdir -p $(DESTDIR)$(sampledir)/
	cp -R $(srcdir)/doc/build/html/* $(DESTDIR)$(docdir)/
	cp -L $(builddir)/.libs/Geometry.so $(DESTDIR)$(scriptdir)/Geometry.so
	cp -R $(srcdir)/mangopy_on_glut/sample/*.py $(DESTDIR)$(sampledir)/

install-exec-hook:
	mkdir -p $(DESTDIR)$(bindir)/
	cp $(builddir)/mango $(DESTDIR)$(bindir)/mango
	cp -R $(srcdir)/python-redist/* $(DESTDIR)$(bindir)/
	ln -s $(DESTDIR)$(bindir)/mango /usr/local/bin/mango

## Define the list of public header files and their install location.  The
## nobase_ prefix instructs Automake to not strip the directory part from each
## filename, in order to avoid the need to define separate file lists for each
## installation directory.  This only works if the directory hierarchy in the
## source tree matches the hierarchy at the install location, however.
#example_includedir = $(includedir)/example-$(EXAMPLE_APIa_VERSION)
#nobase_example_include_HEADERS = example.h \
#                                 example/something.h \
#                                 example/sub/sub.h

## The generated configuration header is installed in its own subdirectory of
## $(libdir).  The reason for this is that the configuration information put
## into this header file describes the target platform the installed library
## has been built for.  Thus the file must not be installed into a location
## intended for architecture-independent files, as defined by the Filesystem
## Hierarchy Standard (FHS).
## The nodist_ prefix instructs Automake to not generate rules for including
## the listed files in the distribution on 'make dist'.  Files that are listed
## in _HEADERS variables are normally included in the distribution, but the
## configuration header file is generated at configure time and should not be
## shipped with the source tarball.
#example_libincludedir = $(libdir)/example-$(EXAMPLE_API_VERSION)/include
#nodist_example_libinclude_HEADERS = exampleconfig.h

## Install the generated pkg-config file (.pc) into the expected location for
## architecture-dependent package configuration information.  Occasionally,
## pkg-config files are also used for architecture-independent data packages,
## in which case the correct install location would be $(datadir)/pkgconfig.
#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = example-$(EXAMPLE_API_VERSION).pc

## Define an independent executable script for inclusion in the distribution
## archive.  However, it will not be installed on an end user's system due to
## the noinst_ prefix.
#dist_noinst_SCRIPTS = autogen.sh
