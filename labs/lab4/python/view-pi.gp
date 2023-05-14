! python3 pi.py 25 > tmp.dat

f(x) = abs(x-pi)

set logscale y
set title "Convergence of series approximations to pi"
set xlabel "iterations"
set ylabel "discrepancy"

plot[0:26] "tmp.dat" using 1:(f($2)) title "arithmetic-geometric mean" with linespoints, \
           "tmp.dat" using 1:(f($3)) title "atan {4,1/2,4,1/5,4,1/8}" with linespoints, \
           "tmp.dat" using 1:(f($4)) title "atan {16,1/5,-4,1/239}" with linespoints, \
           "tmp.dat" using 1:(f($5)) title "atan {24,1/8,8,1/57,4,1/239}" with linespoints

unset logscale
