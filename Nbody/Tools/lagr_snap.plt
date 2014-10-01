set term pngcairo enhanced color dashed
#set term postscript landscape enhanced color "Text" 16
#set output 'lagr.ps'

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

filename = 'data_lagr'
mfile = 'system.dat'
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
colu4 =  "u (column(x)*xscale):(column(4*ntype+shift)*yscale)   t columnhead(4*ntype+shift)  w l lc 1 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(7*ntype+shift)*yscale)   t columnhead(7*ntype+shift)  w l lc 2 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(11*ntype+shift)*yscale)  t columnhead(11*ntype+shift) w l lc 3 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(13*ntype+shift)*yscale)  t columnhead(13*ntype+shift) w l lc 4 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(17*ntype+shift)*yscale)  t columnhead(17*ntype+shift) w l lc 5 lt 1 lw 1"

####---------------macro 18 columns----------------
colu18 = "u (column(x)*xscale):(column(1*ntype+shift)*yscale)   t columnhead(1*ntype+shift)  w l lc 1 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(2*ntype+shift)*yscale)   t columnhead(2*ntype+shift)  w l lc 2 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(3*ntype+shift)*yscale)   t columnhead(3*ntype+shift)  w l lc 3 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(4*ntype+shift)*yscale)   t columnhead(4*ntype+shift)  w l lc 4 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(5*ntype+shift)*yscale)   t columnhead(5*ntype+shift)  w l lc 5 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(6*ntype+shift)*yscale)   t columnhead(6*ntype+shift)  w l lc 6 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(7*ntype+shift)*yscale)   t columnhead(7*ntype+shift)  w l lc 7 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(8*ntype+shift)*yscale)   t columnhead(8*ntype+shift)  w l lc 8 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(9*ntype+shift)*yscale)   t columnhead(9*ntype+shift)  w l lc 9 lt 1 lw 1, \
       '' u (column(x)*xscale):(column(10*ntype+shift)*yscale)  t columnhead(10*ntype+shift) w l lc 1 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(11*ntype+shift)*yscale)  t columnhead(11*ntype+shift) w l lc 2 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(12*ntype+shift)*yscale)  t columnhead(12*ntype+shift) w l lc 3 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(13*ntype+shift)*yscale)  t columnhead(13*ntype+shift) w l lc 4 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(14*ntype+shift)*yscale)  t columnhead(14*ntype+shift) w l lc 5 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(15*ntype+shift)*yscale)  t columnhead(15*ntype+shift) w l lc 6 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(16*ntype+shift)*yscale)  t columnhead(16*ntype+shift) w l lc 7 lt 2 lw 1, \
       '' u (column(x)*xscale):(column(17*ntype+shift)*yscale)  t columnhead(17*ntype+shift) w l lc 8 lt 2 lw 1"
#       '' u (column(x)*xscale):(column(18*ntype+shift)*yscale)  t columnhead(18*ntype+shift) w l lc 9 lt 2 lw 1"

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

xscale = tscale
set xlabel 't [Myr]'
x = 1

####---------------plot mass----------------------
set output 'data_m.png'

set ylabel 'M_{tot}/M_{tot,init}'

plot [0:1200][0.7:1] filename u ($1*tscale):($2/mscale) t 'N-body Total mass' w l lc 1 lt 1 lw 1, \
           '' u ($1*tscale):($3/429790.) t 'N-body Single mass' w l lc 7 lt 7 lw 1, \
           '' u ($1*tscale):($4/44813.2) t 'N-body Binary mass' w l lc 3 lt 3 lw 1, \
        mfile u 2:($3/mscale) t 'MOCCA total mass' w l lc 4 lt 4 lw 1

####---------------plot lagr----------------------
set output 'data_rlagr.png'

set ylabel 'R_{lagr} [pc]'
yscale = rscale
shift = 1
ntype = 4

plot filename @jump @colu18

####---------------plot NPARTC------------------
set output 'data_nlagr.png'
set ylabel 'N_{lagr}'
yscale = 1
shift = 2
ntype = 4

plot filename @jump @colu18

####---------------plot Nb/N------------------
set output 'data_nbnlagr.png'
set ylabel 'N_{bin,lagr}/N_{lagr}'
yscale = 1.0
shift = 3
ntype = 4

plot [][] filename @jump @colu4

####---------------plot Mb/M------------------
set output 'data_mbmlagr.png'
set ylabel 'M_{bin,lagr}/M_{lagr}'
shift = 4
ntype = 4

plot [][] filename @jump @colu4

