from demo import Prompt, OnScreenMessage
from math import *
import sys

class FunctionGrapher(Core.Object):
    def __init__(self):
        Core.Object.__init__(self)
        self.width = 640
        self.height = 480
        self.xmax = 10.0
        self.xmin = -10.0
        self.ymax = 10.0
        self.ymin = -10.0
        self.dx = 1.0

    def f(self, x):
        return x                    

    def draw(self):
        self.transform()        
        glBegin(GL_LINE_STRIP)
        glColor(1, 1, 1)        
        for pt in self.graph_points():            
            glVertex(pt)
        glEnd()
        
        
    def graph_points(self):
        y_scale = self.y_scale()
        for x, scaled_x in self.x_and_scaled_x():
            try:
                y = y_scale*self.f(scaled_x)
                if not type(y) in [int, float]:
                    raise ValueError("f yields invalid value %s" % y)
                yield (x, y)
            except ZeroDivisionError:
                continue

    def x_and_scaled_x(self):
        x_scale = self.x_scale()
        for i in range(self.x_range()):
            x = i*self.dx
            scaled_x = x*x_scale + self.xmin
            yield (x, scaled_x)

    def x_range(self):
        return int(self.width/self.dx)

    def x_scale(self):
        return (self.xmax - self.xmin)/self.width

    def y_scale(self):
        return self.height/(self.ymax - self.ymin)


class StringFunctionGrapher(FunctionGrapher):
    def __init__(self):
        FunctionGrapher.__init__(self)
        self.str_func = "x"

    def f(self, x):        
        return eval(self.str_func)

    def set_string_function(self, strfunc):
        oldfunc = self.str_func
        self.str_func = strfunc
        try:
            for pt in self.graph_points():
                pass
        except Exception as e:
            self.str_func = oldfunc
            raise ValueError("Error evaluating function\n%s" % e)
        


class GraphingInterface(Core.Object):
    enter_function = Core.InputEvent(KEYBOARD, PRESS, ord(' '))

    def __init__(self):
        Core.Object.__init__(self)
        self.graph = StringFunctionGrapher()
        self.prompt = Prompt()
        self.flash = OnScreenMessage()

        self.flash.position = (-310, 230)
        self.flash.text_size = 25
        self.flash.delay = 5.0
        self.flash.color = (0, 0.2, 0.7)
        self.prompt.position = (-310, 230)
        self.prompt.text_size = 25
        self.prompt.color = (0, 0.2, 0.7)
        self.prompt.set_callback(self.update_function)
        self.graph.position = (-320, 0)
        self.graph.set(DRAW)

    def input(self, evt):
        if (evt == self.enter_function) and not self.prompt.active():
            self.flash.hide()
            self.prompt.ask("Function: ")

    def update_function(self, new_func, context = None):
        try:
            self.graph.set_string_function(new_func)
        except Exception as e:            
            self.flash.show("Invalid function '%s':\n%s" % (new_func, e))
        else:
            self.flash.show("Graphing\nf(x) = %s" % new_func)        
     


gi = GraphingInterface()
gi.set(INPUT)
gi.update_function("sin(x)")

View.setMode(LOCK_ALL)

print("""
Function Grapher

Press space to set a new function, as an expression of x.
For example: 
  <space>
  sin(x) + 0.1*x**2
  <enter>

Functions from the math module are available, including: cos, sin, tan, abs, sqrt, ceil, factorial.
""")
