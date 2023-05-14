! test -e well.dat || python3 well.py > well.dat

plot[0:50][0:1] "well.dat" index 0 using 1:4 w l title "energy"
