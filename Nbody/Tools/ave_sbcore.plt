set term pngcairo enhanced color dashed #size 1200,1000 font ',22'set macro

set output 'sbcore_ave.png'
set xlabel 'Time [Myr]'
set ylabel 'R [pc]'
plot [][0:16] 'sbcore.B' u 1:5 w lp t 'Mass', \
                      '' u 1:2 w lp t 'B', \
              'sbcore.V' u 1:2 w lp t 'V', \
              'sbcore.I' u 1:2 w lp t 'I'

set output 'sbcore_mid.png'
set xlabel 'Time [Myr]'
set ylabel 'R [pc]'
plot [][0:16] 'sbcore.B' u 1:6 w lp t 'Mass', \
                      '' u 1:3 w lp t 'B', \
              'sbcore.V' u 1:3 w lp t 'V', \
              'sbcore.I' u 1:3 w lp t 'I'
