set fit errorvariables

e(x) = e0 + e1*x
f(x) = f0 + f1*x + f2*x**2
g(x) = g0 + g1*x + g2*x**2 + g3*x**3

fit e(x) "trip.dat" using 1:2 via e0,e1
fit f(x) "trip.dat" using 1:2 via f0,f1,f2
fit g(x) "trip.dat" using 1:2 via g0,g1,g2,g3

set xlabel "N"
set ylabel "number of valid 0-N triples"
set logscale y
plot "trip.dat" using 1:2 title "exact", e(x), f(x), g(x)
