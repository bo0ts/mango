from math import sin, cos, pi
import random

class Dot(Core.Object):

    def __init__(self):
        Core.Object.__init__(self)
        self.reset()

    def reset(self):
        rand_angle = 100*random.random()
        num = round(10*random.random())        
        self.rand_dir = pow(-1, num)        
        self.v = Vector(cos(rand_angle), sin(rand_angle))
        self.position = Vector(0, 0)
        self.t = 0
        self.k = 0.05 + 0.3*random.random()
        self.num_pts = 50
        self.pts = []
        self.color = 1.0


    def step(self):
        self.t += 0.001
        self.v += self.a()
        self.v.normalize()
        self.translate(self.v)

        self.pts.append(self.position)
        if len(self.pts) == self.num_pts:
            del self.pts[0]
        
        if self.t >= 0.12:
            self.color = (0.15 - self.t)/0.05
        if self.t >= 0.15:
            self.reset()

    def draw(self):
        glBegin(GL_LINE_STRIP)
        for (i, j) in enumerate(self.pts):
            fade = (i/float(self.num_pts))**2
            color = self.color
            glColor(color*0.8*fade, color*0.9*fade, color*fade)
            glVertex(j)
        glEnd()

    def a_scale(self):
        return self.rand_dir*self.k*self.t*random.random()

    def a_dir(self):
        return Vector(-self.v[1], self.v[0])

    def a(self):
        return self.a_scale()*self.a_dir()


class DotSource(Core.Object):
    def __init__(self):
        self.dots = []
        self.created = 0
        self.max = 150

    def step(self):
        if self.created < self.max:
            d = Dot()            
            d.set(DRAW | STEP)
            self.dots.append(d)
            self.created += 1

d = DotSource()
d.set(STEP)


#View.setMode(RMB_CYLINDRICAL_ROTATE)
print(View.modeEnabled(RMB_CYLINDRICAL_ROTATE))

