#set term gif size 900,900 font ',22'
set term pngcairo enhanced color dashed size 1000,1200 font ',22'

set macro

tlst=system("cat snap.lst|cut -d'_' -f2")

xr="-1.0:1.0"

set size ratio 1
set ticslevel 0
shifts = 3000

do for [i in tlst] {
   outfile = sprintf('fig_SNAP_%s.png',i)
   set output outfile
   dt=system("head -1 SNAP_".i."|awk '{print $8}'")
   set title sprintf('T = %s ; Step = %s (NB Time)',i,dt)
   splot [@xr][@xr][@xr] 'SNAP_'.i \
      u 4:5:6:($7==1? ((shifts*$3)**0.3):1/0) w p pt 7 ps var lc 0 t 'NB', \
  ''  u 4:5:6:($7==0? ((shifts*$3)**0.3):1/0) w p pt 6 ps var lc 1 t 'Non-NB', \
  ''  u 4:5:6:($2==5? ((shifts*$3)**0.3):1/0) w p pt 7 ps var lc 4 t '', \
  ''  u 4:5:6:($2==505?((shifts*$3)**0.3):1/0) w p pt 13 ps var lc 4 t '', \
  ''  u 4:5:6:($7==2? ((shifts*$3)**0.3):1/0) w p pt 7 ps var lc 3 t 'REG'
}
