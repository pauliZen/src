#set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set term epscairo dashed enhanced color size 6.4,4.8
suffix='eps'
filter='V'

set macro

tlst=system("cut -d' ' -f2 dlist")
lst=system("cut -d' ' -f1 dlist")
rclst=system("awk '{print $2}' king-fit-lum-".filter.".dat")
rtlst=system("awk '{print $4}' king-fit-lum-".filter.".dat")
klst=system("awk '{print $6/$8/3.1415926/$2**2}' king-fit-lum-".filter.".dat")

colori="1 2 3 4 5 7 9"

f(x,k,rc,rt) = x<rt?(k*(1.0/(1.0+(x/rc)**2)**0.5 - 1.0/(1.0+(rt/rc)**2)**0.5)**2):1/0

set output 'sbl_fit.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface brightness [L_{sun}/pc^2]'
plot [0.09:100][0.001:1E6] for [i=1:7] word(lst,i).'.sb.'.filter every ::2 u 1:2 w p lt i lc word(colori,i) t word(tlst,i).' Myr', \
                  for [i=1:7] f(x,word(klst,i),word(rclst,i),word(rtlst,i)) w l lt i lc word(colori,i) t ''

set output 'den.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface density [M_{sun}/pc^2]'
plot [0.09:100][0.001:1E5] for [i=1:7] word(lst,i).'.sb.'.filter every ::2 u 1:6 w lp lt i lc word(colori,i) t word(tlst,i).' Myr'

set output 'M_L.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'M/L [M_{sun}/L_{sun}]'
plot [0.09:100][0.001:100] for [i=1:7] word(lst,i).'.sb.'.filter u 1:($6/f($1,word(klst,i),word(rclst,i),word(rtlst,i))) w l lt i lc word(colori,i) t word(tlst,i).' Myr', \
                           for [i=1:7] word(lst,i).'.sb.'.filter u 1:($6/$2) w p lt i lc word(colori,i) t ''

