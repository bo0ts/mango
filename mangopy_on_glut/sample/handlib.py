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

    def __init__(self):
        Geometry.Box.__init__(self)
        self.fingers = []
        self.dflex = 0.02
        self.t = 0
        self.segments = []
        self.setDimensions(2.5, 0.5, 2.8)                
        for i in range(5):
            fa = FingerSegment(0.5, 1.2)
            fa.pivot.setParentFrame(self)
            fa.pivot.setOrientation(*self.finger_orientations(i))
            self.fingers.append(fa)
            self.segments.append(fa)
            
            fb = FingerSegment(0.5, 1.1)
            fb.pivot.position = fa.top
            fb.pivot.setParentFrame(fa.pivot)
            fa.segments.append(fb)            
            fa.pivot.position = self.knuckles(i)
            self.segments.append(fb)
            
            if i == 4:
                continue
            
            fc = FingerSegment(0.5, 0.5)
            fc.pivot.position = fb.top
            fc.pivot.setParentFrame(fb.pivot)
            fb.segments.append(fc)
            self.segments.append(fc)

        
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

    def set(self, mask):
        Geometry.Box.set(self, mask)
        for segment in self.segments:
            segment.set(mask)

    def unset(self, mask):
        Geometry.Box.unset(self, mask)
        for segment in self.segments:
            segment.unset(mask)

    def toggle(self, mask):
        Geometry.Box.toggle(self, mask)
        for segment in self.segments:
            segment.toggle(mask)





class OscillatingHand(Hand):
    def step(self):
        for i in range(4):
            self.flex(self.dflex * (math.sin(self.t + i)), i)
            self.t += 0.01

class BringItOnHand(Hand):
    def step(self):        
        self.flex(self.dflex * (math.sin(self.t)), 0)
        self.t += 0.06

