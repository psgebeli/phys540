! ./collect.bash

unset key
plot atan(0.25), atan(0.5), atan(0.75), atan(1.0), atan(1.05),\
     "series.dat" using 1:2 with linespoints
