set terminal dumb ansi256
set pm3d map
set size square
set key off
splot "phi.dat" matrix

call '../../scripts/set-png.gp' 'phi.png'
