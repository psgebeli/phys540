import math
import sys

if len(sys.argv) != 3:
    print('usage: python3 koch.py <recursion-depth> fill|outline')
    exit()

depth = int(sys.argv[1])
if depth < 0 or depth > 20:
    print('usage: python3 kock.py <recursion-depth> fill|outline')
    print('                        ^^^^^^^^^^^^^^^')
    print('                        0 <= depth <= 20')
    exit()

is_filled = False
if sys.argv[2] == "fill":
    is_filled = True;
elif sys.argv[2] != "outline":
    print('usage: python3 kock.py <recursion-depth> fill|outline')
    print('                                         ^^^^^^^^^^^^')
    print('                                 specify drawing mode')
    exit()

z = math.sqrt(3.0)/2.0
third = 1.0/3.0
points = [ (0,0), (1,0), (0.5,z) ]
print('Base case with {} points'.format(len(points)))
for p in points:
    print(p)
print("")

def fractal(p, q):
    dx = q[0]-p[0]
    dy = q[1]-p[1]
    hyp = math.sqrt(dx*dx + dy*dy)
    cos = dx/hyp
    sin = dy/hyp
    # (0,0)--(1,0) ==> (0,0)--(1/3,0)--(1/2,z/3)--(2/3,0)--(1,0)
    return [ p, (p[0]+hyp*third*cos, p[1]+hyp*third*sin),
            (p[0]+hyp*0.5*cos+hyp*third*z*sin,
             p[1]+hyp*0.5*sin-hyp*third*z*cos),
            (p[0]+hyp*2*third*cos, p[1]+hyp*2*third*sin) ]

for n in range(depth):
    lp = len(points)
    newpoints = []
    for i in range(lp):
        for pp in fractal(points[i], points[(i+1)%lp]):
            newpoints.append(pp)
    points = newpoints

print('Final case with {} points'.format(len(points)))
for p in points:
    print(p)

# generate the graphic with an Encapsulated PostScript file
with open('snowflake{}.eps'.format(depth),'w') as f:
    print('%!PS-Adobe-3.0 EPSP-3.0', file=f)
    print('%%BoundingBox: 0 0 400 400', file=f)
    print('newpath', file=f)
    for idx, p in enumerate(points):
        cmd = 'moveto' if idx==0 else 'lineto'
        print('{} {} '.format(100+200*p[0], 100+200*p[1]) + cmd, file=f)
    print('closepath', file=f)
    if is_filled:
        print('0.85 0.15 0.15 setrgbcolor', file=f)
        print('fill', file=f)
    else:
        print('0.8 0.9 1.0 setrgbcolor', file=f)
        print('0.1 setlinewidth', file=f)
        print('stroke', file=f)

