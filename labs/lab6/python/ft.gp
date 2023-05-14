! test -e well.dat || python3 well.py > well.dat

plot[0:2] \
  "well.dat" index 1 using 1:2 w l title "cos", \
  "" i 1 u 1:3 w l title "sin"
