! test -e perc.dat || ./scaling.bash > perc.dat

set terminal dumb ansi256
set key top left
set xlabel "probability of cell to exist"
set ylabel "size of the maximum cluster"
set logscale y
array sizes[8]=[10,20,30,60,100,200,300,600]
plot for [k=7:0:-1] "perc.dat" i k u 1:3 w l title "L=".sizes[k+1]
call '../../scripts/set-png.gp' 'max1.png'
call '../../scripts/set-pdf.gp' 'max1.pdf'
pause -1

set ylabel "relative size of the maximum cluster"
unset logscale
plot for [k=7:0:-1] "perc.dat" i k u 1:($3/$2**2) w l title "L=".sizes[k+1]
call '../../scripts/set-png.gp' 'max2.png'
call '../../scripts/set-pdf.gp' 'max2.pdf'
pause -1


unset logscale
set ylabel "Binder cumulant of the cluster size moments"
plot for [k=0:7] "perc.dat" i k u 1:($5/$4**2) w l title "L=".sizes[k+1]
call '../../scripts/set-png.gp' 'moments.png'
call '../../scripts/set-pdf.gp' 'moments.pdf'
pause -1
