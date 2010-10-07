GPP = g++ 
PROFILE_FLAGS = -pg -g3

APPLE_LDFLAGS = -arch i386
LDFLAGS = $(APPLE_LDFLAGS)

LINUX_PYTHON_LINK = -lpython3.1
APPLE_PYTHON_LINK = -framework Python
PYTHON_LINK = $(APPLE_PYTHON_LINK)

LINUX_GLUT_LINK = -lglut
APPLE_GLUT_LINK = -framework GLUT -framework OpenGL
GLUT_LINK = $(APPLE_GLUT_LINK)

# MANGOPY_ON_GLUT
mangopy_on_glut: build/mango

build/mango: build
	$(GPP) -Iimports/mango_on_glut/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python/ -Limports/mango/build -Limports/mangopy/build -Limports/mango_on_glut/build src/mangopy_on_glut.cpp -o build/mango $(GLUT_LINK) -lmangopy -lmong -lmango $(PYTHON_LINK) $(LDFLAGS) $(PROFILE_FLAGS)


# DIRS
build:
	mkdir -p build

# CLEAN
clean:
	rm -f build/*
