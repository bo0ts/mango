
"""
m = Core.Matrix()
v = Vector(1, 2, 3)
print(m)

print(3*m + m)

m = 3*m
print(m[1])
print(m.det())
print(m.tr())
"""

"""
m = Core.Matrix()
print(m)

"""
n = Core.Matrix((0, 0, 1),
                (0, 1, 0),
                (1, 0, 0))

print(n)

p = Core.Matrix((1, 2),(3, 4))
print(p)

v = Vector(2, 3)
print(p((2, 3)))

