! test -e sum.dat || ./sum > sum.dat

set title "Comparison of summation directions"
set xlabel "series cutoff"
set ylabel "accumulated value"

set logscale x
plot[][:25] "sum.dat" using 1:2 title "sum up" with linespoints, \
     "sum.dat" using 1:3 title "sum down" with points, \
     log(x) + 0.57721566490153286061 + 1.0/(2*x) + 1.0/(12*x**2) \
     title "asymptotic"

unset logscale
