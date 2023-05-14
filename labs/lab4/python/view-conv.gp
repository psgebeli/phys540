! python3 series.py 0.99 > series.dat

set title "Convergence of series approximations to arctan(0.99)"
set xlabel "iterations"
set ylabel "value"

plot atan(0.99),\
     "series.dat" using 1:2 title "version 1" with linespoints,\
     "series.dat" using 1:3 title "version 2" with linespoints,\
     "series.dat" using 1:4 title "versions 3" with linespoints

