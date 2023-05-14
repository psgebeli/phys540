import random

def ps(filebase,n,H):
    with open(filebase+str(n)+".ps","wt") as f:
        f.write("%!\n")
        f.write("%%BoundingBox: 0 0 400 400\n")
        f.write("/mkbox {\n")
        f.write("   newpath\n")
        f.write("   moveto\n")
        f.write("   0 1 rlineto\n")
        f.write("   1 0 rlineto\n")
        f.write("   0 -1 rlineto\n")
        f.write("   closepath\n")
        f.write("   1 0 0 setrgbcolor\n")
        f.write("   fill\n")
        f.write("} def\n")
        f.write("{} {} scale\n".format(400./(1+N), 400./(1+N)))
        for x in range(N):
            for y in H[x]:
                f.write("{} {} mkbox\n".format(x,y))
        f.write("showpage\n")

N = 250
H = []
for _ in range(N):
   H.append([0])

# [ [0], [0], ... ] 

n = 0
#maxh = 0
for drops in range(75*N):
    i = random.randrange(1,N-1)
    h = max( H[i-1][-1], H[i][-1]+1, H[i+1][-1] )
    #h = H[i][-1]+1
    H[i].append(h)
    #if (h > maxh):
    #    maxh = h
    #print("{} {}".format(drops,maxh))
    if drops%(N//2)==0:
        n += 1
        ps("snapshot",n,H)
