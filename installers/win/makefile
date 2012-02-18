MANGO_ROOT = ../../

all: installer

installer: staging/include staging/script staging/lib staging/doc staging/sample \
     staging/core staging/mango-a-493-312.bmp 
	makensis -DPRODUCT_VERSION=`tgit describe` mango-setup.nsi

staging/include: 
	mkdir -p staging/include
	cp $(MANGO_ROOT)/mango/include/*.h staging/include/
	cp -R $(MANGO_ROOT)/mango/include/core staging/include/
	cp -R $(MANGO_ROOT)/mango/include/draw staging/include/
	cp $(MANGO_ROOT)/mango_on_glut/include/*.h staging/include/
	cp $(MANGO_ROOT)/geometry/include/*.h staging/include/
	cp $(MANGO_ROOT)/mangopy/include/*.h staging/include/
	cp $(MANGO_ROOT)/pygeometry/include/*.h staging/include/

staging/core: 
	mkdir -p staging/core
	cp $(MANGO_ROOT)/build-win/.libs/mango.exe staging/core/
	cp $(MANGO_ROOT)/dlls/freeglut.dll staging/core/
	cp $(MANGO_ROOT)/dlls/libstdc++-6.dll staging/core/
	cp $(MANGO_ROOT)/dlls/libgcc_s_dw2-1.dll staging/core/
	cp $(MANGO_ROOT)/dlls/python31.dll staging/core/
	cp -R $(MANGO_ROOT)/python-redist/* staging/core/

staging/lib:
	mkdir -p staging/lib
	cp $(MANGO_ROOT)/build-win/.libs/libmango.a staging/lib/
	cp $(MANGO_ROOT)/build-win/.libs/libgeometry.a staging/lib/
	cp $(MANGO_ROOT)/build-win/.libs/libmong.a staging/lib/
	cp $(MANGO_ROOT)/build-win/.libs/libmangopy.a staging/lib/

staging/script:
	mkdir -p staging/script
	cp $(MANGO_ROOT)/build-win/.libs/Geometry-0.dll staging/script/Geometry.pyd
	cp $(MANGO_ROOT)/mangopy_on_glut/demo/demo.py staging/script/

staging/sample:
	mkdir -p staging/sample
	cp $(MANGO_ROOT)/mangopy_on_glut/sample/*.py staging/sample/

staging/doc:
	mkdir -p staging/doc
	cp -R $(MANGO_ROOT)/doc/build/html/* staging/doc/

staging/mango-a-493-312.bmp:
	cp mango-a-493-312.bmp staging/

clean:
	rm -rf staging
	rm -f Mango*.exe
