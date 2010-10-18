GPP = g++
PROFILE_FLAGS = -pg -g3

APPLE_LDFLAGS = -arch i386
LDFLAGS = $(APPLE_LDFLAGS)

LINUX_GLUT = -lglut
APPLE_GLUT = -framework OpenGL -framework GLUT
GLUT_LINK = $(APPLE_GLUT)

# MANGO ON GLUT
mango_on_glut: copy_to_include build/libmong.a 

objects/mango_on_glut.o: objects src/mango_on_glut.cpp src/mango_on_glut.h
	$(GPP) $(GLUT_LINK) -Iimports/mango/include/ -c src/mango_on_glut.cpp -o objects/mango_on_glut.o $(LDFLAGS) $(PROFILE_FLAGS)

build/libmong.a: build objects/mango_on_glut.o
	ar -rcsu build/libmong.a objects/mango_on_glut.o


# SAMPLE
sample: build/hello_mango_on_glut build/hello_input_events build/hello_geometry build/hello_box build/hello_transform_to_from_parent build/hello_transform_to_from_ancestor

build/hello_mango_on_glut: mango_on_glut sample/hello_mango_on_glut.cpp
	$(GPP) sample/hello_mango_on_glut.cpp -Lbuild -Limports/mango/build $(GLUT_LINK) -Iimports/mango/include -Iinclude -o build/hello_mango_on_glut -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_input_events: mango_on_glut sample/hello_input_events.cpp
	$(GPP) sample/hello_input_events.cpp -Lbuild -Limports/mango/build $(GLUT_LINK) -Iimports/mango/include -Iinclude -o build/hello_input_events -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_geometry: mango_on_glut sample/hello_geometry.cpp
	$(GPP) sample/hello_geometry.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_geometry -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_box: mango_on_glut sample/hello_box.cpp
	$(GPP) sample/hello_box.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_box -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_earth_sun: mango_on_glut sample/hello_earth_sun.cpp
	$(GPP) sample/hello_earth_sun.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_earth_sun -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_coordinate_system: mango_on_glut sample/hello_coordinate_system.cpp
	$(GPP) sample/hello_coordinate_system.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_coordinate_system -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_arrow: mango_on_glut sample/hello_arrow.cpp
	$(GPP) sample/hello_arrow.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_arrow -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_transform_to_from_parent: mango_on_glut sample/hello_transform_to_from_parent.cpp
	$(GPP) sample/hello_transform_to_from_parent.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_transform_to_from_parent -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)

build/hello_transform_to_from_ancestor: mango_on_glut sample/hello_transform_to_from_ancestor.cpp
	$(GPP) sample/hello_transform_to_from_ancestor.cpp -Lbuild -Limports/mango/build -Limports/geometry/build $(GLUT_LINK) -lmgeo -Iimports/mango/include -Iimports/geometry/include -Iinclude -o build/hello_transform_to_from_ancestor -lmong -lmango $(LDFLAGS) $(PROFILE_FLAGS)


# DIRS
objects:
	mkdir -p objects

build:
	mkdir -p build

include:
	mkdir -p include


# INSTALL MANGO ON GLUT
copy_to_include: include include/mango_on_glut.h include/mango_glut.h

include/mango_on_glut.h: src/mango_on_glut.h
	cp src/mango_on_glut.h include/mango_on_glut.h

include/mango_glut.h: src/mango_glut.h
	cp src/mango_glut.h include/mango_glut.h


# CLEAN
clean:
	rm -f objects/*
	rm -f build/*
	rm -f include/*