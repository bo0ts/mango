AC_INIT([Mango], esyscmd(git describe | tr -d "\n"), [mangobits@gmail.com], [mango], [http://mangobits.com/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 no-define])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
LT_INIT([])
AC_CONFIG_FILES([Makefile])

# Set default prefix
AC_PREFIX_DEFAULT("/opt/mango/1.0/")
AC_SUBST([scriptdir], "\${exec_prefix}/script")
AC_SUBST([sampledir], "\${exec_prefix}/sample")
AC_SUBST([bindir], "\${exec_prefix}/core")
AC_SUBST([docdir], "\${exec_prefix}/doc")

# Detect host
AC_CANONICAL_HOST
AC_MSG_NOTICE([building on host_vendor $host_vendor])
if test "x$host_vendor" = "xapple"; then
   AC_SUBST([GL_FRAMEWORK], "-framework OpenGL")
   AC_SUBST([GLUT_FRAMEWORK], "-framework GLUT")
   AC_SUBST([PYTHON_FRAMEWORK], "-framework Python")
fi

# Set version constants
AC_SUBST([MANGO_LIB_VERSION], [1:0:0])
AC_SUBST([MANGO_VERSION], [1.0])

# Allow disabling 'mango' component
AC_ARG_ENABLE([mango],
     [  --disable-mango    do not build core mango library],
     [case "${enableval}" in
       yes) build_mango=true ;;
       no)  build_mango=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-mango]) ;;
     esac],[build_mango=true])
AM_CONDITIONAL([BUILD_MANGO], [test x$enableval != x"no"])

# Allow disabling 'mango_on_glut' component
AC_ARG_ENABLE([mango_on_glut],
     [  --disable-mango-on-glut    do not build mango-on-glut library],
     [case "${enableval}" in
       yes) build_mango_on_glut=true ;;
       no)  build_mango_on_glut=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-mango-on-glut]) ;;
     esac],[build_mango_on_glut=true])
AM_CONDITIONAL([BUILD_MANGO_ON_GLUT], [test x$enableval != x"no"])

# Allow disabling 'geometry' component
AC_ARG_ENABLE([geometry],
     [  --disable-geometry    do not build geometry library],
     [case "${enableval}" in
       yes) build_geometry=true ;;
       no)  build_geometry=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-geometry]) ;;
     esac],[build_geometry=true])
AM_CONDITIONAL([BUILD_GEOMETRY], [test x$enableval != x"no"])

# Allow disabling 'mangopy' component
AC_ARG_ENABLE([mangopy],
     [  --disable-mangopy    do not build mangopy library],
     [case "${enableval}" in
       yes) build_mangopy=true ;;
       no)  build_mangopy=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-mangopy]) ;;
     esac],[build_mangopy=true])
AM_CONDITIONAL([BUILD_MANGOPY], [test x$enableval != x"no"])

# Allow disabling 'pygeometry' component
AC_ARG_ENABLE([pygeometry],
     [  --disable-pygeometry    do not build pygeometry library],
     [case "${enableval}" in
       yes) build_pygeometry=true ;;
       no)  build_pygeometry=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-pygeometry]) ;;
     esac],[build_pygeometry=true])
AM_CONDITIONAL([BUILD_PYGEOMETRY], [test x$enableval != x"no"])

# Allow disabling 'mangopy_on_glut' component
AC_ARG_ENABLE([mangopy_on_glut],
     [  --disable-mangopy-on-glut    do not build mangopy-on-glut library],
     [case "${enableval}" in
       yes) build_mangopy_on_glut=true ;;
       no)  build_mangopy_on_glut=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-mangopy-on-glut]) ;;
     esac],[build_mangopy_on_glut=true])
AM_CONDITIONAL([BUILD_MANGOPY_ON_GLUT], [test x$enableval != x"no"])

# Allow disabling 'samples' component
AC_ARG_ENABLE([samples],
     [  --disable-samples    do not build the samples],
     [case "${enableval}" in
       yes) build_samples=true ;;
       no)  build_samples=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --disable-samples]) ;;
     esac],[build_samples=true])
AM_CONDITIONAL([BUILD_SAMPLES], [test x$enableval != x"no"])

# Allow setting path to 'mango' component
AC_ARG_WITH([mango_prefix],
            [AS_HELP_STRING([--with-mango-prefix=[path]],
            [specify path to the subcomponent mango])],
            [mangodir=$withval],
            [mangodir=$srcdir/mango])

# Allow setting path to 'mango_on_glut' component
AC_ARG_WITH([mango_on_glut_prefix],
            [AS_HELP_STRING([--with-mango-on-glut-prefix=[path]],
            [specify path to the subcomponent mango_on_glut])],
            [mango_on_glutdir=$withval],
            [mango_on_glutdir=$srcdir/mango_on_glut])

# Allow setting path to 'geometry' component
AC_ARG_WITH([geometry_prefix],
            [AS_HELP_STRING([--with-geometry-prefix=[path]],
            [specify path to the subcomponent geometry])],
            [geometrydir=$withval],
            [geometrydir=$srcdir/geometry])

# Allow setting path to 'mangopy' component
AC_ARG_WITH([mangopy_prefix],
            [AS_HELP_STRING([--with-mangopy-prefix=[path]],
            [specify path to the subcomponent mangopy])],
            [mangopydir=$withval],
            [mangopydir=$srcdir/mangopy])

# Allow setting path to 'pygeometry' component
AC_ARG_WITH([pygeometry_prefix],
            [AS_HELP_STRING([--with-pygeometry-prefix=[path]],
            [specify path to the subcomponent pygeometry])],
            [pygeometrydir=$withval],
            [pygeometrydir=$srcdir/pygeometry])

# Allow setting path to 'mangopy_on_glut' component
AC_ARG_WITH([mangopy_on_glut_prefix],
            [AS_HELP_STRING([--with-mangopy-on-glut-prefix=[path]],
            [specify path to the subcomponent mangopy_on_glut])],
            [mangopy_on_glutdir=$withval],
            [mangopy_on_glutdir=$srcdir/mangopy_on_glut])


# Allow --enable-debug flag
AC_MSG_CHECKING(whether to enable debugging)
debug_default="yes"
AC_ARG_ENABLE(debug, [  --enable-debug=[no/yes] turn on debugging
                       [default=$debug_default]],, enable_debug=$debug_default)
if test "x$enable_debug" = "xyes"; then
         CXXFLAGS="$CXXFLAGS -g -DDEBUG"
else
  #CFLAGS="$CFLAGS -O3 -ffast-math -mcpu=v8 -mtune=ultrasparc"
  AC_MSG_RESULT(no)
fi


AC_MSG_NOTICE([build mango (at "$mangodir"): $build_mango])
AC_MSG_NOTICE([build mango-on-glut (at "$mango_on_glutdir"): $build_mango_on_glut])
AC_MSG_NOTICE([build geometry (at "$geometrydir"): $build_geometry])
AC_MSG_NOTICE([build mangopy (at "$mangopydir"): $build_mangopy])
AC_MSG_NOTICE([build pygeometry (at "$pygeometrydir"): $build_pygeometry])
AC_MSG_NOTICE([build mangopy_on_glut (at "$mangopy_on_glutdir"): $build_mangopy_on_glut])
AC_MSG_NOTICE([build samples (at "$mango_on_glutdir/samples"): $build_samples])

AC_SUBST([MANGODIR], [$mangodir])
AC_SUBST([MANGO_ON_GLUTDIR], [$mango_on_glutdir])
AC_SUBST([GEOMETRYDIR], [$geometrydir])
AC_SUBST([MANGOPYDIR], [$mangopydir])
AC_SUBST([PYGEOMETRYDIR], [$pygeometrydir])
AC_SUBST([MANGOPY_ON_GLUTDIR], [$mangopy_on_glutdir])


# -- Headers ---

AC_SUBST([includecoredir], "\${exec_prefix}/include/core")
AC_SUBST([includedrawdir], "\${exec_prefix}/include/draw")

# --- Docs Data ---

AC_SUBST([dochtmldir], "\${exec_prefix}/doc/html")
AC_SUBST([dochtml_imagesdir], "\${exec_prefix}/doc/html/_images")
AC_SUBST([dochtml_staticdir], "\${exec_prefix}/doc/html/_static")
AC_SUBST([dochtmlcppdir], "\${exec_prefix}/doc/html/cpp")
AC_SUBST([dochtmlpythondir], "\${exec_prefix}/doc/html/python")
AC_SUBST([dochtmlsetupdir], "\${exec_prefix}/doc/html/setup")


# --- Python Redistributable Data: libs
AC_SUBST([corelibsdir], "\${exec_prefix}/core/libs")

# --- Python Redistributable Data: Lib ----

AC_SUBST([coreLibdir], "\${exec_prefix}/core/Lib")
AC_SUBST([coreLibctypesdir], "\${exec_prefix}/core/Lib/ctypes")
AC_SUBST([coreLibctypesmacholibdir], "\${exec_prefix}/core/Lib/ctypes/macholib")
AC_SUBST([coreLibctypestestdir], "\${exec_prefix}/core/Lib/ctypes/test")
AC_SUBST([coreLibcursesdir], "\${exec_prefix}/core/Lib/curses")
AC_SUBST([coreLibdbmdir], "\${exec_prefix}/core/Lib/dbm")
AC_SUBST([coreLibdistutilsdir], "\${exec_prefix}/core/Lib/distutils")
AC_SUBST([coreLibdistutilscommanddir], "\${exec_prefix}/core/Lib/distutils/command")
AC_SUBST([coreLibdistutilstestsdir], "\${exec_prefix}/core/Lib/distutils/tests")
AC_SUBST([coreLibemaildir], "\${exec_prefix}/core/Lib/email")
AC_SUBST([coreLibemailmimedir], "\${exec_prefix}/core/Lib/email/mime")
AC_SUBST([coreLibemailtestdir], "\${exec_prefix}/core/Lib/email/test")
AC_SUBST([coreLibemailtestdatadir], "\${exec_prefix}/core/Lib/email/test/data")
AC_SUBST([coreLibencodingsdir], "\${exec_prefix}/core/Lib/encodings")
AC_SUBST([coreLibhtmldir], "\${exec_prefix}/core/Lib/html")
AC_SUBST([coreLibhttpdir], "\${exec_prefix}/core/Lib/http")
AC_SUBST([coreLibidlelibdir], "\${exec_prefix}/core/Lib/idlelib")
AC_SUBST([coreLibidlelibIconsdir], "\${exec_prefix}/core/Lib/idlelib/Icons")
AC_SUBST([coreLibimportlibdir], "\${exec_prefix}/core/Lib/importlib")
AC_SUBST([coreLibimportlibtestdir], "\${exec_prefix}/core/Lib/importlib/test")
AC_SUBST([coreLibimportlibtestbuiltindir], "\${exec_prefix}/core/Lib/importlib/test/builtin")
AC_SUBST([coreLibimportlibtestextensiondir], "\${exec_prefix}/core/Lib/importlib/test/extension")
AC_SUBST([coreLibimportlibtestfrozendir], "\${exec_prefix}/core/Lib/importlib/test/frozen")
AC_SUBST([coreLibimportlibtestimport_dir], "\${exec_prefix}/core/Lib/importlib/test/import_")
AC_SUBST([coreLibimportlibtestsourcedir], "\${exec_prefix}/core/Lib/importlib/test/source")
AC_SUBST([coreLibjsondir], "\${exec_prefix}/core/Lib/json")
AC_SUBST([coreLibjsontestsdir], "\${exec_prefix}/core/Lib/json/tests")
AC_SUBST([coreLiblib2to3dir], "\${exec_prefix}/core/Lib/lib2to3")
AC_SUBST([coreLiblib2to3fixesdir], "\${exec_prefix}/core/Lib/lib2to3/fixes")
AC_SUBST([coreLiblib2to3pgen2dir], "\${exec_prefix}/core/Lib/lib2to3/pgen2")
AC_SUBST([coreLiblib2to3testsdir], "\${exec_prefix}/core/Lib/lib2to3/tests")
AC_SUBST([coreLiblib2to3testsdatadir], "\${exec_prefix}/core/Lib/lib2to3/tests/data")
AC_SUBST([coreLiblib2to3testsdatafixersdir], "\${exec_prefix}/core/Lib/lib2to3/tests/data/fixers")
AC_SUBST([coreLiblib2to3testsdatafixersmyfixesdir], "\${exec_prefix}/core/Lib/lib2to3/tests/data/fixers/myfixes")
AC_SUBST([coreLibloggingdir], "\${exec_prefix}/core/Lib/logging")
AC_SUBST([coreLibmsilibdir], "\${exec_prefix}/core/Lib/msilib")
AC_SUBST([coreLibmultiprocessingdir], "\${exec_prefix}/core/Lib/multiprocessing")
AC_SUBST([coreLibmultiprocessingdummydir], "\${exec_prefix}/core/Lib/multiprocessing/dummy")
AC_SUBST([coreLibpydoc_datadir], "\${exec_prefix}/core/Lib/pydoc_data")
AC_SUBST([coreLibsitepackagesdir], "\${exec_prefix}/core/Lib/site-packages")
AC_SUBST([coreLibsqlite3dir], "\${exec_prefix}/core/Lib/sqlite3")
AC_SUBST([coreLibsqlite3testdir], "\${exec_prefix}/core/Lib/sqlite3/test")
AC_SUBST([coreLibtestdir], "\${exec_prefix}/core/Lib/test")
AC_SUBST([coreLibtestcrashersdir], "\${exec_prefix}/core/Lib/test/crashers")
AC_SUBST([coreLibtestdecimaltestdatadir], "\${exec_prefix}/core/Lib/test/decimaltestdata")
AC_SUBST([coreLibtestleakersdir], "\${exec_prefix}/core/Lib/test/leakers")
AC_SUBST([coreLibtkinterdir], "\${exec_prefix}/core/Lib/tkinter")
AC_SUBST([coreLibtkintertestdir], "\${exec_prefix}/core/Lib/tkinter/test")
AC_SUBST([coreLibtkintertesttest_tkinterdir], "\${exec_prefix}/core/Lib/tkinter/test/test_tkinter")
AC_SUBST([coreLibtkintertesttest_ttkdir], "\${exec_prefix}/core/Lib/tkinter/test/test_ttk")
AC_SUBST([coreLiburllibdir], "\${exec_prefix}/core/Lib/urllib")
AC_SUBST([coreLibwsgirefdir], "\${exec_prefix}/core/Lib/wsgiref")
AC_SUBST([coreLibxmldir], "\${exec_prefix}/core/Lib/xml")
AC_SUBST([coreLibxmldomdir], "\${exec_prefix}/core/Lib/xml/dom")
AC_SUBST([coreLibxmletreedir], "\${exec_prefix}/core/Lib/xml/etree")
AC_SUBST([coreLibxmlparsersdir], "\${exec_prefix}/core/Lib/xml/parsers")
AC_SUBST([coreLibxmlsaxdir], "\${exec_prefix}/core/Lib/xml/sax")
AC_SUBST([coreLibxmlrpcdir], "\${exec_prefix}/core/Lib/xmlrpc")


AC_OUTPUT