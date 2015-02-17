#set term gif size 900,900 font ',22'
set term pngcairo enhanced color dashed size 1200,1000 font ',22'

set macro

cplot="u 4:5:($2>0&&$2<14?log10($3)+3:1/0):7  w p pt 6  ps var lc pal z t 'Star', \
    '' u 4:5:($2==14?     log10($3)+3:1/0):7  w p pt 7  ps var lc pal z t 'BH', \
    '' u 4:5:($2==-1?     log10($3)+3:1/0):7  w p pt 4  ps var lc pal z t 'Binary', \
    '' u 4:5:($2==-10?    log10($3)+3:1/0):7  w p pt 5  ps var lc pal z t 'BH Binary', \
    '' u 4:5:($2==-11?    log10($3)+3:1/0):7  w p pt 13 ps var lc pal z t 'BH-BH Binary', \
    '' u 4:5:($2==-2?     log10($3)+3:1/0):7  w p pt 8  ps var lc pal z t 'Triple', \
    '' u 4:5:($2==-100?   log10($3)+3:1/0):7  w p pt 9  ps var lc pal z t 'BH Triple', \
    '' u 4:5:($2==-110?   log10($3)+3:1/0):7  w p pt 14 ps var lc pal z t 'BH-BH Triple', \
    '' u 4:5:($2==-111?   log10($3)+3:1/0):7  w p pt 15 ps var lc pal z t '3-BH Triple'"

set colorbox

xr="-0.43:0.43"
yr="-0.43:0.43"

set cbrange [1.0:1.3]

tlst=system("ls pots*|cut -d'.' -f2-3")

do for [i in tlst] {
   file = sprintf('pots.%s',i)
   outfile = sprintf('fig_pots.%s.png',i)
   set output outfile
   set title sprintf('%s NB Time',i)
   plot [@xr][@yr] file @cplot
}

set term epscairo enhanced color dashed size 12,10 font ',22'

tscale = 0.56

set output 'r_pot.eps'
set key right bottom
set xlabel 'Radius[pc]'
set ylabel 'Potential[NB]'
set label 1 "Open circle: star" at 0.05,-1.73
set label 2 "Filled circle: BH" at 0.05,-1.75

k=0
plot [0:0.4] for [i=1:24] 'pots.'.word(tlst,i)  u 8:(-$7) w l t word(tlst,i).' NB Time' lt i , \
             for [i=1:24] 'pots.'.word(tlst,i)  u 8:($9<0&&$9>=-50?-$7:1/0):(log10($3)) w p pt 6 ps var lt i t '', \
             for [i=1:24] 'pots.'.word(tlst,i)  u 8:($9>0&&$9<=50?-$7:1/0):(log10($3)) w p pt 7 ps var lt i t ''
