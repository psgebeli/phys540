! test -e conv-1.dat || python3 convergence.py -1 > conv-1.dat
! test -e conv-0.5.dat || python3 convergence.py -0.5 > conv-0.5.dat
! test -e conv0.5.dat || python3 convergence.py 0.5 > conv0.5.dat
! test -e conv1.dat || python3 convergence.py 1 > conv1.dat
! test -e conv2.dat || python3 convergence.py 2 > conv2.dat

set fit quiet
f(x) = f0 + f1*(x + f2*x)

do for [n in "-1 -0.5 0.5 1 2"] {

fit[0:0.01] f(x) "conv".n.".dat" u (1.0/$1):2 via f0, f1, f2
print "extrapolates to ", f0
}
