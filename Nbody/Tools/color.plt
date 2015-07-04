#set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set term epscairo dashed enhanced color size 6.4,4.8
suffix='eps'

load 'color.fct'
set macro

tlst=system("cut -d' ' -f2 sbclst")
lst=system("cut -d' ' -f1 sbclst")
nn=system("wc -l sbclst|cut -d' ' -f1")

set output 'colorB-V.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel 'B-V [Mag/arcsec^2]'
plot [0.1:100][1.35:1.6] for [i=1:nn] word(lst,i) u 1:4 smooth bezier w l lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr', \
                 for [i=1:nn] word(lst,i) u 1:4 w p lt i lc  rgbcolor word(colors10,i) t ''

set output 'colorV-I.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel 'V-I [Mag/arcsec^2]'
plot [0.1:100][1:3] for [i=1:nn] word(lst,i) u 1:8 smooth bezier w l lt i lc  rgbcolor word(colors10,i) t word(tlst,i).' Myr', \
                      for [i=1:nn] word(lst,i) u 1:8 w p lt i lc  rgbcolor word(colors10,i) t ''
