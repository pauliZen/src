#set term pngcairo enhanced color dashed #size 1200,1000 font ',22'
#Preprocess: gether_color.sh
set term epscairo dashed enhanced color size 6.4,4.8
suffix='eps'

set macro

tlst=system("cut -d' ' -f2 dlist")
lst=system("cut -d' ' -f1 sbclst")
filter='B'
rclstb=system("awk '{print $2}' king-fit-lum-".filter.".dat")
rtlstb=system("awk '{print $4}' king-fit-lum-".filter.".dat")
klstb=system("awk '{print $6/$8/3.1415926/$2**2}' king-fit-lum-".filter.".dat")

filter='V'
rclstv=system("awk '{print $2}' king-fit-lum-".filter.".dat")
rtlstv=system("awk '{print $4}' king-fit-lum-".filter.".dat")
klstv=system("awk '{print $6/$8/3.1415926/$2**2}' king-fit-lum-".filter.".dat")

filter='I'
rclsti=system("awk '{print $2}' king-fit-lum-".filter.".dat")
rtlsti=system("awk '{print $4}' king-fit-lum-".filter.".dat")
klsti=system("awk '{print $6/$8/3.1415926/$2**2}' king-fit-lum-".filter.".dat")

colori="1 2 3 4 5 7 9"

f(x,k,rc,rt) = x<rt?(-2.5*log10(k*(1.0/(1.0+(x/rc)**2)**0.5 - 1.0/(1.0+(rt/rc)**2)**0.5)**2)):1/0

set output 'colorB-V_fit.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel 'B-V [Mag/arcsec^2]'
plot [0.1:100][-0.5:1.5] for [i=1:7] word(lst,i) u 1:6 w p lt i lc word(colori,i) t word(tlst,i).' Myr', \
                 for [i=1:7] word(lst,i) u 1:(0.65+f($1,word(klstb,i),word(rclstb,i),word(rtlstb,i))-(f($1,word(klstv,i),word(rclstv,i),word(rtlstv,i)))) w l lt i lc word(colori,i) t ''

set output 'colorV-I_fit.'.suffix
set logscale x
set xlabel 'r [pc]'
set ylabel 'V-I [Mag/arcsec^2]'
plot [0.1:100][-0.5:1.5] for [i=1:7] word(lst,i) u 1:7 w p lt i lc word(colori,i) t word(tlst,i).' Myr', \
                 for [i=1:7] word(lst,i) u 1:(0.76+f($1,word(klstv,i),word(rclstv,i),word(rtlstv,i))-(f($1,word(klsti,i),word(rclsti,i),word(rtlsti,i)))) w l lt i lc word(colori,i) t ''
