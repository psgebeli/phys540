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

def sweep_grid(p):
    global cluster_size
    made_change = False
    Nrows = len(grid)
    for i in range(Nrows):
        Ncols = len(grid[i])
        for j in range(Ncols):
            if grid[i][j] == NA:
                xnbs = []
                if i > 0:
                    xnbs.append(i-1)
                xnbs.append(i)
                if i < Nrows-1:
                    xnbs.append(i+1)
                ynbs = []
                if j > 0:
                    ynbs.append(j-1)
                ynbs.append(j)
                if j < Ncols-1:
                    ynbs.append(j+1)
                if_nb_ON = False
                for ii in xnbs:
                    for jj in ynbs:
                        if (not (i == ii and j == jj)) and grid[ii][jj] == ON:
                            is_nb_ON = True
                if is_nb_ON:
                    made_change = True
                    if (random.random() < p):
                        grid[i][j] = ON
                        cluster_size = cluster_size + 1
                    else:
                        grid[i][j] = OFF
    return made_change

#def grow_grid():
    # expand the grid wherever an ON reaches the perimeter

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

sweep_grid(0.4)
display()
