#set term postscript landscape enhanced color "Text" 16
set term pngcairo enhanced color dashed size 800,600 font ',14'
#set term emf enhanced color dashed
#set term epscairo enhanced color
#set output 'lagr_c.emf'
set output 'lagr_c.png'
#set output 'lagr_c.ps'


set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
#set macro

n1="R7_KTG93/data_lagr"
n2="R7_IMF2001/lagr.snap"
n3="R3_IMF2001/lagr.snap"
n4="R7_ROT/lagr.snap"

tscale1=0.622
tscale2=0.55062
tscale3=0.1382
tscale4=0.54381

set xlabel "Time [Myr]"
set ylabel "R_{lagr} [NB]"

plot [0:600][] \
     n2 u ($1*tscale2):($5 /9.375) t "R7.5-K2001" w l lt 1 lc 1 lw 2, \
     '' u ($1*tscale2):($8 /9.375) t "" w l lt 2 lc 1 lw 2, \
     '' u ($1*tscale2):($12/9.375) t "" w l lt 3 lc 1 lw 2, \
     '' u ($1*tscale2):($13/9.375) t "" w l lt 4 lc 1 lw 2, \
     '' u ($1*tscale2):($14/9.375) t "" w l lt 5 lc 1 lw 2, \
     n3 u ($1*tscale3):($5 /3.730335) t "R3-K2001" w l lt 1 lc 3 lw 2, \
     '' u ($1*tscale3):($8 /3.730335) t "" w l lt 2 lc 3 lw 2, \
     '' u ($1*tscale3):($12/3.730335) t "" w l lt 3 lc 3 lw 2, \
     '' u ($1*tscale3):($13/3.730335) t "" w l lt 4 lc 3 lw 2, \
     '' u ($1*tscale3):($14/3.730335) t "" w l lt 5 lc 3 lw 2, \
     n4 u ($1*tscale4):($5 /9.29757) t "R7.5-ROT" w l lt 1 lc 2 lw 2, \
     '' u ($1*tscale4):($8 /9.29757) t "" w l lt 2 lc 2 lw 2, \
     '' u ($1*tscale4):($12/9.29757) t "" w l lt 3 lc 2 lw 2, \
     '' u ($1*tscale4):($13/9.29757) t "" w l lt 4 lc 2 lw 2, \
     '' u ($1*tscale4):($14/9.29757) t "" w l lt 5 lc 2 lw 2, \
     n1 u ($1*tscale1):17 t "R7.5-KTG93-1% " w l lt 1 lc 0 lw 2, \
     '' u ($1*tscale1):29 t "10%" w l lt 2 lc 0 lw 2, \
     '' u ($1*tscale1):45 t "50%" w l lt 3 lc 0 lw 2, \
     '' u ($1*tscale1):49 t "60%" w l lt 4 lc 0 lw 2, \
     '' u ($1*tscale1):53 t "70%" w l lt 5 lc 0 lw 2

exit