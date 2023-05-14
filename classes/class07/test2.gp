set terminal dumb ansi256
set key top left

plot \
     "test.dat" u 1:2 w l title "raw data", \
     for [s = 4:7] "test-smooth".s.".dat" u 1:2 w l title "smooth ".s  # .s is concatenation

call '../../scripts/set-png.gp' 'test2.png'
