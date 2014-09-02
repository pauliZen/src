set term postscript landscape enhanced color "Text" 16
set output 'lagr.ps'

set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
set macro
#set key autotitle columnhead

rscale = 9.385
tscale = 0.622
mscale = 474603.0
vscale = 14.756

filename = 'lagr_c'
#jump = "every ::1"
jump = ""

####---------------macro 12 columns----------------
colu12 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

####---------------macro 18 columns----------------
colu18 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
           '' u (column(x)*xscale):(column(12+shift)*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
           '' u (column(x)*xscale):(column(13+shift)*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
           '' u (column(x)*xscale):(column(14+shift)*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
           '' u (column(x)*xscale):(column(15+shift)*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
           '' u (column(x)*xscale):(column(16+shift)*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
           '' u (column(x)*xscale):(column(17+shift)*yscale)  t columnhead(17+shift) w l lt 8 lw 1"
#           '' u (column(x)*xscale):(column(18+shift)*yscale)  t columnhead(18+shift) w l lt 9 lw 1"

####---------------macro 19 columns----------------
colu19 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
           '' u (column(x)*xscale):(column(12+shift)*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
           '' u (column(x)*xscale):(column(13+shift)*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
           '' u (column(x)*xscale):(column(14+shift)*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
           '' u (column(x)*xscale):(column(15+shift)*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
           '' u (column(x)*xscale):(column(16+shift)*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
           '' u (column(x)*xscale):(column(17+shift)*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
           '' u (column(x)*xscale):(column(18+shift)*yscale)  t columnhead(18+shift) w l lt 9 lw 1, \
           '' u (column(x)*xscale):(column(19+shift)*yscale)  t columnhead(19+shift) w l lt 1 lw 6"

####---------------macro 18 columns----------------
colu_sqrt18 = "u (column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(12+shift))*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(13+shift))*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(14+shift))*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(15+shift))*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(16+shift))*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(17+shift))*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(18+shift))*yscale)  t columnhead(18+shift) w l lt 9 lw 1"

####---------------macro 19 columns----------------
colu_sqrt19 = "u (column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(12+shift))*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(13+shift))*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(14+shift))*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(15+shift))*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(16+shift))*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(17+shift))*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(18+shift))*yscale)  t columnhead(18+shift) w l lt 9 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(19+shift))*yscale)  t columnhead(19+shift) w l lt 1 lw 6"

####---------------macro 12 columns----------------
colu_sqrt12 = "u (column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

####---------------macro 12 columns----------------
colu_r12 = "u (1/column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (1/column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (1/column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (1/column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (1/column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (1/column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (1/column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (1/column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (1/column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (1/column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (1/column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

####---------------macro 12 columns----------------
colu_r_sqrt12 = "u (1/column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (1/column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

xscale = 1.0
yscale = 1.0
set xlabel 't [Myr]'
x = 1

####---------------plot lagr----------------------

set ylabel 'R_{lagr} [pc]'
shift = 1

plot filename @jump @colu18

####---------------plot NPARTC------------------
set ylabel 'N_{shell}'
shift = 19

plot filename @jump @colu18

####---------------plot AVMASS------------------
set ylabel '<M> [M_{sun}]'
shift = 37

plot filename @jump @colu18

