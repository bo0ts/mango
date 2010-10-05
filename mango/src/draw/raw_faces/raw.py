#! /usr/bin/python3
import glob


raw_files = glob.glob("*.raw")
outfname = "raw_character_data.cpp"

vertices = []
amap = {}
global_y_min = 0
global_y_max = 0

amap[32] = {'start':0, 'length':0, 'width':0.35, 'char':' '}
for raw_file in raw_files:
    with open(raw_file, 'r') as rf:
        raw_lines = rf.readlines()        
        
        letter_vertices = []
        
        char = raw_lines[0][0]
        char_ord = ord(char)
        raw_lines[0] = raw_lines[0][1:]    

        letter_min = 100
        letter_max = -100

        for raw_line in raw_lines:
            raw_vertices = raw_line.split(" ")
            for i in range(0, len(raw_vertices), 3):
                xv = raw_vertices[i]
                if xv == "\n": 
                    continue
                yv = raw_vertices[i + 1]

                letter_min = (float(xv) if float(xv) < float(letter_min) else letter_min)
                letter_max = (float(xv) if float(xv) > float(letter_max) else letter_max)

                global_y_min = (float(yv) if float(yv) < global_y_min else global_y_min)
                global_y_max = (float(yv) if float(yv) > global_y_max else global_y_max)

                letter_vertices.extend([xv, yv])
        
        letter_width = (letter_max - letter_min) if (letter_max != -100 and letter_min != -100) else 0
        char = ('(pound)' if char == '#' else char)
        char = ('(backslash)' if char == "\\" else char)
        char = ('(backtick)' if char == '`' else char)
        amap[char_ord] = {'start': len(vertices), 'length':len(letter_vertices), 'width':letter_width, 'char':char}
        vertices.extend(letter_vertices)

        
vertices_array_def = "    GLfloat raw_vertices[] = {%s};" % ", ".join(vertices)

map_array_data = ""
for i in range(128):
    try:
        info = amap[i]
        map_array_data += "{%s, %s, %s}, // %s \n" % (info['start'], info['length'], round(1000*info['width']), info['char']) 
    except KeyError:
        map_array_data += "{-1, -1, -1}, // ord %s \n" % i

map_array_def = "    int ord_map[][3] = {%s};" % map_array_data 

global_y_min_def = "    GLfloat row_min_height = %s;" % global_y_min
global_y_max_def = "    GLfloat row_max_height = %s;" % global_y_max


"""
for i in range(128):
    try:
        info = amap[i]
        map_array_def += "\nord_map[%s][0] = %s; //%s" % (i, info['start'], info['char'])
        map_array_def += "\nord_map[%s][1] = %s; //%s" % (i, info['length'], info['char'])
    except KeyError:
        map_array_def += "\nord_map[%s][0] = -1;" % (i)
"""

with open(outfname, 'w') as outf:
    outf.write("""
#include "raw_character_data.h"

namespace Mango{
  namespace Draw{
""")
    outf.write(vertices_array_def)
    outf.write("\n\n\n")
    outf.write(map_array_def)
    outf.write("\n\n")
    outf.write(global_y_min_def)
    outf.write("\n")
    outf.write(global_y_max_def)
    outf.write("""
  } // Draw
} // Mango
""")


    
    
