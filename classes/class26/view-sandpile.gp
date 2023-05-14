! make sandpile
! test -e sand.dat || ./sandpile > sand.dat
! ./hist-size.bash
! ./hist-time.bash

set logscale

f(x) = 1.0/(1+a*x)**b
a=3.0
b=1.25
fit[10:500] f(x) "hist-size.dat" using 0:2 via a,b

set title "Sandpile model frequency histograms"
plot[:1000][5E-6:] \
   "hist-size.dat" using 0:2 title "by size" w l, \
   f(x) title "powerlaw fit to size", \
   "hist-time.dat" using 0:2 title "by time" w l