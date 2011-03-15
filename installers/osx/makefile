
all: 1.0 Headers

Mango:
	cp imports/mango/build/libmango.a Mango
	ar rv Mango imports/mango_on_glut/objects/*.o
	ar rv Mango imports/geometry/objects/*.o
	ar rv Mango imports/mangopy/objects/*.o

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
	mkdir 1.0/bin
	mkdir 1.0/lib	
	mkdir 1.0/doc
	cp imports/mangopy_on_glut/build/mango 1.0/bin/
	cp -R imports/mango/build/*.a 1.0/lib/
	cp -R imports/mango_on_glut/build/*.a 1.0/lib/
	cp -R imports/geometry/build/*.a 1.0/lib/
	cp -R imports/mangopy/build/*.a 1.0/lib/
	cp -R imports/pygeometry/build/* 1.0/lib/
	cp Info.plist 1.0/Resources/
	cp osx-link-mango.sh 1.0/Resources/
	cp -R imports/doc/build/html/ 1.0/doc/
	cp Mango 1.0/Mango

clean:
	rm Mango
	rm -rf 1.0/