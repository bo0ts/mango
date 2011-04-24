import random
import math

class Grapher(Core.Object):
    def f(self):
        return x

    def draw(self):
        for x in range(-300, 300):            
            y1 = self.f(x)
            y2 = self.f(x + 1)
            Draw.line((x, y1), (x + 1, y2))


class PerlinGenerator1D:
    def __init__(self):        
        self.seed()
        self.width = 10

    def random(self, x):
        rem = x % self.width
        div = math.floor(x / self.width)        
        v = self.vectors[div]
        u = self.vectors[div + 1]
        a = 0.01 * (u + v)
        b = -0.1*v -0.2*u
        c = u
        return a*rem**3 + b*rem**2 + c*rem

    def seed(self):
        self.vectors = [random.randint(-5, 5) for i in range(100)]
        

class RandomGrapher(Grapher):
    r = PerlinGenerator1D()

    def f(self, x):
        return 2*self.r.random(x)

    def input(self, evt):
        if evt == Core.InputEvent(KEYBOARD, PRESS, KEY_SPACE): 
            self.r.seed()

    
g = RandomGrapher()
g.set(DRAW | INPUT)

print("1D Perlin noise. Use space to seed new tangents")
