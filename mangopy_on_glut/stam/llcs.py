import Geometry

x = (1, 0, 0)
y = (0, 1, 0)

gcs = Geometry.CoordinateSystem()
gcs.set(RENDER)

lcs = Geometry.CoordinateSystem()
lcs.position = (2, 0, 2)
lcs.rotate(30, 60, 90)
lcs.set(RENDER)

llcs = Geometry.CoordinateSystem()
llcs.setParentFrame(lcs)
llcs.position = (2, 2, 2)
llcs.rotate(80, 30, 45)
llcs.set(RENDER)

w = llcs.transformToAncestor(x, GlobalFrame)
all_g = Geometry.Arrow()
all_g.setTipPosition(w)
all_g.set(RENDER)


w = llcs.transformFromAncestor(y, GlobalFrame)
ag_ll = Geometry.Arrow()
ag_ll.setParentFrame(llcs)
ag_ll.setTipPosition(w)
ag_ll.set(RENDER)
