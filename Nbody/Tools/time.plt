#set term postscript landscape enhanced color "Text" 16
#set term epscairo enhanced color
#set output 'time.eps'

#set term pngcairo enhanced color
#set output 'time.png'
#set term xterm

set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
set macro
#set key autotitle columnhead

filename = 'ttotal.0.txt'
offset = "`head -2 ttotal.0.txt|tail -1`"

f(x0,x) = x0/x

####---------------macro 5 columns----------------

####---------------plot lagr----------------------

set ylabel 'T [second]'
set xlabel 'Nodes'
set logscale y
set logscale x 2
x = 1
shift = 1
xscale = 1
yscale = 1.0

plot filename u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 1 lw 4, \
         f(word(offset,2)*yscale,x) w l lt 2 lw 4, \
         f(word(offset,3)*yscale,x) w l lt 2 lw 4, \
         f(word(offset,4)*yscale,x) w l lt 2 lw 4, \
         f(word(offset,5)*yscale,x) w l lt 2 lw 4, \
         f(word(offset,6)*yscale,x) w l lt 2 lw 4

