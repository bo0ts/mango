import Geometry

box = Geometry.Box()
box.set(RENDER)

sphere = Geometry.Sphere();
sphere.setRadius(0.7);
sphere.position = (2, 0, 0);
sphere.set(RENDER);

cylinder = Geometry.Cylinder();
cylinder.position = (0, 0, -2);
cylinder.setHeight(1.0);
cylinder.setRadius(0.5);
cylinder.set(RENDER);

shell = Geometry.Shell();
shell.position = (2, 0, -2);
shell.setRadius(0.7);
shell.setFraction(0.6);
shell.setThickness(0.05);
shell.setOrientation(-25, 205, 0);
shell.set(RENDER);

arrows = [Geometry.Arrow(), Geometry.Arrow(), Geometry.Arrow()]
arrows[0].position = (-2, -0.5, -2);
arrows[0].set(RENDER);

arrows[1].position = (-1.6, -0.5, -2);
arrows[1].setLength(0.4);
arrows[1].setBlueComponent(0.8);
arrows[1].set(RENDER);

arrows[2].position = (-1.8, -0.5, -1.6);
arrows[2].setLength(1.75);
arrows[2].setThickness(0.3);
arrows[2].setRedComponent(0.6);
arrows[2].set(RENDER);

coordinate_system = Geometry.CoordinateSystem();
coordinate_system.position = (2, -0.3, 1.6);
coordinate_system.setAxisLength(0.8);
coordinate_system.setAxisThickness(0.1);
coordinate_system.setRightHanded(True);
coordinate_system.set(RENDER);

circles = [Geometry.Circle(), Geometry.Circle()]
circles[0].position = (-2.0, 0, 2.0);
circles[0].setRadius(0.7);
circles[0].setGreenComponent(0.9);
circles[0].set(RENDER);

circles[1].position = (-2.0, 0, 2.0);
circles[1].setRadius(0.2);
circles[1].setStyle(Geometry.FILL);
circles[1].setOrientation(0, 90, 0);
circles[1].setRenderReverseOrientation(True);
circles[1].set(RENDER);

ngons = [Geometry.NGon(), Geometry.NGon()]
ngons[0].position = (-2.0, 0, 0);
ngons[0].setRadius(0.3);
ngons[0].setStyle(Geometry.FILL);
ngons[0].setNumberOfSides(6);
ngons[0].setRenderReverseOrientation(True);
ngons[0].set(RENDER);

ngons[1].position = (-2.0, 0, 0);
ngons[1].setOrientation(0, 90, 0);
ngons[1].set(RENDER);

rectangles = [Geometry.Rectangle(), Geometry.Rectangle()]
rectangles[0].position = (-4.0, 0, 0);
rectangles[0].setOrientation(0, 45, 0);
rectangles[0].set(RENDER);

rectangles[1].position = (-4.0, 0, 0);
rectangles[1].setOrientation(0, 135, 0);
rectangles[1].setDimensions(0.5, 0.5/1.1618);
rectangles[1].setStyle(Geometry.FILL);
rectangles[1].set(RENDER);

vertices = Geometry.VertexArray();
vertices.add(-0.5, 0.0, 0.0);
vertices.add(0.0, 0.5, 0.0);
vertices.add(0.0, 1.5, 0.0);

vertices.add(0.0, 0.5, 0.0);
vertices.add(0.5, 0.0, 0.0);
vertices.add(0.0, 1.5, 0.0);

vertices.setRenderReverseOrientation(True);
vertices.setStyle(4);
vertices.position = (0, -0.5, 2);
vertices.set(RENDER);

Camera.lookFrom((-4, 5, 5))
