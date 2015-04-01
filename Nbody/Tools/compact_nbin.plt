#set term postscript landscape enhanced color "Text" 16
set term pngcairo enhanced color dashed

tscale = 0.622

set xlabel 'Time [Myr]'
set ylabel 'Number'
#set logscale y 10

set output 'nbin_t.png'

plot [0:2500][0:1500] \
     'nbinwd' u ($1*tscale):2 w l t 'WD' lt 1 lw 4, \
     'nbinbh' u ($1*tscale):2 w l t 'BH' lt 3 lw 4, \
     'nbinns' u ($1*tscale):2 w l t 'NS' lt 5 lw 4

