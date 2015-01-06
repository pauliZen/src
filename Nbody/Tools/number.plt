#set term wxt
set term epscairo enhanced color
set output 'number.eps'

filename = 'number.dat'

set xlabel 'Time[Myr]'
set ylabel 'N'

plot filename u 1:5  w l lw 1 t 'NS single', \
          ''  u 1:6  w l lw 1 t 'BH single', \
          ''  u 1:10 w l lw 1 t 'NS binary', \
          ''  u 1:11 w l lw 1 t 'BH binary'

