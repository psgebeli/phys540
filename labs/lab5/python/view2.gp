! python3 orbit_vel.py > ov.dat

set size square

unset object
set object 1 rect from -100,-100 to 100,100 fc lt 1 lw 0
set title "satellite in earth orbit"
unset label
set xlabel "x position [km]"
set ylabel "y position [km]"
unset key

plot "ov.dat" using ($2*cos($3)):($2*sin($3)) w l
unset object

pause -1

set xlabel "time [hrs]"
set ylabel "radial velocity [km/hr]"
plot "ov.dat" using 1:4 w l

pause -1

set ylabel "angular velocity [radians/hr]"
plot "ov.dat" using 1:5 w l

pause -1 

set xlabel "sin(theta)"
set ylabel "speed [km/hr]"
plot "ov.dat" using (sin($3)):(sqrt($4**2 + ($2*$5)**2))

pause -1