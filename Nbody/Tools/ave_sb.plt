#set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set term epscairo dashed enhanced color size 6.4,4.8
suffix='eps'

set macro

tlst=system("cut -d' ' -f2 sblst.V")
lst=system("cut -d' ' -f1 sblst.V")

colori="1 2 3 4 5 7 9"

set output 'sbl_ave.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface brightness [L_{sun}/pc^2]'
plot [0.09:100][] for [i=1:7] word(lst,i) u 1:2 w lp lt i lc word(colori,i) t word(tlst,i).' Myr'

set output 'sbl_mid.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface brightness [L_{sun}/pc^2]'
plot [0.09:100][0.001:1E6] for [i=1:7] word(lst,i) u 1:3 smooth bezier w l lt i lc word(colori,i) t word(tlst,i).' Myr', \
                 for [i=1:7] word(lst,i) u 1:3 w p lt i lc word(colori,i) t ''

set output 'sbmag_ave.'.suffix
set logscale x
unset logscale y
set xlabel 'r [arcsec]'
set ylabel 'Surface brightness [Mag/arcsec^2]'
plot [][34:14] for [i=1:7] word(lst,i) u 5:6 w lp lt i lc word(colori,i) t word(tlst,i).' Myr'

set output 'sbmag_mid.'.suffix
set logscale x
unset logscale y
set xlabel 'r [arcsec]'
set ylabel 'Surface brightness [Mag/arcsec^2]'
plot [][34:14] for [i=1:7] word(lst,i) u 5:7 smooth bezier w l lt i lc word(colori,i) t word(tlst,i).' Myr', \
               for [i=1:7] word(lst,i) u 5:7 w p lt i lc word(colori,i) t ''

reset

set output 'den_ave.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface density [M_{sun}/pc^2]'
plot [0.09:100][] for [i=1:7] word(lst,i) u 1:13 w lp lt i lc word(colori,i) t word(tlst,i).' Myr'

set output 'den_mid.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'Surface density [M_{sun}/pc^2]'
plot [0.09:100][0.001:1E5] for [i=1:7] word(lst,i) u 1:14 smooth bezier w l lt i lc word(colori,i) t word(tlst,i).' Myr', \
                 for [i=1:7] word(lst,i) u 1:14 w p lt i lc word(colori,i) t ''

do for [i=1:7] {
   set table word(lst,i).'.smooth_sb'
   plot [][] word(lst,i) u 1:3 smooth bezier
   set table word(lst,i).'.smooth_sd'
   plot [][] word(lst,i) u 1:14 smooth bezier
   unset table
}

system("sh merge_smooth_sb_sd.sh")

set output 'M_L_ave.'.suffix
set logscale x
unset logscale y
set xlabel 'r [pc]'
set ylabel 'M/L [M_{sun}/L_{sun}]'
plot [0.09:100][0:24] for [i=1:7] word(lst,i) u 1:($13/$2) w lp lc word(colori,i) t word(tlst,i).' Myr'

set output 'M_L_mid.'.suffix
set logscale x
set logscale y
set xlabel 'r [pc]'
set ylabel 'M/L [M_{sun}/L_{sun}]'
plot [0.09:100][0.001:100] for [i=1:7] word(lst,i) u 1:($14/$3) smooth bezier w l lt i lc word(colori,i) t word(tlst,i).' Myr', \
                     for [i=1:7] word(lst,i) u 1:($14/$3) w p lt i lc word(colori,i) t ''

set output 'M_L_smooth.'.suffix
set logscale x
unset logscale y
set xlabel 'r [pc]'
set ylabel 'M/L [M_{sun}/L_{sun}]'
plot [0.09:100][0:24] for [i=1:7] word(lst,i).'.smooth' u 1:($3/$2) w l lt i lc word(colori,i) t word(tlst,i).' Myr',\
                      for [i=1:7] word(lst,i) u 1:($14/$3) w p lt i lc word(colori,i) t ''

