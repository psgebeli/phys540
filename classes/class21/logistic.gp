set terminal dumb ansi256

plot[900:950] "logisticA.dat" u 0:1 w lp, \
            "logisticB.dat" u 0:1 w lp

call '../../scripts/set-png.gp' 'logistic-cf.png'

