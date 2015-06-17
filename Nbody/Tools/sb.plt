set term pngcairo enhanced color dashed #size 1200,1000 font ',22'


set macro

lst=system("cut -d' ' -f1 sblst.V")

set palette defined (1 "blue", 320 "red")
set autoscale cbfix

set output 'sbl.png'
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface brightness [L_{sun}/pc^2]'
plot [0.1:100][] for [i=1:320] word(lst,i) u 1:2:(i) w l lt 1 lc palette t ''

set output 'den.png'
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface density [M_{sun}/pc^2]'
plot [0.1:100][] for [i=1:320] word(lst,i) u 1:6:(i) w l lt 1 lc palette t ''

set output 'M_L.png'
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'M/L [M_{sun}/L_{sun}]'
plot [0.1:100][] for [i=1:320] word(lst,i) u 1:($6/$2):(i) w l lt 1 lc palette t ''

set output 'sbmag.png'
set logscale x
unset logscale y
set xlabel 'r [arcsec]'
set ylabel 'Surface brightness [Mag/arcsec^2]'
plot [][34:14] for [i=1:320] word(lst,i) u 3:4:(i) w l lt 1 lc palette t ''

