#set term wxt
set term epscairo enhanced color size 14,8 font ',22'
set output 'mpivshyd.eps'

set grid
set style data histograms
set logscale y
#set xtic rotate by -30
set ylabel 'T/T_{NB} [s]'
set style line 1
set style fill solid 1.00 border -1
plot 'mpivshyd' u 3:xtic(1) title columnhead(3), \
             '' u 4 title columnhead(4), \
             '' u 2:($3*1.2):3 with labels title '' , \
             '' u 2:($4*1.2):4 with labels title ''

set term wxt
