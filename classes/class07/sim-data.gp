set terminal dumb ansi256
set key top left

plot \
     "sim-data.dat" u 1:2 w l title "raw data", \
     for [s = 3:7:2] "sim-data-smooth".s.".dat" u 1:2 w l title "smooth ".s

call '../../scripts/set-png.gp' 'sim-data.png'
