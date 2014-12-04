#set term wxt
set term epscairo enhanced color size 14,8 font ',22'
set output 'kshist.eps'

set grid
set style data histograms
#set logscale y
#set xtic rotate by -30
set ylabel 'T/T_{NB} [s]'
set style line 1
set style fill solid 1.00 border -1
set key autotitle columnheader
plot 'ks.dat' index 0 u 3:xtic(1), \
           '' index 0 u 4, \
           '' index 0 u 5, \
           '' index 0 u ($2-0.125):($3+2):3 with labels title '' font ',14', \
           '' index 0 u ($2+0.125):($4+2):4 with labels title '' font ',14', \
           '' index 0 u ($2+0.375):($5+2):5 with labels title '' font ',14'

set term wxt
