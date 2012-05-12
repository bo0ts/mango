import Geometry

class Tree(Core.Object):
    def __init__(self, trunk_height = 1.0, foliage_radius = 1.0):
        Core.Object.__init__(self)
        self.trunk = Geometry.Cylinder()
        self.trunk.setColor(0.5, 0.25, 0)
        self.trunk.setRadius(trunk_height / 10.0)
        self.trunk.setHeight(trunk_height)
        
        self.foliage = Geometry.Sphere()
        self.foliage.setColor(0.0, 0.8, 0.0)
        self.foliage.setRadius(foliage_radius)
        self.foliage.position = (0, trunk_height/2.0 + foliage_radius, 0)
        
        self.trunk.setParentFrame(self)
        self.foliage.setParentFrame(self)

    def set(self, mask):
        Core.Object.set(self, mask)
        self.trunk.set(mask)
        self.foliage.set(mask)    

    def unset(self, mask):
        Core.Object.unset(self, mask)
        self.trunk.unset(mask)
        self.foliage.unset(mask)    
            
    def toggle(self, mask):
        Core.Object.toggle(self, mask)
        self.trunk.toggle(mask)
        self.foliage.toggle(mask)    

if __name__ == '__main__':
    t = Tree()
    t.set(RENDER)
    Camera.lookFrom((3, 1, 3))
    Camera.translate(0, 1, 0)

