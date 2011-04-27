import time

class OnScreenMessage(Core.Object):
    msg = ""
    last_show_time = 0
    text_size = 30
    delay = 1.0
    color = (0.6, 0.2, 0.2)

    def draw(self):
        self.transform()
        glColor(self.color)
        for i, line in enumerate(self.msg):
            Draw.text((0, -i*self.text_size), line, self.text_size)
        self.hide_if_its_time()

    def setMessage(self, msg):
        self.msg = msg.split("\n")

    def show(self, msg = None):
        if msg != None:
            self.setMessage(msg)
        self.set(DRAW)
        self.last_show_time = time.time()

    def hide_if_its_time(self):
        if time.time() - self.last_show_time >= self.delay:
            self.hide()

    def hide(self):        
        self.unset(DRAW)



class Prompt(Core.Object):
    key_press = Core.InputEvent(KEYBOARD, PRESS, ANY)
    confirm = Core.InputEvent(KEYBOARD, PRESS, KEY_ENTER)
    cancel = Core.InputEvent(KEYBOARD, PRESS, KEY_ESCAPE)
    default_allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYS0123456789 .,!@#$%^&*()_-=+/"
    text_size = 30
    color = (0, 0.2, 0.7)

    def __init__(self, msg = ""):
        Core.Object.__init__(self)
        self.callback = None
        self.set_allowed_chars(self.default_allowed_chars)

    def draw(self):
        self.transform()
        glColor(self.color)        
        Draw.text((0, 0), self.msg, self.text_size)

    def input(self, evt):
        if evt == self.key_press:
            if evt.code in self.allowed_codes:
                self.msg += chr(evt.code)
            elif (evt.code in [KEY_DELETE, KEY_BACKSPACE]) and (len(self.msg) > self.editable_index):
                self.msg = self.msg[:-1]
        
        if evt == self.confirm:            
            self.execute_callback()
            self.unset(DRAW | INPUT)
        elif evt == self.cancel:
            self.unset(DRAW | INPUT)
        

    def set_allowed_chars(self, chars):
        self.allowed_codes = [ord(c) for c in chars]

    def set_editable_index(self, index):
        self.editable_index = index

    def set_msg(self, msg):
        self.msg = msg

    def set_callback(self, callback, context = None):
        self.callback = callback        
        self.callback_context = context

    def ask(self, msg):
        self.set_msg(msg)
        self.set_editable_index(len(msg))
        self.set(DRAW | INPUT)

    def active(self):
        return self.executes(DRAW | INPUT)

    def last_answer(self):
        return self.msg[self.editable_index:]

    def execute_callback(self):
        if self.callback:
            self.callback(self.last_answer(), self.callback_context)




class Label(Core.Object):
    def __init__(self, str):
        Core.Object.__init__(self)
        self.str = str
        self.color = (1.0, 0.3, 0.0)
        self.text_size = 0.3
    
    def render(self):
        glColor(self.color)
        self.transform()        
        Draw.text((0, 0), self.str, self.text_size)
        
    def step(self):
        camera_parent = Camera.parentFrame()
        camera_pos = camera_parent.transformToParent(Camera.position)        
        self.pointTo(camera_pos)
        self.rotate(0, -90, 0)


class FpsDisplay(Core.Object):    
    
    def __init__(self):
        Core.Object.__init__(self)
        w, h = Engine.windowDimensions()
        self.color = (1.0, 0.5, 0.0)
        self.text_size = 20
        self.position = (-w/2.0 + 10, h/2.0 - 10)
        

    def draw(self):
        self.transform()
        fps = Engine.actualFps()
        glColor(self.color)
        Draw.text((0, 0), "FPS: %.0f" % fps, self.text_size)
