GPP = g++
PROFILE_FLAGS = -pg -g3 

LINUX_PYTHON_INCLUDES = -Iimports/python
APPLE_PYTHON_INCLUDES = -framework Python 
PYTHON_INCLUDES = $(APPLE_PYTHON_INCLUDES)

APPLE_LDFLAGS = -arch i386
LDFLAGS = $(APPLE_LDFLAGS)

# MANGOPY
mangopy: copy_to_include build/libmangopy.a

objects/mangopy.o: objects src/mangopy.c src/mangopy.h
	$(GPP) $(PYTHON_INCLUDES) -Iimports/mango/include/ -fpic -c src/mangopy.c -o objects/mangopy.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_core.o: objects src/mangopy_core.cpp src/mangopy_core.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_core.cpp -o objects/mangopy_core.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_frame.o: objects src/mangopy_frame.cpp src/mangopy_frame.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_frame.cpp -o objects/mangopy_frame.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_vector.o: objects  src/mangopy_vector.cpp src/mangopy_vector.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_vector.cpp -o objects/mangopy_vector.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_matrix.o: objects  src/mangopy_matrix.cpp src/mangopy_matrix.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_matrix.cpp -o objects/mangopy_matrix.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_pyengine.o: objects src/mangopy_pyengine.cpp src/mangopy_pyengine.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_pyengine.cpp -o objects/mangopy_pyengine.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_triangle.o: objects src/mangopy_triangle.cpp src/mangopy_triangle.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_triangle.cpp -o objects/mangopy_triangle.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_camera.o: objects src/mangopy_camera.cpp src/mangopy_camera.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_camera.cpp -o objects/mangopy_camera.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_keyboard.o: objects src/mangopy_keyboard.cpp src/mangopy_keyboard.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_keyboard.cpp -o objects/mangopy_keyboard.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_mouse.o: objects src/mangopy_mouse.cpp src/mangopy_mouse.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_mouse.cpp -o objects/mangopy_mouse.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_input_event.o: objects src/mangopy_input_event.cpp src/mangopy_input_event.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_input_event.cpp -o objects/mangopy_input_event.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_opengl.o: objects src/mangopy_opengl.cpp src/mangopy_opengl.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_opengl.cpp -o objects/mangopy_opengl.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_draw.o: objects src/mangopy_draw.cpp src/mangopy_draw.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_draw.cpp -o objects/mangopy_draw.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_core_module.o: objects src/mangopy_core_module.cpp src/mangopy_core_module.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_core_module.cpp -o objects/mangopy_core_module.o $(LDFLAGS) $(PROFILE_FLAGS)

objects/mangopy_pyengine_wrapper.o: objects src/mangopy_pyengine_wrapper.cpp src/mangopy_pyengine_wrapper.h
	$(GPP) -Iimports/mango/include/ $(PYTHON_INCLUDES) -fpic -c src/mangopy_pyengine_wrapper.cpp -o objects/mangopy_pyengine_wrapper.o $(LDFLAGS) $(PROFILE_FLAGS)

build/libmangopy.a: build objects/mangopy.o objects/mangopy_core.o objects/mangopy_frame.o objects/mangopy_vector.o objects/mangopy_matrix.o objects/mangopy_pyengine.o objects/mangopy_triangle.o objects/mangopy_camera.o objects/mangopy_keyboard.o objects/mangopy_mouse.o objects/mangopy_input_event.o objects/mangopy_opengl.o objects/mangopy_draw.o objects/mangopy_core_module.o objects/mangopy_pyengine_wrapper.o
	ar -rcsu build/libmangopy.a objects/mangopy.o objects/mangopy_core.o objects/mangopy_frame.o objects/mangopy_vector.o objects/mangopy_matrix.o objects/mangopy_pyengine.o objects/mangopy_triangle.o objects/mangopy_camera.o objects/mangopy_keyboard.o objects/mangopy_mouse.o objects/mangopy_input_event.o objects/mangopy_opengl.o objects/mangopy_draw.o objects/mangopy_core_module.o objects/mangopy_pyengine_wrapper.o



# DIRS
build:
	mkdir -p build

objects:
	mkdir -p objects

include:
	mkdir -p include


# INSTALL MANGOPY
copy_to_include:  include/mangopy.h  include/mangopy_core.h include/mangopy_frame.h include/mangopy_vector.h include/mangopy_matrix.h include/mangopy_pyengine.h include/mangopy_pyengine_wrapper.h include/mangopy_triangle.h include/mangopy_camera.h include/mangopy_keyboard.h include/mangopy_mouse.h include/mangopy_input_event.h include/mangopy_opengl.h include/mangopy_draw.h include/mangopy_core_module.h  include/mangopy_error.h include/mangopy_python.h

include/mangopy.h: include src/mangopy.h
	cp src/mangopy.h include/mangopy.h

include/mangopy_core.h: include src/mangopy_core.h
	cp src/mangopy_core.h include/mangopy_core.h

include/mangopy_frame.h: include src/mangopy_frame.h
	cp src/mangopy_frame.h include/mangopy_frame.h

include/mangopy_vector.h: include src/mangopy_vector.h
	cp src/mangopy_vector.h include/mangopy_vector.h

include/mangopy_matrix.h: include src/mangopy_matrix.h
	cp src/mangopy_matrix.h include/mangopy_matrix.h

include/mangopy_pyengine.h: include src/mangopy_pyengine.h
	cp src/mangopy_pyengine.h include/mangopy_pyengine.h

include/mangopy_pyengine_wrapper.h: include src/mangopy_pyengine_wrapper.h
	cp src/mangopy_pyengine_wrapper.h include/mangopy_pyengine_wrapper.h

include/mangopy_triangle.h: include src/mangopy_triangle.h
	cp src/mangopy_triangle.h include/mangopy_triangle.h

include/mangopy_camera.h: include src/mangopy_camera.h
	cp src/mangopy_camera.h include/mangopy_camera.h

include/mangopy_keyboard.h: include src/mangopy_keyboard.h
	cp src/mangopy_keyboard.h include/mangopy_keyboard.h

include/mangopy_mouse.h: include src/mangopy_mouse.h
	cp src/mangopy_mouse.h include/mangopy_mouse.h

include/mangopy_input_event.h: include src/mangopy_input_event.h
	cp src/mangopy_input_event.h include/mangopy_input_event.h

include/mangopy_opengl.h: include src/mangopy_opengl.h
	cp src/mangopy_opengl.h include/mangopy_opengl.h

include/mangopy_draw.h: include src/mangopy_draw.h
	cp src/mangopy_draw.h include/mangopy_draw.h

include/mangopy_core_module.h: include src/mangopy_core_module.h
	cp src/mangopy_core_module.h include/mangopy_core_module.h

include/mangopy_error.h: include src/mangopy_error.h
	cp src/mangopy_error.h include/mangopy_error.h

include/mangopy_python.h: include src/mangopy_python.h
	cp src/mangopy_python.h include/mangopy_python.h




# CLEAN
clean:
	rm -f objects/*
	rm -f build/*
	rm -f include/*
