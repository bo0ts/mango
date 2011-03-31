import Geometry, math

class BouncingBall(Geometry.Sphere):
    t = 0
    delta = 0.1
    paused = False

    def step(self):
        self.handle_input()
        self.bounce()      

    def bounce(self):
        self.t += (self.delta if not self.paused else 0)
        self.position = (0, 0.2 + abs(math.sin(self.t)), 0)

    def handle_input(self):
        if Keyboard.down(KEY_UP):
            self.delta += 0.01
        elif Keyboard.down(KEY_DOWN):
            self.delta -= 0.01

    def input(self, event):
        if event == Core.InputEvent(KEYBOARD, RELEASE, KEY_SPACE):            
            self.paused = not self.paused

platform = Geometry.Box()
platform.setDimensions(1.0, 0.1, 1.0)
ball = BouncingBall()
ball.setRadius(0.2)

ball.set(RENDER | STEP | INPUT)
platform.set(RENDER | STEP)
