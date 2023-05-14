f(x) = a*x*cos(b*x)*exp(-c*x)
fit f(x) "sim-data.dat" u 1:2 via a,b,c

set terminal dumb ansi256
plot "sim-data.dat" u 1:2 w p, f(x)
print "Best fit to f(x) = ", a, " x cos(", b, " x)exp(-", c, " x)"

call '../../scripts/set-png.gp' 'sim-data.png'
