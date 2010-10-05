GPP = g++ 
PROFILE_FLAGS = -pg -g3

# MANGOPY_ON_GLUT
mangopy_on_glut: build/mango

build/mango: build
	$(GPP) -Iimports/mango_on_glut/include -Iimports/mango/include -Iimports/mangopy/include -Iimports/python/ -Limports/mango/build -Limports/mangopy/build -Limports/mango_on_glut/build src/mangopy_on_glut.cpp -o build/mango -lglut -lmangopy -lmong -lmango -lpython3.1 $(PROFILE_FLAGS)


# DIRS
build:
	mkdir -p build

# CLEAN
clean:
	rm -f build/*
