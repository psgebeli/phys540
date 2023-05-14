! test -e func.dat || ./func.bash # if the function doesnt exist, generate it!

array p = [ -2, -1, -0.5, 0, 0.5, 1, 2, 3]

set terminal dumb ansi256
set logscale y
plot for [j=1:8] "func.dat" index j w l \
     title sprintf("-x^{%1.2f} ln(x):", p[j])

call '../../scripts/set-png.gp' 'func.png'
