set fit errorvariables

e(x) = e0 + e1*x
f(x) = f0 + f1*x + f2*x**2
g(x) = g0 + g1*x + g2*x**2 + g3*x**3
h(x) = h0 + h1*x + h2*x**2 + h3*x**2 + h4*x**4

fit e(x) "quad.dat" using 1:2 via e0,e1
fit f(x) "quad.dat" using 1:2 via f0,f1,f2
fit g(x) "quad.dat" using 1:2 via g0,g1,g2,g3
fit h(x) "quad.dat" using 1:2 via h0,h1,h2,h3,h4

set xlabel "N"
set ylabel "number of valid 0-N quadruples"
set logscale y
plot "quad.dat" using 1:2 title "exact", e(x), f(x), g(x), h(x)