import Geometry

v_focus = Geometry.Sphere()
v_focus.setParentFrame(Camera.parentFrame())
v_focus.set(RENDER)
v_focus.setRadius(0.2)

class CameraTracker(Core.Object):
    def step(self):
        camera_parent = Camera.parentFrame()
        print("\n\n-----------")
        print("Camera: ", Camera.position, "   ", Camera.orientation())
        print("Focus: ", camera_parent.position, "   ", camera_parent.orientation())
        pos = Camera.position
        pos[2] = 0
        v_focus.position = pos

gcs = Geometry.CoordinateSystem()
gcs.set(RENDER)


b = Geometry.Box()
b.position = Vector(1, 1, 1)
b.rotate(34, 56, 0)
b.set(RENDER)





focus_cs = Geometry.CoordinateSystem()
focus_cs.setParentFrame(Camera.parentFrame())
focus_cs.set(RENDER)

tracker = CameraTracker()
tracker.set(STEP)
