! ./bob-damped.bash 

set terminal dumb ansi256
set key bottom left 

array d[4] = [0.001, 0.01, 0.1, 1]

plot[:5][-0.75:1] for [j=0:3] "bob-damped.dat" i j using 1:(-$2) with lines title sprintf("%1.3f", d[j+1]) 

call '../../scripts/set-png.gp' 'bob-damped.png'
