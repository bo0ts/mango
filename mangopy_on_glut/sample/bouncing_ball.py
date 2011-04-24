import Geometry, math

class BouncingBall(Geometry.Sphere):
    t = 0
    def step(self):
        self.t += 0.08
        self.position = (0, 0.2 + abs(math.sin(self.t)), 0)

class MovingPlatform(Geometry.Box):
    t = 0
    def step(self):
        self.t += 0.01
        self.position = (math.sin(self.t), 0, 0)

platform = MovingPlatform()
platform.setDimensions(1.0, 0.1, 1.0)
ball = BouncingBall()
ball.setRadius(0.2)
ball.setParentFrame(platform)

ball.set(RENDER | STEP)
platform.set(RENDER | STEP)

Camera.lookFrom((0, 2, 3))
Camera.translate(0, 0.7, 0)
