GPP = g++ 
PROFILE_FLAGS = -pg -g3


# PYGEOMETRY
pygeometry: copy_to_include build/Geometry.so 

objects/pygeometry.o: objects src/pygeometry.cpp src/pygeometry.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry.cpp -o objects/pygeometry.o

objects/pygeometry_colorful_object.o: objects src/pygeometry_colorful_object.cpp src/pygeometry_colorful_object.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_colorful_object.cpp -o objects/pygeometry_colorful_object.o

objects/pygeometry_box.o: objects src/pygeometry_box.cpp src/pygeometry_box.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_box.cpp -o objects/pygeometry_box.o

objects/pygeometry_sphere.o: objects src/pygeometry_sphere.cpp src/pygeometry_sphere.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_sphere.cpp -o objects/pygeometry_sphere.o

objects/pygeometry_cylinder.o: objects src/pygeometry_cylinder.cpp src/pygeometry_cylinder.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_cylinder.cpp -o objects/pygeometry_cylinder.o

objects/pygeometry_shell.o: objects src/pygeometry_shell.cpp src/pygeometry_shell.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_shell.cpp -o objects/pygeometry_shell.o

objects/pygeometry_arrow.o: objects src/pygeometry_arrow.cpp src/pygeometry_arrow.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_arrow.cpp -o objects/pygeometry_arrow.o

objects/pygeometry_coordinate_system.o: objects src/pygeometry_coordinate_system.cpp src/pygeometry_coordinate_system.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_coordinate_system.cpp -o objects/pygeometry_coordinate_system.o

objects/pygeometry_vertex_array.o: objects src/pygeometry_vertex_array.cpp src/pygeometry_vertex_array.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_vertex_array.cpp -o objects/pygeometry_vertex_array.o

objects/pygeometry_circle.o: objects src/pygeometry_circle.cpp src/pygeometry_circle.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_circle.cpp -o objects/pygeometry_circle.o

objects/pygeometry_ngon.o: objects src/pygeometry_ngon.cpp src/pygeometry_ngon.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_ngon.cpp -o objects/pygeometry_ngon.o

objects/pygeometry_rectangle.o: objects src/pygeometry_rectangle.cpp src/pygeometry_rectangle.h
	$(GPP) -Iimports/geometry/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python -Limports/mangopy/build -fpic -c src/pygeometry_rectangle.cpp -o objects/pygeometry_rectangle.o

build/Geometry.so: build objects/pygeometry.o objects/pygeometry_colorful_object.o objects/pygeometry_sphere.o objects/pygeometry_box.o objects/pygeometry_cylinder.o objects/pygeometry_shell.o objects/pygeometry_arrow.o objects/pygeometry_coordinate_system.o objects/pygeometry_vertex_array.o objects/pygeometry_circle.o objects/pygeometry_ngon.o objects/pygeometry_rectangle.o 
	$(GPP) -Limports/mangopy/build -Limports/geometry/build -Limports/mango/build objects/pygeometry.o objects/pygeometry_colorful_object.o objects/pygeometry_box.o objects/pygeometry_sphere.o objects/pygeometry_cylinder.o objects/pygeometry_shell.o objects/pygeometry_arrow.o objects/pygeometry_coordinate_system.o objects/pygeometry_vertex_array.o objects/pygeometry_circle.o objects/pygeometry_ngon.o objects/pygeometry_rectangle.o -lmangopy -lmgeo -lmango -lpython3.1 -fpic -shared -o build/Geometry.so


# DIRS
objects:
	mkdir -p objects

build:
	mkdir -p build

include:
	mkdir -p include


copy_to_include: include/pygeometry_arrow.h include/pygeometry_circle.h include/pygeometry_coordinate_system.h include/pygeometry.h include/pygeometry_rectangle.h include/pygeometry_sphere.h include/pygeometry_box.h include/pygeometry_colorful_object.h include/pygeometry_cylinder.h include/pygeometry_ngon.h include/pygeometry_shell.h include/pygeometry_vertex_array.h

include/pygeometry_arrow.h: include src/pygeometry_arrow.h
	cp src/pygeometry_arrow.h include/pygeometry_arrow.h

include/pygeometry_circle.h: include src/pygeometry_circle.h
	cp src/pygeometry_circle.h include/pygeometry_circle.h

include/pygeometry_coordinate_system.h: include src/pygeometry_coordinate_system.h
	cp src/pygeometry_coordinate_system.h include/pygeometry_coordinate_system.h

include/pygeometry.h: include src/pygeometry.h
	cp src/pygeometry.h include/pygeometry.h

include/pygeometry_rectangle.h: include src/pygeometry_rectangle.h
	cp src/pygeometry_rectangle.h include/pygeometry_rectangle.h

include/pygeometry_sphere.h: include src/pygeometry_sphere.h
	cp src/pygeometry_sphere.h include/pygeometry_sphere.h

include/pygeometry_box.h: include src/pygeometry_box.h
	cp src/pygeometry_box.h include/pygeometry_box.h

include/pygeometry_colorful_object.h: include src/pygeometry_colorful_object.h
	cp src/pygeometry_colorful_object.h include/pygeometry_colorful_object.h

include/pygeometry_cylinder.h: include src/pygeometry_cylinder.h
	cp src/pygeometry_cylinder.h include/pygeometry_cylinder.h

include/pygeometry_ngon.h: include src/pygeometry_ngon.h
	cp src/pygeometry_ngon.h include/pygeometry_ngon.h

include/pygeometry_shell.h: include src/pygeometry_shell.h
	cp src/pygeometry_shell.h include/pygeometry_shell.h

include/pygeometry_vertex_array.h: include src/pygeometry_vertex_array.h
	cp src/pygeometry_vertex_array.h include/pygeometry_vertex_array.h


# CLEAN

clean:
	rm -f objects/*
	rm -f build/*
	rm -f include/*