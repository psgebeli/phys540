set terminal dumb ansi256
set size square
set key off
u=0.03
plot "E.dat" using ($1-0.5*u*$3):($2-0.5*u*$4):(u*$3):(u*$4) with vectors filled head lt 5

call '../../scripts/set-png.gp' 'E.png'
