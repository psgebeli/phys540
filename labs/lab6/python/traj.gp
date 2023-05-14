! test -e well.dat || python3 well.py > well.dat

plot[0:20] \
  "well.dat" index 0 using 1:2 w l title "position", \
  "" i 0 u 1:3 w l title "velocity"
