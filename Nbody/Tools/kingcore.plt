#set term pngcairo enhanced color dashed #size 1200,1000 font ',22'set macro
set term epscairo dashed enhanced color size 6.4,4.8
suffix='eps'

set output 'radius.'.suffix
set xlabel 'Time [Myr]'
set ylabel 'R [pc]'
set key top left

plot [0:8000][0:18] 'king-fit-lum.fin'  u 1:2:3 w yerr lt 1 t '2-D R_{c} - King fitting', \
                              ''  u 1:9 w lp lt 2 t '2-D R_{hl} - King fitting', \
          'global.30.all' u 2:9 w l lt 3 t '3-D R_{c} - casertano & hut (1985, density^2 weighted)',\
                       '' u 2:6 w l lt 4 t '3-D R_{hm}'
#                      ''  u 1:2:3 w l lt 1 t '2-D King fitting', \
