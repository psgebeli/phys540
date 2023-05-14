! make kpz3
! test -e height-sticky.dat || ./kpz3 sticky > height-sticky.dat
! test -e height-nonstick.dat || ./kpz3 nonstick > height-nonstick.dat

set terminal dumb ansi256

set xlabel "measurements (one per N/2 drops)"

set ylabel "maximum height"
plot "height-sticky.dat" u 1:2 w l title "sticky", \
     "height-nonstick.dat" u 1:2 w l title "nonstick"
call "../../scripts/set-png.gp" "hmax.png"

pause -1

set ylabel "mean height"
plot "height-sticky.dat" u 1:3 w l title "sticky", \
     "height-nonstick.dat" u 1:3 w l title "nonstick"
call "../../scripts/set-png.gp" "hmean.png"

pause -1

set ylabel "variance of height from the mean"
plot "height-sticky.dat" u 1:4 w l title "sticky", \
     "height-nonstick.dat" u 1:4 w l title "nonstick"
call "../../scripts/set-png.gp" "hvar.png"

pause -1

