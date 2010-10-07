GPP = g++
PROFILE_FLAGS = -pg -g3

APPLE_LDFLAGS = -arch i386
LDFLAGS = $(APPLE_LDFLAGS)

# GEOMETRY
geometry: copy_to_include build/libmgeo.a

objects/geometry.o: objects src/geometry.cpp src/geometry.h
	$(GPP) -Iimports/mango/include -fpic -c src/geometry.cpp -o objects/geometry.o $(LDFLAGS) $(PROFILE_FLAGS)

build/libmgeo.a: build objects/geometry.o
	ar -rcsu build/libmgeo.a objects/geometry.o


# DIRS
objects:
	mkdir -p objects

build:
	mkdir -p build

include:
	mkdir -p include


# INCLUDE 
copy_to_include: include include/geometry.h

include/geometry.h: include src/geometry.h
	cp src/geometry.h include/geometry.h


# CLEAN
clean:
	rm -f build/*
	rm -f objects/*
	rm -f include/*
