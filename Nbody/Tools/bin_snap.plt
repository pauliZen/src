set term pngcairo enhanced color dashed size 1200,1000 font ',22'

set macro

tlst=system("cat bin.lst|cut -d ' ' -f1")
tt=system("cat bin.lst|cut -d ' ' -f2")

tscale = 0.5506
mscale = 606363
rscale = 9.375
rau = 206265

#set colorbox
#set cbrange [0:1]
#set cblabel 'Eccentricity'

set xlabel 'Energy [NB]'
set ylabel 'Distance [pc]'
set logscale y 10
set logscale x 10
set zrange [0:80]
#set key left top

do for [i=1:25] {
   set title word(tt,i).' Myr'
   set output 'er_'.word(tt,i).'.png'
#   plot [0.0001:1000][0.1:100] word(tlst,i) u (escale*$3*$4/$11):(sqrt($5*$5+$6*$6+$7*$7)):12 w p ps 0.1 lc pal z lt 7
    splot [1E-10:0.01][0.1:100] 'er_'.word(tlst,i) u ($1/mscale/mscale*rau*rscale/2):2:3 t ''
}
   
