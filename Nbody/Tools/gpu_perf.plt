set term postscript landscape enhanced color "Text" 16
set output 'gpu_perf.ps'

set zeroaxis
set grid
set pointsize 1.0
set mxtics 10
set mytics 10
set macro
set key left
#set key autotitle columnhead

####---------------macro 5 columns----------------
colu7 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w lp lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w lp lt 2 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w lp lt 3 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w lp lt 4 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w lp lt 5 lw 4, \
           '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w lp lt 6 lw 4, \
           '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w lp lt 7 lw 4"

set title 'Nbody6++ GPU Force calculation performance in Hydra Cluster'
set ylabel 'Speed [Gflops]'
set xlabel 'N_{GPU}'
set logscale y 10
set logscale x 2
x = 1
shift = 1
xscale = 1
yscale = 1.0

f(x) = 2000*x
f2(x) = 1000*x

plot [1:32][1000:100000] 'reg.reduce' @colu7, f(x) t '2 Tflops/GPU' w l lt 8 lw 2, f2(x) t '1 Tflops/GPU' w l lt 9 lw 2
