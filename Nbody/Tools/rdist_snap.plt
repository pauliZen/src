set term pngcairo enhanced color dashed size 1200,1000 font ',22'

set macro

tlst=system("cat rdist.lst|cut -d ' ' -f1")
tt=system("cat rdist.lst|cut -d ' ' -f2")

tscale = 0.5506

do for [i=1:25] {
   set title word(tt,i).' Myr'
   set xlabel 'r [pc]'
   set ylabel 'Cumulative mass [M_{sun}]'
   set output 'rdist_'.word(tt,i).'.png'
   set logscale y 10
   set logscale x 10
   set key left top
   plot [0.01:100][0.1:1000000] word(tlst,i) \
                          u 1:3 t 'MS (0.08-0.4 M_{sun})' w l lw 4 lc 1 lt 1, \
                       '' u 1:5 t 'MS (0.4-0.7 M_{sun})'  w l lw 4 lc 2 lt 1, \
                       '' u 1:7 t 'MS (0.7-100 M_{sun})'  w l lw 4 lc 3 lt 1, \
                       '' u 1:9 t 'RG'                    w l lw 4 lc 4 lt 1, \
                       '' u 1:15 t 'AGB'                  w l lw 4 lc 5 lt 1, \
                       '' u 1:17 t 'WD'                   w l lw 4 lc 9 lt 1, \
                       '' u 1:19 t 'NS'                   w l lw 4 lc 7 lt 1, \
                       '' u 1:21 t 'BH'                   w l lw 4 lc 8 lt 1, \
  'h'.word(tlst,i)        u 2:($1==3?$3:1/0)  t ''        w p ps 3 lc 1 lt 7, \
                       '' u 2:($1==5?$3:1/0)  t ''        w p ps 3 lc 2 lt 7, \
                       '' u 2:($1==7?$3:1/0)  t ''        w p ps 3 lc 3 lt 7, \
                       '' u 2:($1==9?$3:1/0)  t ''        w p ps 3 lc 4 lt 7, \
                       '' u 2:($1==15?$3:1/0) t ''        w p ps 3 lc 5 lt 7, \
                       '' u 2:($1==17?$3:1/0) t ''        w p ps 3 lc 9 lt 7, \
                       '' u 2:($1==19?$3:1/0) t ''        w p ps 3 lc 7 lt 7, \
                       '' u 2:($1==21?$3:1/0) t ''        w p ps 3 lc 8 lt 7
}
   
do for [i=1:25] {
   set title word(tt,i).' Myr'
   set xlabel 'r [pc]'
   set ylabel 'Cumulative number'
   set output 'rdist_n_'.word(tt,i).'.png'
   set logscale y 10
   set logscale x 10
   set key left top
   plot [0.01:100][1:1000000] word(tlst,i) \
                          u 1:2 t 'MS (0.08-0.4 M_{sun})' w l lw 4 lc 1 lt 1, \
                       '' u 1:4 t 'MS (0.4-0.7 M_{sun})'  w l lw 4 lc 2 lt 1, \
                       '' u 1:6 t 'MS (0.7-100 M_{sun})'  w l lw 4 lc 3 lt 1, \
                       '' u 1:8 t 'RG'                    w l lw 4 lc 4 lt 1, \
                       '' u 1:14 t 'AGB'                  w l lw 4 lc 5 lt 1, \
                       '' u 1:16 t 'WD'                   w l lw 4 lc 9 lt 1, \
                       '' u 1:18 t 'NS'                   w l lw 4 lc 7 lt 1, \
                       '' u 1:20 t 'BH'                   w l lw 4 lc 8 lt 1, \
  'h'.word(tlst,i)        u 2:($1==2?$3:1/0)  t ''        w p ps 3 lc 1 lt 7, \
                       '' u 2:($1==4?$3:1/0)  t ''        w p ps 3 lc 2 lt 7, \
                       '' u 2:($1==6?$3:1/0)  t ''        w p ps 3 lc 3 lt 7, \
                       '' u 2:($1==8?$3:1/0)  t ''        w p ps 3 lc 4 lt 7, \
                       '' u 2:($1==14?$3:1/0) t ''        w p ps 3 lc 5 lt 7, \
                       '' u 2:($1==16?$3:1/0) t ''        w p ps 3 lc 9 lt 7, \
                       '' u 2:($1==18?$3:1/0) t ''        w p ps 3 lc 7 lt 7, \
                       '' u 2:($1==20?$3:1/0) t ''        w p ps 3 lc 8 lt 7
}
   