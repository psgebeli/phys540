set terminal dumb ansi256

plot "ave-cluster-size2.dat" u 1:2 w lp, "" u 1:2:3 w e

call '../../scripts/set-png.gp' 'cluster.png'
call '../../scripts/set-pdf.gp' 'cluster.pdf'
