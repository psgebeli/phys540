# grow a typical single cluster
import sys
import random

# some constants that serve as numerical aliases
NA = -1 # Not Assigned
OFF = 0
ON = 1

# cluster is seeded with a single ON cell
cluster_size = 1
grid = [ [NA, NA, NA],
         [NA, ON, NA],
         [NA, NA, NA] ]

def has_ON_neighbour(i,j):
    if i > 0:
        if grid[i-1][j] == ON:
            return True
    if i+1 < len(grid):
        if grid[i+1][j] == ON:
            return True
    if j > 0:
        if grid[i][j-1] == ON:
            return True
    if j+1 < len(grid[i]):
        if grid[i][j+1] == ON:
            return True
    return False

def sweep_grid(p):
    # for each cell, assign NA -> ON or OFF if there is a
    # neighbouring ON cell
    global cluster_size
    made_change = False
    Nrows = len(grid)
    for i in range(Nrows):
        Ncols = len(grid[i])
        for j in range(Ncols):
            if grid[i][j] == NA and has_ON_neighbour(i,j):
                made_change = True
                if (random.random() < p):
                    grid[i][j] = ON
                    cluster_size = cluster_size + 1
                else:
                    grid[i][j] = OFF
    return made_change

def grow_grid():
    # expand the grid wherever an ON reaches the perimeter
    # grow top
    if NA not in grid[0] and ON in grid[0]:
        Ncols = len(grid[0])
        grid.insert(0,[NA]*Ncols)
    # grow bottom
    Nrows = len(grid)
    if NA not in grid[Nrows-1] and ON in grid[Nrows-1]:
        Ncols = len(grid[Nrows-1])
        grid.append([NA]*Ncols)
    # grow left
    testNA = True
    testON = False
    Nrows = len(grid)
    for i in range(1, Nrows-1):
        if grid[i][0] == NA:
            testNA = False
        if grid[i][0] == ON:
            testON = True
    if testNA and testON:
        for i in range(Nrows):
            grid[i].insert(0,NA)
    # grow right
    testNA = True
    testON = False
    Nrows = len(grid)
    for i in range(1, Nrows-1):
        Ncols = len(grid[i])
        if grid[i][Ncols-1] == NA:
            testNA = False
        if grid[i][Ncols-1] == ON:
            testON = True
    if testNA and testON:
        for i in range(Nrows):
            grid[i].append(NA)

def display():
    Nrows = len(grid)
    for i in range(Nrows):
        Ncols = len(grid[i])
        for j in range(Ncols):
            if (grid[i][j] == ON):
                print("o",end="")
            else:
                print(" ",end="")
        print("")

def verify_cluster_size():
    count = 0
    Nrows = len(grid)
    for i in range(Nrows):
        Ncols = len(grid[i])
        for j in range(Ncols):
            if (grid[i][j] == ON):
                count += 1
    return count

def usage():
    print("usage: python3 perc4.py (0 < p < 1) (draw|report)")
    exit(1)

if not len(sys.argv) == 3:
    usage()

prob = float(sys.argv[1])

if prob < 0.0 or prob > 1.0:
    usage()

is_draw = (sys.argv[2] == "draw")
is_report = (sys.argv[2] == "report")
if not is_draw and not is_report:
    usage()

while sweep_grid(prob):
    grow_grid()

if is_draw:
    display()
    print("Cluster size is {}".format(cluster_size))
    print("Cluster size is {}".format(verify_cluster_size()))
    quit()

if is_report:
    print(cluster_size)
