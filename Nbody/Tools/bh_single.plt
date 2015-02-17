set term epscairo enhanced color dashed
set macro

tscale=0.55062
mscale=606363
rscale=9.375

set xlabel "Time [Myr]"
set ylabel "Number"

##-------------sbhn--------
set output 'bhn.eps'
set ylabel 'N_{sbh}'
set logscale y 10
plot [][1:2000] 'bh_score' u ($1*tscale):8   w l lt 1 lc 1 title 'Single BH' , \
                'bh_bcore' u ($1*tscale):6   w l lt 1 lc 2 title 'BH binary' , \
                        '' u ($1*tscale):10  w l lt 1 lc 3 title 'BH-BH binary'

