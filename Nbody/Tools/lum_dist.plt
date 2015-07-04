set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set output 'lum_hist.png'

set xlabel 'Log10(L[L_sun])'
set ylabel 'Number'

#rlst=system("sed -n '2,$ p' data_10896.12500000.sb.V|cut -d' ' -f1 ")

plot 'data_10896.12500000.prj' u (hist($2*$2+$3*$3<1.0?0.4*(4.83-$18):1/0,0.1)):(1.0) smooth frequency with boxes
