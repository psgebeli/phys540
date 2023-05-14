# ! ./root 3 --verbose > sqrt3.dat
! echo "" > sqrt3.dat

! echo >> sqrt3.dat
! echo >> sqrt3.dat
! python3 seriesroot.py 2 -1 $(seq 30) >> sqrt3.dat
! echo >> sqrt3.dat
! echo >> sqrt3.dat
! python3 seriesroot.py 1.5 0.75 $(seq 30) >> sqrt3.dat
! echo >> sqrt3.dat
! echo >> sqrt3.dat
! python3 seriesroot.py 1.75 -0.0625 $(seq 30) >> sqrt3.dat


set title "Expansion of sqrt(a^2+b)"
set xlabel "truncation order of expansion"
set ylabel "series summation"

plot[0:10] "sqrt3.dat" index 0 title "Heron" with linespoints,\
           "sqrt3.dat" index 1 title "sqrt(2^2-1)" with linespoints,\
           "sqrt3.dat" index 2 title "sqrt(1.5^2+0.75)" with linespoints, \
           "sqrt3.dat" index 3 title "sqrt(1.75^2-0.0625)" with linespoints, sqrt(3.0)

pause -1

set logscale y
set ylabel "deviation from sqrt(3)"

plot "sqrt3.dat" index 0 using 1:(abs($2-sqrt(3.0))) title "Heron" with linespoints,\
     "sqrt3.dat" index 1 using 1:(abs($2-sqrt(3.0))) title "sqrt(2^2-1)" with linespoints,\
     "sqrt3.dat" index 2 using 1:(abs($2-sqrt(3.0))) title "sqrt(1.5^2+0.75)" with linespoints,\
     "sqrt3.dat" index 3 using 1:(abs($2-sqrt(3.0))) title "sqrt(1.75^2-0.0625)" with linespoints
     
unset logscale
