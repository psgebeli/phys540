set key bottom right
plot[][0:1] "rng-test.dat" using 2:1 title "uniform [0,1)", x
pause -1
plot[][:1] "rng-test.dat" using 3:1 title "gaussian", 0.5*(1+erf(x/sqrt(2)))
pause -1