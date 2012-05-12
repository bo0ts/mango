from demo import Label
import Geometry


lx = Label("x")
lx.position = (1.1, 0.1, 0)
lx.set(RENDER | STEP)

ly = Label("y")
ly.position = (0, 1.2, 0)
ly.set(RENDER | STEP)

lz = Label("z")
lz.position = (0, 0.1, 1.1)
lz.set(RENDER | STEP)

cs = Geometry.CoordinateSystem()
cs.set(RENDER)
