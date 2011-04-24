from tree import Tree
from random import random

num = 25
positions = [(-2.5 + 5*random(), 0, -2.5 + 5*random()) 
             for i in range(num)]
trunk_sizes = [0.5 + 0.2 * random() for i in range(num)]
foliage_sizes = [0.2 + 0.2 * random() for i in range(num)]

forest = []
for pos, height, radius in zip(positions, trunk_sizes, foliage_sizes):
    tree = Tree(height, radius)
    tree.position = pos
    tree.set(RENDER)
    forest.append(tree)

            
Camera.lookFrom((0, 2, 7))
