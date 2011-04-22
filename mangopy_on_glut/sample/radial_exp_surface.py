import Geometry, math

class Surface(Core.Object):
    xrange = (-1.0, 1.0)
    yrange = (-1.0, 1.0)
    delta = 0.1

    def render(self):
        self.transform()
        glBegin(GL_QUADS)
        for point in self.points_in_region():
            self.render_f_quad(point[0], point[1])            
        glEnd()

    def render_f_quad(self, x, y):
        for pt in self.points_in_quad(x, y): 
            self.render_f_vertex(pt[0], pt[1])

    def render_f_vertex(self, x, y):
        green = (x**2 + y**2)**0.4
        glColor(0.0, green, 1.0)
        glVertex(self.s(x, y))

    def points_in_quad(self, x, y):
        pts = [(x, y),
               (x, y + self.delta),
               (x + self.delta, y + self.delta),
               (x + self.delta, y)]
        rpts = [pt for pt in reversed(pts)]
        return pts + rpts
        
    def points_in_region(self):
        for i in range(round((self.xrange[1] - self.xrange[0])/self.delta)):
            for j in range(round((self.yrange[1] - self.yrange[0])/self.delta)):
                x = self.xrange[0] + i*self.delta
                y = self.yrange[0] + j*self.delta
                yield (x, y)                        

    def s(self, x, y):
        return (x, self.f(x, y), y)

    def f(self, x, y):
        return math.exp(-10*(x**2 + y**2))
        

s = Surface()
s.set(RENDER)
