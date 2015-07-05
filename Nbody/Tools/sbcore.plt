set term pngcairo enhanced color dashed #size 1200,1000 font ',22'set macro

set output 'sbcore.png'
set xlabel 'Time [Myr]'
set ylabel 'R [pc]'
plot [][0:16] 'sbcore.B' u 1:3 w l t 'Mass', \
                      '' u 1:2 w l t 'B', \
              'sbcore.V' u 1:2 w l t 'V', \
              'sbcore.I' u 1:2 w l t 'I'

