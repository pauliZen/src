set term pngcairo enhanced color dashed
#set term epscairo enhanced color dashed
suffix='png'

#set term postscript landscape enhanced color "Text" 16
#set output 'data.py.ps'

#set zeroaxis
set grid
#set pointsize 1.0
#set mxtics 10
#set mytics 10
set macro
#set key autotitle columnhead

rscale = 1.0
tscale = 1.0
mscale = 1.0
vscale = 1.0

filename = 'lagr.snap'
jump = "every ::1"
#jump = ""

trange=""
rrange=""
nrange=""
mrange=""
vrange=""

mmrange=""
nnrange=""

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
           '' u (column(x)*xscale):(column(17+shift)*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
           '' u (column(x)*xscale):(column(18+shift)*yscale)  t columnhead(18+shift) w l lt 9 lw 1"

####---------------macro 18 columns x/y----------------
colu18_xy = "u (column(x)*xscale):(column(1 +shift)/column(1 +shift2)*yscale)  t columnhead(1+shift)  w l lt 1 lw 4, \
          '' u (column(x)*xscale):(column(2 +shift)/column(2 +shift2)*yscale)  t columnhead(2+shift)  w l lt 2 lw 4, \
          '' u (column(x)*xscale):(column(3 +shift)/column(3 +shift2)*yscale)  t columnhead(3+shift)  w l lt 3 lw 4, \
          '' u (column(x)*xscale):(column(4 +shift)/column(4 +shift2)*yscale)  t columnhead(4+shift)  w l lt 4 lw 4, \
          '' u (column(x)*xscale):(column(5 +shift)/column(5 +shift2)*yscale)  t columnhead(5+shift)  w l lt 5 lw 4, \
          '' u (column(x)*xscale):(column(6 +shift)/column(6 +shift2)*yscale)  t columnhead(6+shift)  w l lt 6 lw 4, \
          '' u (column(x)*xscale):(column(7 +shift)/column(7 +shift2)*yscale)  t columnhead(7+shift)  w l lt 7 lw 4, \
          '' u (column(x)*xscale):(column(8 +shift)/column(8 +shift2)*yscale)  t columnhead(8+shift)  w l lt 8 lw 4, \
          '' u (column(x)*xscale):(column(9 +shift)/column(9 +shift2)*yscale)  t columnhead(9+shift)  w l lt 9 lw 4, \
          '' u (column(x)*xscale):(column(10+shift)/column(10+shift2)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
          '' u (column(x)*xscale):(column(11+shift)/column(11+shift2)*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
          '' u (column(x)*xscale):(column(12+shift)/column(12+shift2)*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
          '' u (column(x)*xscale):(column(13+shift)/column(13+shift2)*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
          '' u (column(x)*xscale):(column(14+shift)/column(14+shift2)*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
          '' u (column(x)*xscale):(column(15+shift)/column(15+shift2)*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
          '' u (column(x)*xscale):(column(16+shift)/column(16+shift2)*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
          '' u (column(x)*xscale):(column(17+shift)/column(17+shift2)*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
          '' u (column(x)*xscale):(column(18+shift)/column(18+shift2)*yscale)  t columnhead(18+shift) w l lt 9 lw 1"

####---------------macro 18 columns x/y*z----------------
colu18_xyz= "u (column(x)*xscale):(column(1 +shift2)/(column(1 +shift)*column(1 +shift3)))  t columnhead(1+shift)  w l lt 1 lw 4, \
          '' u (column(x)*xscale):(column(2 +shift2)/(column(2 +shift)*column(2 +shift3)))  t columnhead(2+shift)  w l lt 2 lw 4, \
          '' u (column(x)*xscale):(column(3 +shift2)/(column(3 +shift)*column(3 +shift3)))  t columnhead(3+shift)  w l lt 3 lw 4, \
          '' u (column(x)*xscale):(column(4 +shift2)/(column(4 +shift)*column(4 +shift3)))  t columnhead(4+shift)  w l lt 4 lw 4, \
          '' u (column(x)*xscale):(column(5 +shift2)/(column(5 +shift)*column(5 +shift3)))  t columnhead(5+shift)  w l lt 5 lw 4, \
          '' u (column(x)*xscale):(column(6 +shift2)/(column(6 +shift)*column(6 +shift3)))  t columnhead(6+shift)  w l lt 6 lw 4, \
          '' u (column(x)*xscale):(column(7 +shift2)/(column(7 +shift)*column(7 +shift3)))  t columnhead(7+shift)  w l lt 7 lw 4, \
          '' u (column(x)*xscale):(column(8 +shift2)/(column(8 +shift)*column(8 +shift3)))  t columnhead(8+shift)  w l lt 8 lw 4, \
          '' u (column(x)*xscale):(column(9 +shift2)/(column(9 +shift)*column(9 +shift3)))  t columnhead(9+shift)  w l lt 9 lw 4, \
          '' u (column(x)*xscale):(column(10+shift2)/(column(10+shift)*column(10+shift3)))  t columnhead(10+shift) w l lt 1 lw 1, \
          '' u (column(x)*xscale):(column(11+shift2)/(column(11+shift)*column(11+shift3)))  t columnhead(11+shift) w l lt 2 lw 1, \
          '' u (column(x)*xscale):(column(12+shift2)/(column(12+shift)*column(12+shift3)))  t columnhead(12+shift) w l lt 3 lw 1, \
          '' u (column(x)*xscale):(column(13+shift2)/(column(13+shift)*column(13+shift3)))  t columnhead(13+shift) w l lt 4 lw 1, \
          '' u (column(x)*xscale):(column(14+shift2)/(column(14+shift)*column(14+shift3)))  t columnhead(14+shift) w l lt 5 lw 1, \
          '' u (column(x)*xscale):(column(15+shift2)/(column(15+shift)*column(15+shift3)))  t columnhead(15+shift) w l lt 6 lw 1, \
          '' u (column(x)*xscale):(column(16+shift2)/(column(16+shift)*column(16+shift3)))  t columnhead(16+shift) w l lt 7 lw 1, \
          '' u (column(x)*xscale):(column(17+shift2)/(column(17+shift)*column(17+shift3)))  t columnhead(17+shift) w l lt 8 lw 1, \
          '' u (column(x)*xscale):(column(18+shift2)/(column(18+shift)*column(18+shift3)))  t columnhead(18+shift) w l lt 9 lw 1"

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

####---------------plot lagr----------------------
set output 'lagr.'.suffix
set ylabel 'R_{lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
#set logscale y 10
set nologscale x
x = 1
shift = 1
xscale = tscale
yscale = rscale

plot [@trange][@rrange] filename @jump @colu18

####---------------plot s,lagr----------------------
set output 'slagr.'.suffix

set ylabel 'R_{s,lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
#set logscale y 10
set nologscale x
x = 1
shift = 19
xscale = tscale
yscale = rscale

plot [@trange][@rrange] filename @jump @colu18

####---------------plot b,lagr----------------------
set output 'blagr.'.suffix

set ylabel 'R_{b,lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
#set logscale y 10
set nologscale x
x = 1
shift = 37
xscale = tscale
yscale = rscale

plot [@trange][@rrange] filename @jump @colu18

####---------------plot AVMASS------------------
set output 'avemass.'.suffix
set ylabel '<M> [M_{sun}]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 55
xscale = tscale
yscale = mscale

plot [@trange][@mrange] filename @jump @colu18

####---------------plot s,AVMASS------------------
set output 'savemass.'.suffix
set ylabel '<M_s> [M_{sun}]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 73
xscale = tscale
yscale = mscale

plot [@trange][@mrange] filename @jump @colu18

####---------------plot b,AVMASS------------------
set output 'bavemass.'.suffix
set ylabel '<M_b> [M_{sun}]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 91
xscale = tscale
yscale = mscale

plot [@trange][@mrange] filename @jump @colu18

####---------------plot NPARTC------------------
set output 'npart.'.suffix
set ylabel 'N'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 109
xscale = tscale
yscale = 1

plot [@trange][@nrange] filename @jump @colu18

####---------------plot s,NPARTC------------------
set output 'snpart.'.suffix
set ylabel 'N_s'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 127
xscale = tscale
yscale = 1

plot [@trange][@nrange] filename @jump @colu18

####---------------plot b,NPARTC------------------
set output 'bnpart.'.suffix
set ylabel 'N'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 145
xscale = tscale
yscale = 1

plot [@trange][@nrange] filename @jump @colu18

####---------------plot Mb/M------------------
set output 'mb_m.'.suffix
set ylabel 'M_{bin}/M'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 55
shift2 = 163
shift3 = 109
xscale = tscale
yscale = 1

plot [@trange][@mmrange] filename @jump @colu18_xyz

####---------------plot Nb/N------------------
set output 'nb_n.'.suffix
set ylabel 'N_{bin}/N'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 181
shift2 = 109
xscale = tscale
yscale = 1

plot [@trange][@nnrange] filename @jump @colu18_xy

####---------------plot V------------------
set output 'v.'.suffix
set ylabel '<V> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 199
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot V_s------------------
set output 'sv.'.suffix
set ylabel '<V_s> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 217
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot V_b------------------
set output 'bv.'.suffix
set ylabel '<V_b> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 235
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

#####---------------plot Vx------------------
set output 'vx.'.suffix
set ylabel '<V_x> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 253
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

#####---------------plot Vx_s------------------
set output 'svx.'.suffix
set ylabel '<V_{x,s}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 271
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

#####---------------plot Vx_s------------------
set output 'bvx.'.suffix
set ylabel '<V_{x,b}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 289
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vy------------------
set output 'vy.'.suffix
set ylabel '<V_y> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 307
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vy_s------------------
set output 'svy.'.suffix
set ylabel '<V_{y,s}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 325
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vy_b------------------
set output 'bvy.'.suffix
set ylabel '<V_{y,b}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 343
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vz------------------
set output 'vz.'.suffix
set ylabel '<V_z> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 361
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vz_s------------------
set output 'svz.'.suffix
set ylabel '<V_{z,s}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 379
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vz_b------------------
set output 'bvz.'.suffix
set ylabel '<V_{z,b}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 397
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vr------------------
set output 'vr'.suffix
set ylabel '<V_r> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 415
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vr_s------------------
set output 'svr'.suffix
set ylabel '<V_{r,s}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 433
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vr_b------------------
set output 'bvr'.suffix
set ylabel '<V_{r,b}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 451
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vt------------------
set output 'vt.'.suffix
set ylabel '<V_t> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 469
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vt_s------------------
set output 'svt.'.suffix
set ylabel '<V_{t,s}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 487
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Vt_b------------------
set output 'bvt.'.suffix
set ylabel '<V_{t,b}> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 505
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu18

####---------------plot Sigma--------------------
set output 'sigma.'.suffix
set ylabel '\Sigma [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 523
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_s--------------------
set output 'ssigma.'.suffix
set ylabel '\Sigma_s [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 541
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_b--------------------
set output 'bsigma.'.suffix
set ylabel '\Sigma_b [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 559
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_x--------------------
set output 'sigmax.'.suffix
set ylabel '\Sigma_x [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 577
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_x,s--------------------
set output 'ssigmax.'.suffix
set ylabel '\Sigma_{x,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 595
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_x,b--------------------
set output 'bsigmax.'.suffix
set ylabel '\Sigma_{x,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 613
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_y--------------------
set output 'sigmay.'.suffix
set ylabel '\Sigma_y [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 631
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_y,s--------------------
set output 'ssigmay.'.suffix
set ylabel '\Sigma_{y,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 649
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_y,b--------------------
set output 'bsigmay.'.suffix
set ylabel '\Sigma_{y,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 667
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_z--------------------
set output 'sigmaz.'.suffix
set ylabel '\Sigma_z [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 685
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_z,s--------------------
set output 'ssigmaz.'.suffix
set ylabel '\Sigma_{z,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 703
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_z,b--------------------
set output 'bsigmaz.'.suffix
set ylabel '\Sigma_{z,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 721
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_r--------------------
set output 'sigmar.'.suffix
set ylabel '\Sigma_{r} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 739
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_r,s--------------------
set output 'ssigmar.'.suffix
set ylabel '\Sigma_{r,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 757
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_r,b--------------------
set output 'bsigmar.'.suffix
set ylabel '\Sigma_{r,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 775
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_t------------------
set output 'sigmat.'.suffix
set ylabel '\Sigma_{t} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 793
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_t,s------------------
set output 'ssigmat.'.suffix
set ylabel '\Sigma_{t,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 811
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_t,b------------------
set output 'bsigmat.'.suffix
set ylabel '\Sigma_{t,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 829
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot VROT------------------
set output 'vrot.'.suffix
set ylabel 'V_{rot} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 847
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu18

####---------------plot VROT,s------------------
set output 'svrot.'.suffix
set ylabel 'V_{rot,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 865
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu18

####---------------plot VROT,b------------------
set output 'bvrot.'.suffix
set ylabel 'V_{rot,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 883
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu18

####---------------plot Sigma_rot------------------
set output 'sigmarot.'.suffix
set ylabel '\Sigma_{rot} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 901
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_rot,s------------------
set output 'ssigmarot.'.suffix
set ylabel '\Sigma_{rot,s} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 919
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18

####---------------plot Sigma_rot,b------------------
set output 'bsigmarot.'.suffix
set ylabel '\Sigma_{rot,b} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 937
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt18
