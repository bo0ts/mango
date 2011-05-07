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
script_LTLIBRARIES =
include_HEADERS = 
includecore_HEADERS =
includedraw_HEADERS =
if BUILD_MANGO
  lib_LTLIBRARIES += libmango.la
  libmango_la_SOURCES = mango/include/mango.h mango/src/mango.cpp \
                     mango/include/core/core.h mango/src/core/core.cpp \
		     mango/include/core/vector.h \
	             mango/include/core/matrix.h \
		     mango/include/core/constants.h \
		     mango/include/core/error.h mango/src/core/error.cpp \
	             mango/include/core/input.h mango/src/core/input.cpp \
                     mango/include/core/triangle.h mango/src/core/triangle.cpp \
	             mango/include/core/utils.h mango/src/core/utils.cpp \
                     mango/include/core/frame.h mango/src/core/frame.cpp \
	             mango/include/draw/draw.h mango/src/draw/draw.cpp \
		     mango/include/draw/raw_character_data.h mango/src/draw/raw_character_data.cpp

  libmango_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libmango_la_CXXFLAGS = "-I@MANGODIR@/include"
  include_HEADERS += $(top_srcdir)/mango/include/*.h
  includecore_HEADERS += $(top_srcdir)/mango/include/core/*.h
  includedraw_HEADERS += $(top_srcdir)/mango/include/draw/*.h
endif

if BUILD_MANGO_ON_GLUT
  lib_LTLIBRARIES += libmong.la
  libmong_la_SOURCES = mango_on_glut/include/mango_on_glut.h mango_on_glut/src/mango_on_glut.cpp

  libmong_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libmong_la_CXXFLAGS = -I@MANGODIR@/include -I@MANGO_ON_GLUTDIR@/include

  include_HEADERS += $(top_srcdir)/mango_on_glut/include/*.h
endif

if BUILD_GEOMETRY
  lib_LTLIBRARIES += libgeometry.la
  libgeometry_la_SOURCES = geometry/include/geometry.h geometry/src/geometry.cpp

  libgeometry_la_LDFLAGS = -static  $(MANGO_LIB_VERSION)
  libgeometry_la_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include

  include_HEADERS += $(top_srcdir)/geometry/include/*.h
endif

if BUILD_SAMPLES
  noinst_PROGRAMS += bouncing_ball
  bouncing_ball_SOURCES = @MANGO_ON_GLUTDIR@/sample/hello_bouncing_ball.cpp
  bouncing_ball_LDFLAGS = -L.libs -lmango -lgeometry -lmong $(GL_FRAMEWORK) $(GLUT_FRAMEWORK)
  bouncing_ball_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include -I@MANGO_ON_GLUTDIR@/include

  noinst_LTLIBRARIES += Solids.la
  Solids_la_SOURCES = mangopy/samples/solids/pysolids.cpp \
		      mangopy/samples/solids/pytetrahedron.cpp \
	              mangopy/samples/solids/pytetrahedron.h \
	  	      mangopy/samples/solids/tetrahedron.h
  Solids_la_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include -I@MANGOPYDIR@/include -I@PYGEOMETRYDIR@/include -fpic 
  Solids_la_LDFLAGS = -module -L.libs -lmangopy -lgeometry -lmango  $(GL_FRAMEWORK) $(PYTHON_FRAMEWORK) $(OPENGL_LINK) -shared -no-undefined -rpath /nowhere
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
  include_HEADERS += $(top_srcdir)/mangopy/include/*.h
endif

if BUILD_PYGEOMETRY
  script_LTLIBRARIES += Geometry.la
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
  Geometry_la_CXXFLAGS = -I@MANGODIR@/include -I@GEOMETRYDIR@/include -I@MANGOPYDIR@/include -I@PYGEOMETRYDIR@/include -fpic 
  Geometry_la_LDFLAGS = -module -L.libs -lmangopy -lgeometry -lmango  $(GL_FRAMEWORK) $(PYTHON_FRAMEWORK) $(OPENGL_LINK) -shared -no-undefined
  include_HEADERS += $(top_srcdir)/pygeometry/include/*.h
endif

if BUILD_MANGOPY_ON_GLUT
  bin_PROGRAMS += mango
  mango_SOURCES = @MANGOPY_ON_GLUTDIR@/src/mangopy_on_glut.cpp
  mango_LDFLAGS = -L.libs -lmong -lmangopy -lmango $(GL_FRAMEWORK) $(GLUT_FRAMEWORK) $(PYTHON_FRAMEWORK)
  mango_CXXFLAGS = -I@MANGODIR@/include -I@MANGO_ON_GLUTDIR@/include -I@MANGOPYDIR@/include
endif

include_HEADERS += $(top_builddir)/config.h

dist_script_DATA = $(top_srcdir)/mangopy_on_glut/demo/demo.py
dist_sample_DATA = $(top_srcdir)/mangopy_on_glut/sample/*.py 

install-exec-hook:
	ln -fs $(DESTDIR)$(bindir)/mango /usr/local/bin/mango







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


# --- Docs Data ---

dist_dochtml_DATA = $(top_srcdir)/doc/build/html/*.html \
     $(top_srcdir)/doc/build/html/*.inv \
     $(top_srcdir)/doc/build/html/*.js
dist_dochtml_images_DATA = $(top_srcdir)/doc/build/html/_images/*.png
dist_dochtml_static_DATA = $(top_srcdir)/doc/build/html/_static/*.css \
     $(top_srcdir)/doc/build/html/_static/*.png \
     $(top_srcdir)/doc/build/html/_static/*.mod \
     $(top_srcdir)/doc/build/html/_static/*.css_t~ \
     $(top_srcdir)/doc/build/html/_static/*.js \
     $(top_srcdir)/doc/build/html/_static/*.ico \
     $(top_srcdir)/doc/build/html/_static/*.jpg
dist_dochtmlcpp_DATA = $(top_srcdir)/doc/build/html/cpp/*.html
dist_dochtmlpython_DATA = $(top_srcdir)/doc/build/html/python/*.html
dist_dochtmlsetup_DATA = $(top_srcdir)/doc/build/html/setup/*.html

# --- Python Redistributable Data: libs ---

dist_corelibs_DATA = $(top_srcdir)/python-redist/libs/*.lib \
     $(top_srcdir)/python-redist/libs/*.a

# --- Python Redistributable Data: Lib ---

dist_coreLib_DATA = $(top_srcdir)/python-redist/Lib/*.py \
     $(top_srcdir)/python-redist/Lib/*.pyc
dist_coreLibctypes_DATA = $(top_srcdir)/python-redist/Lib/ctypes/*.py
dist_coreLibctypesmacholib_DATA = $(top_srcdir)/python-redist/Lib/ctypes/macholib/*.py
dist_coreLibctypestest_DATA = $(top_srcdir)/python-redist/Lib/ctypes/test/*.py
dist_coreLibcurses_DATA = $(top_srcdir)/python-redist/Lib/curses/*.py
dist_coreLibdbm_DATA = $(top_srcdir)/python-redist/Lib/dbm/*.py
dist_coreLibdistutils_DATA = $(top_srcdir)/python-redist/Lib/distutils/*.py
dist_coreLibdistutilscommand_DATA = $(top_srcdir)/python-redist/Lib/distutils/command/*.py \
     $(top_srcdir)/python-redist/Lib/distutils/command/*.exe
dist_coreLibdistutilstests_DATA = $(top_srcdir)/python-redist/Lib/distutils/tests/*.py
dist_coreLibemail_DATA = $(top_srcdir)/python-redist/Lib/email/*.py
dist_coreLibemailmime_DATA = $(top_srcdir)/python-redist/Lib/email/mime/*.py
dist_coreLibemailtest_DATA = $(top_srcdir)/python-redist/Lib/email/test/*.py
dist_coreLibemailtestdata_DATA = $(top_srcdir)/python-redist/Lib/email/test/data/*.au \
     $(top_srcdir)/python-redist/Lib/email/test/data/*.txt \
     $(top_srcdir)/python-redist/Lib/email/test/data/*.gif
dist_coreLibencodings_DATA = $(top_srcdir)/python-redist/Lib/encodings/*.py \
     $(top_srcdir)/python-redist/Lib/encodings/*.pyc
dist_coreLibhtml_DATA = $(top_srcdir)/python-redist/Lib/html/*.py
dist_coreLibhttp_DATA = $(top_srcdir)/python-redist/Lib/http/*.py
dist_coreLibidlelib_DATA = $(top_srcdir)/python-redist/Lib/idlelib/*.py \
     $(top_srcdir)/python-redist/Lib/idlelib/*.def \
     $(top_srcdir)/python-redist/Lib/idlelib/*.txt \
     $(top_srcdir)/python-redist/Lib/idlelib/*.bat \
     $(top_srcdir)/python-redist/Lib/idlelib/*.pyw
dist_coreLibidlelibIcons_DATA = $(top_srcdir)/python-redist/Lib/idlelib/Icons/*.gif \
     $(top_srcdir)/python-redist/Lib/idlelib/Icons/*.icns
dist_coreLibimportlib_DATA = $(top_srcdir)/python-redist/Lib/importlib/*.py
dist_coreLibimportlibtest_DATA = $(top_srcdir)/python-redist/Lib/importlib/test/*.py
dist_coreLibimportlibtestbuiltin_DATA = $(top_srcdir)/python-redist/Lib/importlib/test/builtin/*.py
dist_coreLibimportlibtestextension_DATA = $(top_srcdir)/python-redist/Lib/importlib/test/extension/*.py
dist_coreLibimportlibtestfrozen_DATA = $(top_srcdir)/python-redist/Lib/importlib/test/frozen/*.py
dist_coreLibimportlibtestimport__DATA = $(top_srcdir)/python-redist/Lib/importlib/test/import_/*.py
dist_coreLibimportlibtestsource_DATA = $(top_srcdir)/python-redist/Lib/importlib/test/source/*.py
dist_coreLibjson_DATA = $(top_srcdir)/python-redist/Lib/json/*.py
dist_coreLibjsontests_DATA = $(top_srcdir)/python-redist/Lib/json/tests/*.py
dist_coreLiblib2to3_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/*.py \
     $(top_srcdir)/python-redist/Lib/lib2to3/*.txt
dist_coreLiblib2to3fixes_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/fixes/*.py
dist_coreLiblib2to3pgen2_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/pgen2/*.py
dist_coreLiblib2to3tests_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/tests/*.py
dist_coreLiblib2to3testsdata_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/tests/data/*.py
dist_coreLiblib2to3testsdatafixers_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/tests/data/fixers/*.py
dist_coreLiblib2to3testsdatafixersmyfixes_DATA = $(top_srcdir)/python-redist/Lib/lib2to3/tests/data/fixers/myfixes/*.py
dist_coreLiblogging_DATA = $(top_srcdir)/python-redist/Lib/logging/*.py
dist_coreLibmsilib_DATA = $(top_srcdir)/python-redist/Lib/msilib/*.py
dist_coreLibmultiprocessing_DATA = $(top_srcdir)/python-redist/Lib/multiprocessing/*.py
dist_coreLibmultiprocessingdummy_DATA = $(top_srcdir)/python-redist/Lib/multiprocessing/dummy/*.py
dist_coreLibpydoc_data_DATA = $(top_srcdir)/python-redist/Lib/pydoc_data/*.py
dist_coreLibsitepackages_DATA = $(top_srcdir)/python-redist/Lib/site-packages/*.txt
dist_coreLibsqlite3_DATA = $(top_srcdir)/python-redist/Lib/sqlite3/*.py
dist_coreLibsqlite3test_DATA = $(top_srcdir)/python-redist/Lib/sqlite3/test/*.py
dist_coreLibtest_DATA = $(top_srcdir)/python-redist/Lib/test/*.db \
     $(top_srcdir)/python-redist/Lib/test/*.py \
     $(top_srcdir)/python-redist/Lib/test/*.au \
     $(top_srcdir)/python-redist/Lib/test/*.pem \
     $(top_srcdir)/python-redist/Lib/test/*.1 \
     $(top_srcdir)/python-redist/Lib/test/*.vbs \
     $(top_srcdir)/python-redist/Lib/test/*.txt \
     $(top_srcdir)/python-redist/Lib/test/*.pck \
     $(top_srcdir)/python-redist/Lib/test/*.html \
     $(top_srcdir)/python-redist/Lib/test/*.aif \
     $(top_srcdir)/python-redist/Lib/test/*.xml \
     $(top_srcdir)/python-redist/Lib/test/*.out \
     $(top_srcdir)/python-redist/Lib/test/*.tar \
     $(top_srcdir)/python-redist/Lib/test/*.zip
dist_coreLibtestcrashers_DATA = $(top_srcdir)/python-redist/Lib/test/crashers/*.py
dist_coreLibtestdecimaltestdata_DATA = $(top_srcdir)/python-redist/Lib/test/decimaltestdata/*.decTest
dist_coreLibtestleakers_DATA = $(top_srcdir)/python-redist/Lib/test/leakers/*.py \
     $(top_srcdir)/python-redist/Lib/test/leakers/*.txt
dist_coreLibtkinter_DATA = $(top_srcdir)/python-redist/Lib/tkinter/*.py
dist_coreLibtkintertest_DATA = $(top_srcdir)/python-redist/Lib/tkinter/test/*.py
dist_coreLibtkintertesttest_tkinter_DATA = $(top_srcdir)/python-redist/Lib/tkinter/test/test_tkinter/*.py
dist_coreLibtkintertesttest_ttk_DATA = $(top_srcdir)/python-redist/Lib/tkinter/test/test_ttk/*.py
dist_coreLiburllib_DATA = $(top_srcdir)/python-redist/Lib/urllib/*.py
dist_coreLibwsgiref_DATA = $(top_srcdir)/python-redist/Lib/wsgiref/*.py
dist_coreLibxml_DATA = $(top_srcdir)/python-redist/Lib/xml/*.py
dist_coreLibxmldom_DATA = $(top_srcdir)/python-redist/Lib/xml/dom/*.py
dist_coreLibxmletree_DATA = $(top_srcdir)/python-redist/Lib/xml/etree/*.py
dist_coreLibxmlparsers_DATA = $(top_srcdir)/python-redist/Lib/xml/parsers/*.py
dist_coreLibxmlsax_DATA = $(top_srcdir)/python-redist/Lib/xml/sax/*.py
dist_coreLibxmlrpc_DATA = $(top_srcdir)/python-redist/Lib/xmlrpc/*.py
