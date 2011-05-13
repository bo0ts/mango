import Solids

pyramids = [Solids.Tetrahedron() for i in range(4)]
for i, p in enumerate(pyramids):
    p.position = (-4 + i*2, 0, 0)
    p.setHeight(i + 1)
    p.set(RENDER)

Camera.lookFrom((-2, 7, 6))
