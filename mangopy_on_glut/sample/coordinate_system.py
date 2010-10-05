import Geometry

class Label(Core.Object):
    def __init__(self, str):
        self.str = str
        Core.Object.__init__(self)
    
    
    def render(self):
        glColor(1.0, 0.3, 0.0)
        self.transform()        
        Draw.text((0, 0), self.str, 0.3)
        
    def step(self):
        camera_parent = Camera.parentFrame()
        camera_pos = camera_parent.transformToParent(Camera.position)        
        self.pointTo(camera_pos)
        self.rotate(0, -90, 0)


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
