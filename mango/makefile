GPP = g++ -DAPPLE
PROFILE_FLAGS = -pg -g3

CXXINCS = -L"C:/Dev-Cpp/Lib" -L"C:/Dev-Cpp/lib/gcc/mingw32/3.4.2" -I"C:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include"  -I"C:/Dev-Cpp/include/c++/3.4.2/mingw32" -I"C:/Dev-Cpp/include/c++/3.4.2" -I"C:/Dev-Cpp/include"
OPENGLINCS = -I"C:/Dev-Cpp/include/GL" -I"C:/freeglut/include" -L"C:/freeglut/lib" -lfreeglut -lglu32 -lopengl32 -lwinmm -lgdi32 

INCLUDE_DIRS = -IC:\files\projects\mango\install\include\mango -Iinstall\include\mango_on_glut -Iinstall\include\geometry
LIB_DIRS = -LC:\files\projects\mango\install\lib
CXXTEST_INCLUDES = -Isrc\cxxtest
PROJECTDIR_INC = -IC:\files\projects\mango





# MANGO_TESTS
test: build/test_vector 

src/test/core_vector_test_runner.cpp: src/test/core_vector.h
	imports/cxxtest/cxxtestgen.py --error-printer -o src/test/core_vector_test_runner.cpp src/test/core_vector.h

build/test_vector: src/test/core_vector_test_runner.cpp mango
	$(GPP) -Iimports/cxxtest -I. -lglut -lmango -Lbuild -Iinclude -o build/test_vector src/test/core_vector.h src/test/core_vector_test_runner.cpp -lmango $(PROFILE_FLAGS)





# MANGO	
mango: build/libmango.a copy_to_include

objects/mango.o: objects src/mango.h src/mango.cpp src/core/core.h src/core/core.cpp
	$(GPP) -fpic -c src/mango.cpp -o objects/mango.o $(PROFILE_FLAGS)

objects/core.o: objects src/core/core.h src/core/core.cpp 
	$(GPP) -fpic -c src/core/core.cpp -o objects/core.o $(PROFILE_FLAGS)

objects/vector.o: objects src/core/vector.h
	$(GPP) -fpic -c src/core/vector.h -o objects/vector.o $(PROFILE_FLAGS)

objects/matrix.o: objects src/core/matrix.h
	$(GPP) -fpic -c src/core/matrix.h -o objects/matrix.o $(PROFILE_FLAGS)

objects/constants.o: objects src/core/constants.h
	$(GPP) -fpic -c src/core/constants.h -o objects/constants.o $(PROFILE_FLAGS)

objects/error.o: objects src/core/error.cpp src/core/error.h
	$(GPP) -fpic -c src/core/error.cpp -o objects/error.o $(PROFILE_FLAGS)

objects/input.o: objects src/core/input.cpp src/core/input.h
	$(GPP) -fpic -c src/core/input.cpp -o objects/input.o $(PROFILE_FLAGS)

objects/triangle.o: objects src/core/triangle.cpp src/core/triangle.h
	$(GPP) -fpic -c src/core/triangle.cpp -o objects/triangle.o $(PROFILE_FLAGS)

objects/utils.o: objects src/core/utils.cpp src/core/utils.h
	$(GPP) -fpic -c src/core/utils.cpp -o objects/utils.o $(PROFILE_FLAGS)

objects/frame.o: objects src/core/frame.cpp src/core/frame.h
	$(GPP) -fpic -c src/core/frame.cpp -o objects/frame.o $(PROFILE_FLAGS)

objects/draw.o: objects src/draw/draw.cpp src/draw/draw.h
	$(GPP) -fpic -c src/draw/draw.cpp -o objects/draw.o $(PROFILE_FLAGS)

objects/raw_character_data.o: objects src/draw/raw_character_data.cpp src/draw/raw_character_data.h
	$(GPP) -fpic -c src/draw/raw_character_data.cpp -o objects/raw_character_data.o $(PROFILE_FLAGS)

build/libmango.a: build objects/mango.o objects/core.o objects/vector.o objects/matrix.o objects/constants.o objects/error.o objects/input.o objects/triangle.o objects/utils.o objects/frame.o objects/draw.o objects/raw_character_data.o
	ar -rcsu build/libmango.a objects/mango.o objects/core.o objects/vector.o objects/matrix.o objects/constants.o objects/error.o objects/input.o objects/triangle.o objects/utils.o objects/frame.o objects/draw.o objects/raw_character_data.o


build:
	mkdir -p build

objects:
	mkdir -p objects

include:
	mkdir -p include

include/core:
	mkdir -p include/core

include/draw:
	mkdir -p include/draw


# INCLUDE
copy_to_include: include/mango.h include/core/core.h include/core/vector.h include/core/matrix.h include/core/constants.h include/core/error.h include/core/input.h include/core/group.h include/core/triangle.h include/core/frame.h include/draw/draw.h include/draw/raw_character_data.h


include/mango.h: include src/mango.h 
	cp src/mango.h include/mango.h

include/core/core.h: include/core src/core/core.h 
	cp src/core/core.h include/core/core.h

include/core/vector.h: include/core src/core/vector.h 
	cp src/core/vector.h include/core/vector.h

include/core/matrix.h: include/core src/core/matrix.h 
	cp src/core/matrix.h include/core/matrix.h

include/core/constants.h: include/core src/core/constants.h 
	cp src/core/constants.h include/core/constants.h

include/core/error.h: include/core src/core/error.h 
	cp src/core/error.h include/core/error.h

include/core/input.h: include/core src/core/input.h 
	cp src/core/input.h include/core/input.h

include/core/group.h: include/core src/core/group.h 
	cp src/core/group.h include/core/group.h

include/core/triangle.h: include/core src/core/triangle.h 
	cp src/core/triangle.h include/core/triangle.h

include/core/frame.h: include/core src/core/frame.h 
	cp src/core/frame.h include/core/frame.h

include/draw/draw.h: include/draw src/draw/draw.h 
	cp src/draw/draw.h include/draw/draw.h

include/draw/raw_character_data.h: include/draw src/draw/raw_character_data.h 
	cp src/draw/raw_character_data.h include/draw/raw_character_data.h



# CLEAN
clean:
	rm -f objects/*
	rm -f build/*	
	rm -f include/*.h
	rm -f include/core/*.h
	rm -f include/draw/*.h









