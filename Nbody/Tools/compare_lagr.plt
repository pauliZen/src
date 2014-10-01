#set term postscript landscape enhanced color "Text" 16
set term pngcairo enhanced color dashed
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
set macro
#set key autotitle columnhead

rscale = 9.385
tscale = 0.622
mscale = 474603.0
vscale = 14.756

nfile = 'lagr_c'
mfile = 'system.dat'
nbout = 'nbout'
#jump = "every ::1"
jump = ""

set ylabel "Lagrangian Radii [pc]"
set xlabel "Time [Myr]"

#-------------lagr---------------------------------
plot [0:1200][0:17] \
   mfile u 2:14 t "M-Rc"  w l lt 1 lc 1 lw 2 , \
      '' u 2:10 t "M-1%"  w l lt 1 lc 2 lw 2 , \
      '' u 2:16 t "M-10%" w l lt 1 lc 3 lw 2 , \
      '' u 2:17 t "M-50%" w l lt 1 lc 4 lw 2 , \
      '' u 2:20 t "M-70%" w l lt 1 lc 7 lw 2 , \
      nbout u ($2*tscale):($14*rscale) t "N-Rc" w l lt 2 lc 1 lw 2, \
   nfile u 1:5  t "N-1%"  w l lt 2 lc 2 lw 2, \
      '' u 1:8  t "N-10%" w l lt 2 lc 3 lw 2, \
      '' u 1:12 t "N-50%" w l lt 2 lc 4 lw 2, \
      '' u 1:14 t "N-70%" w l lt 2 lc 7 lw 2

#set output 'avem_c.emf'
#set output 'avem_c.ps'
set output 'avem_c.png'

#-----------------average mass--------------------
set ylabel "Average Mass [M_{\odot}]"
set xlabel "Time [Myr]"
#set logscale y

###        
###      


plot [0:1500][0.3:1.5] \
   mfile u 2:39 t "M-Rc"  w l lt 1 lc 1 lw 2, \
      '' u 2:40 t "M-1%"  w l lt 1 lc 2 lw 2, \
      '' u 2:41 t "M-10%" w l lt 1 lc 3 lw 2, \
      '' u 2:42	t "M-50%" w l lt 1 lc 8 lw 2, \
      '' u 2:43	t "M-70%" w l lt 1 lc 7 lw 2, \
   nbout u ($2*tscale):($16*mscale/$15) t "N-Rc" w l lt 2 lc 1 lw 2, \
   nfile u 1:(($20*$38+$21*$39+$22*$40+$23*$41)/($20+$21+$22+$23)) t "N-1%" w l lt 2 lc 2 lw 2, \
      '' u 1:(($20*$38+$21*$39+$22*$40+$23*$41+$24*$42+$25*$43+$26*$44)/($20+$21+$22+$23+$24+$25+$26)) t "N-10%" w l lt 2 lc 3 lw 2, \
      '' u 1:(($20*$38+$21*$39+$22*$40+$23*$41+$24*$42+$25*$43+$26*$44+$27*$45+$28*$46+$29*$47+$30*$48)/($20+$21+$22+$23+$24+$25+$26+$27+$28+$29+$30)) t "N-50%" w l lt 2 lc 8 lw 2, \
      '' u 1:(($20*$38+$21*$39+$22*$40+$23*$41+$24*$42+$25*$43+$26*$44+$27*$45+$28*$46+$29*$47+$30*$48+$31*$49+$32*$50)/($20+$21+$22+$23+$24+$25+$26+$27+$28+$29+$30+$31+$32)) t "N-70%" w l lt 2 lc 7 lw 2
