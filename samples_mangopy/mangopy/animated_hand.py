import math, handlib

class OscillatingHand(handlib.Hand):
    def __init__(self):
        handlib.Hand.__init__(self)
        self.t = 0
        self.dflex = 0.02

    def step(self):
        for i in range(4):
            self.flex(self.dflex * (math.sin(self.t + i)), i)
            self.t += 0.01

h1 = OscillatingHand()
h1.set(STEP | RENDER)

Camera.lookFrom((4, 3, 4))
Camera.translate(0, 1, 0)
