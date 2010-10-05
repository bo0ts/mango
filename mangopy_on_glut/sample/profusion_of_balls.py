import Geometry
from random import random

class ColorfulSphere(Geometry.Sphere):
    def __init__(self):
        Geometry.Sphere.__init__(self)
        self.boundary = 5

    def step(self):
        if self.position[0] > self.boundary or self.position[0] < -self.boundary:
            self.v[0] = -self.v[0];
        if self.position[1] > self.boundary or self.position[1] < -self.boundary:
            self.v[1] = -self.v[1];
        if self.position[2] > self.boundary or self.position[2] < -self.boundary:
            self.v[2] = -self.v[2];
            
        self.translate(self.v)

    def randomize(self):
        self.setRadius(0.15 + random()/10.0)
        self.v = Vector(random()/8.0, random()/8.0, random()/8.0)
        self.setColor((random(), random(), random()))
        self.position = Vector(self.boundary - 2*self.boundary*random(), self.boundary - 2*self.boundary*random(), self.boundary - 2*self.boundary*random())


for i in range(100):
    sphere = ColorfulSphere()
    sphere.randomize()
    sphere.set(RENDER | STEP)
