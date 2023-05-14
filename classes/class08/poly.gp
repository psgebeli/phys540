! test -e poly.dat || python3 polynomial.py

set terminal dumb ansi256
plot "poly.dat" u 1:2 w l title "p(x)",\
     "" u 1:3 w l title "q(x)",\
     "" u 1:4 w l title "p(x)^2 - q(x)^2"

call '../../scripts/set-png.gp' 'poly.png'
