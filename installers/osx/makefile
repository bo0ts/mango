
all: staging



staging: 1.0 Headers

Mango:
	cp imports/build-osx/.libs/libmango.a Mango
	mkdir -p tmp-objects-mong
	cp imports/build-osx/.libs/libmong.a tmp-objects-mong/	
	cd tmp-objects-mong && ar -x libmong.a
	mkdir -p tmp-objects-geometry	
	cp imports/build-osx/.libs/libgeometry.a tmp-objects-geometry/
	cd tmp-objects-geometry	&& ar -x libgeometry.a
	mkdir -p tmp-objects-mangopy
	cp imports/build-osx/.libs/libmangopy.a tmp-objects-mangopy
	cd tmp-objects-mangopy && ar -x libmangopy.a
	ar rv Mango tmp-objects-mong/*.o
	ar rv Mango tmp-objects-geometry/*.o
	ar rv Mango tmp-objects-mangopy/*.o
	rm -rf tmp-objects-mong 
	rm -rf tmp-objects-geometry
	rm -rf tmp-objects-mangopy

Headers: 1.0
	mkdir 1.0/Headers
	cp imports/mango/include/*.h 1.0/Headers/
	cp -R imports/mango/include/core 1.0/Headers/
	cp -R imports/mango/include/draw 1.0/Headers/
	cp imports/mango_on_glut/include/*.h 1.0/Headers/
	cp imports/geometry/include/*.h 1.0/Headers/
	cp imports/mangopy/include/*.h 1.0/Headers/
	cp imports/pygeometry/include/*.h 1.0/Headers/


1.0: Mango
	mkdir 1.0
	mkdir 1.0/Resources
	mkdir -p 1.0/core/lib
	mkdir 1.0/script
	mkdir 1.0/lib
	mkdir 1.0/doc
	mkdir 1.0/sample
	cp imports/build-osx/mango 1.0/core/
	cp -R /Library/Frameworks/Python.framework/Versions/Current/Python 1.0/core/lib/
	cp -R /Library/Frameworks/Python.framework/Versions/Current/lib/python3.1 1.0/core/lib/
	cp imports/build-osx/.libs/*.a 1.0/lib/
	cp -L imports/build-osx/.libs/Geometry.so 1.0/script/Geometry.so
	cp imports/mangopy_on_glut/demo/demo.py 1.0/script/
	cp -R imports/doc/build/html/ 1.0/doc/
	cp imports/mangopy_on_glut/sample/*.py 1.0/sample/
	cp Info.plist 1.0/Resources/
	cp osx-link-mango.sh 1.0/Resources/
	cp Mango 1.0/Mango

clean:
	rm Mango
	rm -rf 1.0/
	rm -rf tmp-objects-*