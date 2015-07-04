rt = 100
rc = 3
NTOT = 1000000

lst=system("cut -d' ' -f1 dlst")
tlst=system("cut -d' ' -f2 dlst")

do for [i=1:34] {

reset

filename=word(lst,i)

set table filename.'.ncum'

plot [][] filename u ($19>12&&$20>12?1/0:sqrt($23*$23+$24*$24)):(1.0) smooth cumulative

unset table

n(x) = NTOT*( log(1.0+(x/rc)**2) - 4.0*( sqrt(1.0+(x/rc)**2) - 1.0 )/sqrt(1.0+(rt/rc)**2) + (x/rc)**2/(1.0+(rt/rc)**2) ) / ( log(1.0+(rt/rc)**2) - ( 3.0*sqrt(1.0+(rt/rc)**2) - 1.0 ) * ( sqrt(1.0+(rt/rc)**2) - 1.0 ) / (1.0+(rt/rc)**2) )

set fit errorvariables

fit n(x) filename.'.ncum' every 10::5 u 1:2 via rc, rt, NTOT

n0 = ( log(1.0+(rt/rc)**2) - ( 3.0*sqrt(1.0+(rt/rc)**2) - 1.0 ) * ( sqrt(1.0+(rt/rc)**2) - 1.0 ) / (1.0+(rt/rc)**2) )

print sprintf(' Time Rc Rc_err Rt Rt_err N0 %s %f %f %f %f %f %d %d', word(tlst,i), rc, rc_err, rt, rt_err, n0, NTOT, NTOT_err)

########################
set term epscairo enhanced color dashed #size 1200,1000 font ',22'
#set term postscript landscape enhanced color "Text" 14
#set term postscript eps enhanced color solid "Text" 16
#set term postscript portrait enhanced color "Text" 16

set output filename.".kfit.eps"

set zeroaxis
#set grid
set pointsize 0.1
set mxtics 10
set mytics 10

set key top left

FIT_LIMIT=1e-6

set xlabel 'r[pc]'
set ylabel 'Number'

#set xrange [1e-1:]
#set yrange [:1]

#set xtic 0.0,20.0,100.0
#set ytic 1e-6,,2,0

set logscale x 10.0
set logscale y 10.0

#set format x "%.2f"
#set format x "10^{%T}"

#set format y "%.2f"
#set format y "10^{%T}"
#set format y "%T"

plot [][] filename.'.ncum' every 20::5 u 1:2 t 'T= '.word(tlst,i).' Myr' w l lt 1 lc 1 lw 2, \
          n(x) t 'King fit.' w l lt 1 lc 2 lw 1
}
