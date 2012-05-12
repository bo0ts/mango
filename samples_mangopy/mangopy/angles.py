import Geometry, math

class Arc(Geometry.ColorfulObject):
    def __init__(self, rin, rout, fraction):
        Core.Object.__init__(self)
        self.rin = rin
        self.rout = rout
        self.fraction = fraction        
        self.reflect = 1

    def render(self):
        self.transform()
        glColor(self.color())
        glBegin(GL_QUADS)
        sign = self.reflect
        dangle = sign * 5
        maxangle = sign * round(self.fraction*360)
        dangle = -dangle if self.fraction < 0 else dangle
        for angle in range(0, maxangle, dangle):
            angles = [angle, angle+dangle]
            sins = [math.sin(x/180.0*math.pi) for x in angles]
            cosins = [math.cos(x/180.0*math.pi) for x in angles]            
            rin = self.rin
            rout = self.rout
            points = [(rin * sins[0], 0, rin * cosins[0]),
                      (rout * sins[0], 0, rout * cosins[0]),
                      (rout * sins[1], 0, rout * cosins[1]),
                      (rin * sins[1], 0, rin * cosins[1])]
            
            glVertex(points[0])
            glVertex(points[1])
            glVertex(points[2])
            glVertex(points[3])

            glVertex(points[3])
            glVertex(points[2])
            glVertex(points[1])
            glVertex(points[0])
        glEnd()


class RotatingCoordinateSystem(Core.Object):
    def __init__(self):
        Core.Object.__init__(self)
        self.make_cs()
        self.make_arcs()
    
    def draw(self):        
        tsize = 25
        xs = -310
        ys = 230
        glColor(self.arcs[0].color())
        Draw.text((xs, ys), "alpha: %.2f" % self.cs[1].alpha, tsize)
        glColor(self.arcs[1].color())
        Draw.text((xs, ys - tsize), "beta: %.2f" % self.cs[2].beta, tsize)
        glColor(self.arcs[2].color())
        Draw.text((xs, ys - 2*tsize), "gamma: %.2f" % self.cs[3].gamma, tsize)

    def step(self):
        keys = ['q', 'a', 'w', 's', 'e', 'd']
        isdown = [Keyboard.down(ord(x)) for x in keys]
        dangle = 0.4
        deltas = [0, 0, 0]
        for i in range(3):                        
            deltas[i] = dangle*(-1)**i if isdown[i*2] else deltas[i]            
            deltas[i] = -dangle*(-1)**i if isdown[i*2 + 1] else deltas[i]
            self.arcs[i].fraction +=  deltas[i] / 360.0 * (-1)**i        
        self.cs[1].rotate(deltas[0], 0, 0)
        self.cs[2].rotate(0, deltas[1], 0)
        self.cs[3].rotate(0, 0, deltas[2])

    def make_cs(self):
        self.cs = [Geometry.CoordinateSystem() for i in range(4)]
        self.cs[1].setParentFrame(self.cs[0])
        self.cs[2].setParentFrame(self.cs[1])
        self.cs[3].setParentFrame(self.cs[2])
        for cs in self.cs[:-1]: cs.setAxisThickness(0.03)
        

    def make_arcs(self):
        xarc = Arc(0.7, 0.8, 0)
        xarc.setColor(0.4, 1.0, 0.0)

        yarc = Arc(0.7, 0.8, 0)
        yarc.rotate(90, 90, -90)
        yarc.setColor(1.0, 1.0, 0.0)        
        yarc.reflect = -1
        yarc.setParentFrame(self.cs[1])

        zarc = Arc(0.7, 0.8, 0)
        zarc.reflect = -1
        zarc.rotate(0, 180, 180)
        zarc.setParentFrame(self.cs[2])
        zarc.setColor(1.0, 0.5, 0.0)
        self.arcs = [xarc, yarc, zarc]

    def set(self, mask):
        Core.Object.set(self, mask)
        for cs in self.cs: cs.set(mask)
        for arc in self.arcs: arc.set(mask)

    def unset(self, mask):
        Core.Object.unset(self, mask)
        for cs in self.cs: cs.unset(mask)
        for arc in self.arcs: arc.unset(mask)

    def toggle(self, mask):
        Core.Object.toggle(self, mask)
        for cs in self.cs: cs.toggle(mask)
        for arc in self.arcs: arc.toggle(mask)

    

lcs = RotatingCoordinateSystem()
lcs.set(RENDER | STEP | DRAW)
Camera.lookFrom((3, 3, 3))
View.setMode(LOCK_ALL)
print("Rotatable Coordinate System")
print("  alpha +/-: q/a")
print("  beta +/-: s/w")
print("  gamma +/-: e/d")
