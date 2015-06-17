# King model fitting use cumulative luminosity based on Morscher, M., Pattabiraman, B., Rodriguez, C., Rasio, F. A., & Umbreit, S. (2015).ApJ, 800, 9
# require dlst (projected_datafile time[Myr])
# require dpar (parameter for filters: suffix msun ncolumn)

rc = 3
rt = 100
s0 = 1E7

## suffix=system("awk '{print $1}' dpar")
## msun=system("awk '{print $2}' dpar")
## mcol=system("awk '{print $3}' dpar")

# V filter
suffix='V'
msun=4.83
mcol=18

# I filter
## suffix='I'
## msun = 4.08
## mcol = 21

# B filter
## suffix='B'
## msun = 5.48
## mcol = 20

lst=system("cut -d' ' -f1 dlst")
tlst=system("cut -d' ' -f2 dlst")
nn=system("wc -l dlst|cut -d' ' -f1")

do for [i=1:nn] {

reset

filename=word(lst,i)

set table filename.'.nlum.'.suffix

plot [][] filename u (sqrt($2*$2+$3*$3)):(10.0**(0.4*(msun-column(mcol)))) smooth cumulative

unset table

s(x) = s0*( log(1.0+(x/rc)**2) - 4.0*( sqrt(1.0+(x/rc)**2) - 1.0 )/sqrt(1.0+(rt/rc)**2) + (x/rc)**2/(1.0+(rt/rc)**2) ) / ( log(1.0+(rt/rc)**2) - ( 3.0*sqrt(1.0+(rt/rc)**2) - 1.0 ) * ( sqrt(1.0+(rt/rc)**2) - 1.0 ) / (1.0+(rt/rc)**2) )

set fit errorvariables

s0=system("tail ".filename.".nlum.".suffix."|egrep 'i'|tail -1|awk '{print $2}'")

fit s(x) filename.'.nlum.'.suffix every 10::5 u 1:2 via rc, rt, s0

ss = ( log(1.0+(rt/rc)**2) - ( 3.0*sqrt(1.0+(rt/rc)**2) - 1.0 ) * ( sqrt(1.0+(rt/rc)**2) - 1.0 ) / (1.0+(rt/rc)**2) )

print sprintf(' Time Rc Rc_err Rt Rt_err sigma0 sigma0_err ss %s %f %f %f %f %f %f %f', word(tlst,i), rc, rc_err, rt, rt_err, s0, s0_err, ss)

########################
set term epscairo enhanced color dashed #size 1200,1000 font ',22'
#set term postscript landscape enhanced color "Text" 14
#set term postscript eps enhanced color solid "Text" 16
#set term postscript portrait enhanced color "Text" 16

set output filename.".kfit.".suffix.".eps"

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

plot [][] filename.'.nlum.'.suffix every 20::5 u 1:2 t 'T= '.word(tlst,i).' Myr' w l lt 1 lc 1 lw 2, \
          s(x) t 'King fit.' w l lt 1 lc 2 lw 1
}
