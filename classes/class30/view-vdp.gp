set terminal dumb ansi256
set key noautotitle

set title "Real-space trajectory (unforced)"
set xlabel "time {/:Italic t}" enhanced
set ylabel "postition {/:Italic x}" enhanced
plot[0:50] "vdp.dat" u 1:2:(column(-2)) linecolor variable w l
call '../../scripts/set-png.gp' 'time-trace.png'
pause -1

set title "Phase-space trajectory (unforced)"
set xlabel "position {/:Italic x}" enhanced
set ylabel "velocity {/:Italic v}" enhanced
plot "vdp.dat" u 2:3:(column(-2)) linecolor variable w l
call '../../scripts/set-png.gp' 'phase-space.png'
pause -1

set title "Real-space trajectory (forced)"
set xlabel "time {/:Italic t}" enhanced
set ylabel "postition {/:Italic x}" enhanced
plot[0:] "vdp-forced.dat" u 1:2:(column(-2)) linecolor variable w l
call '../../scripts/set-png.gp' 'time-trace-forced.png'
pause -1

set title "Phase-space trajectory (forced)"
set xlabel "position {/:Italic x}" enhanced
set ylabel "velocity {/:Italic v}" enhanced
plot "vdp-forced.dat" u 2:3:(column(-2)) linecolor variable w l
call '../../scripts/set-png.gp' 'phase-space-forced.png'
pause -1


