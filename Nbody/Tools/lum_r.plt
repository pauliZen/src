set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set output 'lum_r.png'

set xlabel 'r [pc]'
set ylabel 'M_{V}'
set logscale x
set logscale y
set xrange [0.01:100]
#set yrange [30:-10]

set palette maxcolors 31
# defined \
# ( 0 "#332288", \
#   1 "#332288", \
#   2 "#88CCEE", \
#   3 "red", \
#   4 "#CC6677", \
#   5 "#882255", \
#   6 "#882255", \
#   7 "#117733", \
#   8 "#117733", \
#   9 "#117733", \
#   10 "#774411",\
#   11 "#774411",\
#   12 "#774411",\
#   13 "#4477AA",\
#   14 "black" \
# )

plot 'data_10896.12500000.prj' u (sqrt($2*$2+$3*$3)):(10.0**(0.4*(4.83-$18))):($1==0?$8:($8>$9?-$8:-$9)) lc pal z
