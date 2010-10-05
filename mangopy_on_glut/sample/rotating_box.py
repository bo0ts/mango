import Geometry           

class RotatingBox(Geometry.Box):
    def step(self):
        self.rotate(1, 0, 0)
        
b = RotatingBox()
b.set(RENDER | STEP)
