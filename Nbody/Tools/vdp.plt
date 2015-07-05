# plot velocity dispersion profile
# need vdlst (data_file_name time[Myr])

#set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
set term epscairo dashed enhanced color size 6.4,4.8
suffix='eps'

load 'color.fct'

lst=system("cut -d' ' -f1 vdlst")
tlst=system("cut -d' ' -f2 vdlst")
nn=system("wc -l vdlst|cut -d' ' -f1")

set output 'avev_lum.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel '<v_r>[km/s]'
plot [0.1:100][0:11] for [i=1:nn] word(lst,i) every ::2 u 1:2 w lp lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr'

set output 'vdp_lum.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel '<\sigma_r>[km/s]'
plot [0.1:100][0:11] for [i=1:nn] word(lst,i) every ::2 u 1:3 w lp lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr'

set output 'avev_mass.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel '<v_r>[km/s]'
plot [0.1:100][0:11] for [i=1:nn] word(lst,i) every ::2 u 4:5 w lp lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr'

set output 'vdp_mass.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel '<\sigma_r>[km/s]'
plot [0.1:100][0:11] for [i=1:nn] word(lst,i) every ::2 u 4:6 w lp lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr'

set output 'avev.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel '<v_r>[km/s]'
plot [0.1:100][0:11] for [i=1:nn] word(lst,i) every ::2 u 7:8 w lp lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr'

set output 'vdp.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel '<\sigma_r>[km/s]'
plot [0.1:100][0:11] for [i=1:nn] word(lst,i) every ::2 u 7:9 w lp lt i lc rgbcolor word(colors10,i) t word(tlst,i).' Myr'

