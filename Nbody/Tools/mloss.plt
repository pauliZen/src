set term postscript landscape enhanced color "Text" 16
set output 'mloss.ps'

set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
set xlabel 't [Myr]'
set ylabel 'Mass[M_sun]'

rscale = 1.0
tscale = 0.23
mscale = 1.0

####---------------plot mass----------------------
#plot 'mloss' u 1:3 w l t "Mtot(t)" lt 1 lw 4, '' u 1:4 w l t "Mtot(0)" lt 1 lw 1, '' u 1:6 w l t 'Mstr(t)' lt 2 lw 4, '' u 1:7 w l t 'Mstr(0)'lt 2 lw 1, '' u 1:9 w l t 'Mweak(t)' lt 3 lw 4, '' u 1:10 w l t 'Mweak(0)' lt 3 lw 1, '' u 1:(#$3-$9) w l t 'Mtot(t)-Mweak(t)' lt 4 lw 4

####---------------plot number--------------------
#set ylabel 'Number'

#plot 'mloss' u 1:5 w l t 'Ntot' lt 1 lw 1, '' u 1:8 w l t 'Nstr' lt 2 lw 1, '' u 1:11 w l t 'Nweak' lt 3 lw 1

####---------------plot lagr----------------------
set ylabel 'R_lagr [pc]'
set key autotitle columnhead
set logscale y 10

plot 'rlagr' u ($1*tscale):($3*rscale) w l lt 1 lw 4, '' u ($1*tscale):($4*rscale) w l lt 2 lw 4, '' u ($1*tscale):($5*rscale) w l lt 3 lw 4,  '' u ($1*tscale):($6*rscale)  w l lt 4 lw 4, '' u ($1*tscale):($7*rscale)  w l lt 5 lw 4, '' u ($1*tscale):($8*rscale)  w l lt 6 lw 4, '' u ($1*tscale):($9*rscale)  w l lt 7 lw 4, '' u ($1*tscale):($10*rscale)  w l lt 8 lw 4, '' u ($1*tscale):($11*rscale)  w l lt 9 lw 4, '' u ($1*tscale):($12*rscale)  w l lt 1 lw 1, '' u ($1*tscale):($13*rscale)  w l lt 2 lw 1,'' u ($1*tscale):($14*rscale)  w l lt 3 lw 1

####---------------plot avmass--------------------
set ylabel '<m> [M_sun]'
set nologscale y

plot 'avmass' u ($1*tscale):($3*mscale) w l lt 1 lw 4, '' u ($1*tscale):($4*mscale) w l lt 2 lw 4, '' u ($1*tscale):($5*mscale) w l lt 3 lw 4,  '' u ($1*tscale):($6*mscale)  w l lt 4 lw 4, '' u ($1*tscale):($7*mscale)  w l lt 5 lw 4, '' u ($1*tscale):($8*mscale)  w l lt 6 lw 4, '' u ($1*tscale):($9*mscale)  w l lt 7 lw 4, '' u ($1*tscale):($10*mscale)  w l lt 8 lw 4, '' u ($1*tscale):($11*mscale)  w l lt 9 lw 4, '' u ($1*tscale):($12*mscale)  w l lt 1 lw 1, '' u ($1*tscale):($13*mscale)  w l lt 2 lw 1,'' u ($1*tscale):($14*mscale)  w l lt 3 lw 1
