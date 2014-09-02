set term postscript landscape enhanced color "Text" 16
set output 'data.ps'

set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
set macro
#set key autotitle columnhead

filename = 'time.dat'

f(x) = 400.0/x

####---------------macro 5 columns----------------
colu5 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 1 lw 4"

####---------------plot lagr----------------------

set ylabel 'T [second]'
set xlabel 'Nodes'
set logscale y
set logscale x 2
x = 1
shift = 1
xscale = 1
yscale = 1.0

plot filename @colu5 , f(x) t '1/N_{P}' w l lt 2 lw 4

