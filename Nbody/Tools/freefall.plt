set term postscript landscape enhanced color "Text" 16
set output 'freefall.ps'

set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
set macro
#set key autotitle columnhead

rscale = 1.0
tscale = 0.018
mscale = 700000.0
vscale = 54.869

filename = 'alldata'
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

set ylabel 'R_{lagr} [pc]'
set xlabel 't [Myr]'
set logscale y 10
set nologscale x
x = 1
shift = 37
xscale = tscale
yscale = rscale

plot filename @colu12

####---------------plot NPARTC------------------
set ylabel 'NPART'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 63
xscale = tscale
yscale = 1

plot filename @colu12

####---------------plot Sigma_R2------------------
set ylabel 'Sigma_{R} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 76
xscale = tscale
yscale = vscale

plot filename @colu_sqrt12

####---------------plot Sigma_T2------------------
set ylabel 'Sigma_{T} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 89
xscale = tscale
yscale = vscale

plot filename @colu_sqrt12

####---------------plot VROT------------------
set ylabel 'VROT [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 102
xscale = tscale
yscale = vscale

plot filename @colu12

####---------------plot lagr <R>------------------

set ylabel 'R_{lagr} [pc]'
set xlabel 'C'
set logscale y 10
set nologscale x
x = 15
shift = 37
xscale = 1.0
yscale = rscale

plot filename @colu_r12

####---------------plot NPARTC <R>----------------
set ylabel 'NPART'
set xlabel 'C'
set nologscale y
set nologscale x
x = 15
shift = 63
xscale = 1.0
yscale = 1

plot filename @colu_r12

####---------------plot Sigma_R2 <R>------------------
set ylabel 'Sigma_{R} [km/s]'
set xlabel 'C'
set nologscale y
set nologscale x
x = 15
shift = 76
xscale = 1.0
yscale = vscale

plot filename @colu_r_sqrt12

####---------------plot Sigma_T2 <R>------------------
set ylabel 'Sigma_{T} [km/s]'
set xlabel 'C'
set nologscale y
set nologscale x
x = 15
shift = 89
xscale = 1.0
yscale = vscale

plot filename @colu_r_sqrt12

####---------------plot VROT------------------
set ylabel 'VROT [km/s]'
set xlabel 'C'
set nologscale y
set nologscale x
x = 15
shift = 102
xscale = 1.0
yscale = vscale

plot filename @colu_r12

# ####------------R vs T-----------------
# set xlabel 'T'
# set ylabel '<R>'
# plot filename u 1:15 w l
