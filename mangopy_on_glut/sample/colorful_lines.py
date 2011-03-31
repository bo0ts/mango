from random import random

def random_pt():
    return (-2 + 4*random(), -2 + 4*random(), -2 + 4*random())

def random_color():
    return (random(), random(), random())


class ColorfulSticks(Core.Object):
    lines = [(
            random_pt(),
            random_pt(),
            random_color()
            ) for i in range(30)]
    
    def render(self):
        for pt1, pt2, color in self.lines:
            glColor(color)
            Draw.line(pt1, pt2)


cs = ColorfulSticks()
cs.set(RENDER)
