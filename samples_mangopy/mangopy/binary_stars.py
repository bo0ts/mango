from demo import OnScreenMessage
from math import sin, cos, sqrt
import random, time


class binaryStarSystem(Core.Object):
    e_toggle_particles = Core.InputEvent(KEYBOARD, PRESS, KEY_SPACE)
    e_toggle_centripetal = Core.InputEvent(KEYBOARD, PRESS, ord('c'))

    M2_over_M1 = 0.5
    a = 200
    primaryThreshold = -12.0
    secondaryThreshold = -12.0

    screen_width = 640.0
    screen_height = 480.0
    vertical_offset = -100
    
    CM = None
    r1 = None
    r2 = None    

    phiIncludeCentripetalForce = False
    primaryStarParticles = None
    secondaryStarParticles = None

    screenMessage = None
    
    def __init__(self):
        Core.Object.__init__(self)

        # Calculate/Set the position-information
        self.CM = Vector()
        self.centerOfScreen = (0, 250, 0)
        self.calculateRs()
        self.calculateRadii()
        self.position = self.CM        

        # Set up the primaryParticles variables
        self.createdPrimaryStarParticles = False
        self.primaryStarParticles = []
        self.secondaryStarParticles = []

        # Create the on-screen message
        self.screenMessage = OnScreenMessage()
        self.screenMessage.position = (-310, 230, 0)        
        self.screenMessage.set(DRAW) 

        

        
    def drawStars(self, primary_radius):        
        glPushMatrix()
        glTranslate(self.centerOfScreen[0], self.centerOfScreen[1] + self.vertical_offset, 0)
        glColor(1.0, 0, 0)
        Draw.circle((self.r1, 0, 0), primary_radius, True)
        Draw.circle((self.r1 + self.a, 0, 0), primary_radius*self.M2_over_M1, True)
        glPopMatrix()
        
    def drawCM(self):
        glColor(0.0, 1.0, 0.0)
        glBegin(GL_LINES)
        glVertex(self.CM[0] + 2, self.CM[1] + self.vertical_offset + 2)
        glVertex(self.CM[0] - 2, self.CM[1] + self.vertical_offset - 2)
        glVertex(self.CM[0] + 2, self.CM[1] + self.vertical_offset - 2)
        glVertex(self.CM[0] - 2, self.CM[1] + self.vertical_offset + 2)
        glEnd()

    def draw(self):            
        self.drawStars(10)                
        self.drawCM()        

    def render(self):
        self.plotPhiSurface()


    def input(self, evt):
        if evt == self.e_toggle_centripetal:
            self.phiIncludeCentripetalForce = not self.phiIncludeCentripetalForce
        elif evt == self.e_toggle_particles:
            if not self.createdPrimaryStarParticles:
                self.createStarParticles()
            else:
                self.destroyStarParticles()
                
            

    def step(self):
        if Keyboard.down(KEY_LEFT) and self.a > 25:
            self.updateA(self.a - 2)
            self.screenMessage.show("Seperation: %.2f R" % (self.a/self.primaryRadius))                
        elif Keyboard.down(KEY_RIGHT):
            self.updateA(self.a + 2)
            self.screenMessage.show("Seperation: %.2f R" % (self.a/self.primaryRadius))
        elif Keyboard.down(KEY_DOWN) and self.M2_over_M1 > 0.14:    
            self.updateM2_over_M1(self.M2_over_M1 - 0.05)
            self.screenMessage.show("M2 = %.2f M1" % (1.0/self.M2_over_M1))
        elif Keyboard.down(KEY_UP) and self.M2_over_M1 < 0.96:
            self.updateM2_over_M1(self.M2_over_M1 + 0.05)
            self.screenMessage.show("M2 = %.2f M1" % (1.0/self.M2_over_M1))
            
            

    def calculateRs(self):
        self.r1 = -100
        self.r2 = self.r1 + self.a
        self.CM[0] = self.centerOfScreen[0] + (self.r1 + self.M2_over_M1*self.r2)/(1 + self.M2_over_M1)
        self.CM[1] = self.centerOfScreen[1]
        self.CM[2] = 0

    def calculateRadii(self):
        # Find the primaryRadius, the leftmost point on the graph of Phi that is equal to primaryThreshold
        self.primaryRadius = 0
        P1 = self.primaryStarPosition()
        while self.Phi(P1[0] - self.primaryRadius, P1[1]) <= self.primaryThreshold:
            self.primaryRadius += 0.1

        self.secondaryRadius = 0
        P2 = self.secondaryStarPosition()        
        while self.Phi(P2[0] + self.secondaryRadius, P2[1]) <= self.secondaryThreshold:
            self.secondaryRadius += 0.1


    def updateA(self, a):
        self.a = a
        self.calculateRs()

    def updateM2_over_M1(self, M2_over_M1):
        self.M2_over_M1 = M2_over_M1
        self.calculateRs()
        self.calculateRadii()

        # This relationship is not derived from any physical laws, it just seems to work well        
        self.secondaryThreshold = self.primaryThreshold - (1.0 - self.M2_over_M1)*4.0


    def Phi(self, sx, sy):
        x = sx - self.CM[0]
        y = sy - self.CM[1]

        r1 = (self.centerOfScreen[0] - self.CM[0]) + self.r1
        r2 = self.centerOfScreen[0] + (self.r2 - self.CM[0])
        s1 = 0.1*sqrt( (x-r1)**2 + y**2 )
        s2 = 0.1*sqrt( (x-r2)**2 + y**2 )

        if (s1 <= 0.001 or s2 <= 0.001):
            return -50
        else:
            local_a = 100
            Phi = -(local_a/s1)* (1 + self.M2_over_M1*s1/s2)/(1+self.M2_over_M1)
            if Phi < -50:
                return -50
            if self.phiIncludeCentripetalForce:
                Phi -= (x**2 + y**2)/(2*local_a*local_a)
            return Phi

    def primaryPsuedoPressurePotential(self, sx, sy):
        x = sx - self.CM[0]
        y = sy - self.CM[1]

        s1 = 0.1*sqrt( (x-self.r1)**2 + y**2 )

        local_a = 100
        
        return (local_a/s1)
    

    def plotPhiSurface(self):
        N = 40
        phi_max = 100

        x_start = -320
        x_end = 320
        y_start = 0
        y_end = 480
        
        len_x = x_end - x_start
        len_y = y_end - y_start
        
        dx = round(len_x / N)
        dy = round(len_y / N)

        glScale(0.0125, 0.0125, 0.01)
        glTranslate(-100, 100, 0)
        glBegin(GL_QUADS)

        kx = 200/len_x
        ky = 200/len_y
        for x in range(0, len_x, dx):
            xnext = x + dx
            for y in range(0, len_y, dy):
                ynext = y + dy
                
                k = 10
                phi_x_y = k*self.Phi(x_start + x, y_start + y)
                phi_xnext_y = k*self.Phi(x_start + x + dx, y_start + y)
                phi_xnext_ynext = k*self.Phi(x_start + x + dx, y_start + y + dy)
                phi_x_ynext = k*self.Phi(x_start + x, y_start + y + dy)

                glNormal((phi_x_y-phi_xnext_y)*dy, (phi_x_y - phi_x_ynext)*dx, dx*dy)

                c = 1.0+phi_x_y/phi_max
                glColor(0.0, c, 1.0-c)
                
                glVertex(kx*x, phi_x_y, ky*y)
                glVertex(kx*xnext, phi_xnext_y, ky*y)
                glVertex(kx*xnext, phi_xnext_ynext, ky*ynext)
                glVertex(kx*x, phi_x_ynext, ky*ynext)

                glVertex(kx*x, phi_x_ynext, ky*ynext)
                glVertex(kx*xnext, phi_xnext_ynext, ky*ynext)
                glVertex(kx*xnext, phi_xnext_y, ky*y)
                glVertex(kx*x, phi_x_y, ky*y)

        glEnd()
        
    def primaryStarPosition(self):
        return Vector(self.centerOfScreen[0] + self.r1, self.centerOfScreen[1], 0)

    def secondaryStarPosition(self):
        return Vector(self.centerOfScreen[0] + self.r2, self.centerOfScreen[1], 0)

    def createStarParticles(self):
        num_secondary_particles = round(500 * self.M2_over_M1)
        for i in range(1000 - num_secondary_particles):                
            p = starParticle(binarySystem, binarySystem.primaryStarPosition(), self.primaryThreshold, self.primaryRadius - 10)
            self.primaryStarParticles.append(p)                    
            p.set(DRAW | STEP)
            
        for i in range(num_secondary_particles):
            p = starParticle(binarySystem, binarySystem.secondaryStarPosition(), self.secondaryThreshold, self.secondaryRadius - 10, (1.0, 0.5, 0.0))
            self.secondaryStarParticles.append(p)                    
            p.set(DRAW | STEP)
            
        self.createdPrimaryStarParticles = True

    def destroyStarParticles(self):
        for p in self.primaryStarParticles:
            p.unset(DRAW | STEP)
            del p
        for p in self.secondaryStarParticles:
            p.unset(DRAW | STEP)
            del p
        self.primaryStarParticles = []
        self.secondaryStarParticles = []
        self.createdPrimaryStarParticles = False


class starParticle(Core.Object):
    binarySystem = None

    radius = 5

    vertical_offset = -100
    threshold = None
    velocity = None
    color = None
    
    def __init__(self, binarySystem, position, threshold, max_random_r, color = (1.0, 1.0, 0.0)):
        Core.Object.__init__(self)

        self.binarySystem = binarySystem
        self.color = color
        self.threshold = threshold

        theta = 6.28 * random.random()
        self.position = (position + max_random_r*Vector(cos(theta), sin(theta), 0))

        # Generate a random velocity
        r =  2 + 2*random.random()
        theta = 6.28 * random.random()
        self.velocity = r*Vector(cos(theta), sin(theta), 0)


    def draw(self):
        self.transform()
        self.drawSquare()

    def drawSquare(self):
        glColor(self.color)
        glBegin(GL_POLYGON)
        for p in self.squarePoints(): glVertex(p) 
        glEnd()

    def squarePoints(self):
        return [(self.radius, self.vertical_offset),
         (0, self.radius + self.vertical_offset),
         (-self.radius, self.vertical_offset),
         (0, -self.radius + self.vertical_offset)]

        

    def step(self):            
        nextpos = self.position + self.velocity

        if binarySystem.Phi(nextpos[0], nextpos[1]) >= self.threshold:
            gradPhi = Vector(binarySystem.Phi(nextpos[0]+1, nextpos[1])-binarySystem.Phi(nextpos[0]-1, nextpos[1]), binarySystem.Phi(nextpos[0], nextpos[1]+1) - binarySystem.Phi(nextpos[0], nextpos[1]-1))
            gradPhi.normalize()
            self.velocity -= 2*self.velocity.dot(gradPhi)*gradPhi

        self.translate(self.velocity)
        


# Create the binary system
binarySystem = binaryStarSystem()
binarySystem.set(STEP | RENDER | DRAW | INPUT)

# Orient the camera
View.setMode(LOCK_ALL)
Camera.lookFrom((0, 3, 6), (0, 0, 1))


# Print out instructions
print("Contact Binary Star System Simulation")
print("")
print("Interface:")
print(" Up/Down:    Adjust mass ratio")
print(" Left/Right: Adjust seperation")
print(" Space:      Create/destroy particles")
print(" c:          Toggle rendering of centriptal force")
print("\n\n")


