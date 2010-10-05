import Geometry, math

class FingerSegment(Geometry.Box):
    def __init__(self, thickness, length):
        Geometry.Box.__init__(self)
        self.pivot = Core.Frame()
        self.setParentFrame(self.pivot)
        self.setDimensions(thickness, thickness, length)
        self.translate(0, 0, -length/2.0)
        self.top = (0, 0, -length + thickness/6.0)
        self.segments = []

    def update(self, dgamma):
        if dgamma > 0 and self.pivot.beta < 90:
            self.pivot.beta += dgamma*90
        elif dgamma < 0 and self.pivot.beta > 0:
            self.pivot.beta += dgamma*90
        for segment in self.segments:
            segment.update(dgamma)


class Hand(Geometry.Box):
    fingers = []
    dflex = 0.02
    t = 0

    def step(self):        
        """
        if Keyboard.down(KEY_UP):
            self.flex(self.dflex)
        if Keyboard.down(KEY_DOWN):
            self.flex(-self.dflex)
        if Keyboard.down(ord('q')):
            self.flex(self.dflex, 4)
        if Keyboard.down(ord('a')):
            self.flex(-self.dflex, 4)
        if Keyboard.down(ord('w')):
            self.flex(self.dflex, 0)
        if Keyboard.down(ord('s')):
            self.flex(-self.dflex, 0)
        if Keyboard.down(ord('e')):
            self.flex(self.dflex, 1)
        if Keyboard.down(ord('d')):
            self.flex(-self.dflex, 1)
        if Keyboard.down(ord('r')):
            self.flex(self.dflex, 2)
        if Keyboard.down(ord('f')):
            self.flex(-self.dflex, 2)
        if Keyboard.down(ord('t')):
            self.flex(self.dflex, 3)
        if Keyboard.down(ord('g')):
            self.flex(-self.dflex, 3)
            """
        for i in range(4):
            self.flex(self.dflex * (math.sin(self.t + i)), i)
        self.t += 0.03
        
    def flex(self, delta, findex = -1):
        if findex == -1:
            for finger in self.fingers:
                finger.update(delta)
        else:
            self.fingers[findex].update(delta)

    def knuckles(self, i):
        w, h, l  = self.dimensions()
        if (i != 4):
            return (-1.0 + 0.667*i, 0, -l*0.45)
        else:
            return (-1.2, 0, -l*0.08)

    def finger_orientations(self, i):
        if i != 4:
            return (5 - 5 * i, 0, 0)
        else:
            return (35, 0, 0)

left = Hand()
left.setDimensions(2.5, 0.5, 2.8)
for i in range(5):
    fa = FingerSegment(0.5, 1.2)
    fa.set(RENDER)
    fa.pivot.setOrientation(*left.finger_orientations(i))
    left.fingers.append(fa)

    fb = FingerSegment(0.5, 1.1)
    #fb.setColor(0.0, 0.2, 1.0)
    fb.set(RENDER)
    fb.pivot.position = fa.top
    fb.pivot.setParentFrame(fa.pivot)
    fa.segments.append(fb)

    fa.pivot.position = left.knuckles(i)

    if i == 4:
        continue

    fc = FingerSegment(0.5, 0.5)
    #fc.setColor(0.0, 0.4, 1.0)
    fc.set(RENDER)
    fc.pivot.position = fb.top
    fc.pivot.setParentFrame(fb.pivot)
    fb.segments.append(fc)
    


left.set(RENDER | STEP)

