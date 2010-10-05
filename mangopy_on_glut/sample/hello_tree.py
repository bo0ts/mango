import Geometry

trunk = Geometry.Cylinder()
trunk.setColor(1.0, 0.5, 0.3)
trunk.setRadius(0.1)
trunk.set(RENDER)

leaves = Geometry.Sphere()
leaves.setColor(0, 1.0, 0)
leaves.position = (0, 1.0, 0)
leaves.set(RENDER)
