set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set output 'cmd.png'

file='data_10897.25000000.prj'

set xlabel 'B-V'
set ylabel 'V'
set xrange [-1:5]
set yrange [30:-10]
plot file u ($20-$18):18:($1==0?$8:($8>$9?-$8:-$9)) lc pal z
