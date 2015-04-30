#set term pngcairo dashed enhanced color size 1024,768
set term epscairo dashed enhanced color size 6.4,4.8
#set term postscript landscape enhanced color "Text" 16
suffix='eps'
#set output 'data.'.suffix

#set zeroaxis
#set grid
#set pointsize 1.0
#set mxtics 10
#set mytics 10
set macro
#set key autotitle columnhead

rscale = 5.0
tscale = 1.0
mscale = 7.49825
vscale = 2.539

filename = 'lagr.7'
jump = "every ::1"
#jump = ""

#Plot range:
trange=""
rrange=""
vrange=""
mrange=""
nrange=""
srange=""

####---------------macro 7 columns----------------
colu7 = "u (column(x)*xscale):(column(1 +shift)*yscale)   t columnhead(1 +shift) w l lc 1 lt 1, \
      '' u (column(x)*xscale):(column(4 +shift)*yscale)   t columnhead(4 +shift) w l lc 2 lt 1, \
      '' u (column(x)*xscale):(column(7 +shift)*yscale)   t columnhead(7 +shift) w l lc 3 lt 1, \
      '' u (column(x)*xscale):(column(9 +shift)*yscale)   t columnhead(9 +shift) w l lc 4 lt 1, \
      '' u (column(x)*xscale):(column(11+shift)*yscale)   t columnhead(11+shift) w l lc 5 lt 1, \
      '' u (column(x)*xscale):(column(13+shift)*yscale)   t columnhead(13+shift) w l lc 6 lt 1, \
      '' u (column(x)*xscale):(column(15+shift)*yscale)   t columnhead(15+shift) w l lc 7 lt 2"

####---------------macro 8 columns----------------
colu8 = "u (column(x)*xscale):(column(1 +shift)*yscale)   t columnhead(1 +shift) w l lc 1 lt 1, \
      '' u (column(x)*xscale):(column(4 +shift)*yscale)   t columnhead(4 +shift) w l lc 2 lt 1, \
      '' u (column(x)*xscale):(column(7 +shift)*yscale)   t columnhead(7 +shift) w l lc 3 lt 1, \
      '' u (column(x)*xscale):(column(9 +shift)*yscale)   t columnhead(9 +shift) w l lc 4 lt 1, \
      '' u (column(x)*xscale):(column(11+shift)*yscale)   t columnhead(11+shift) w l lc 5 lt 1, \
      '' u (column(x)*xscale):(column(13+shift)*yscale)   t columnhead(13+shift) w l lc 6 lt 1, \
      '' u (column(x)*xscale):(column(15+shift)*yscale)   t columnhead(15+shift) w l lc 7 lt 1, \
      '' u (column(x)*xscale):(column(19+shift)*yscale)   t columnhead(19+shift) w l lc 9 lt 2"

####---------------macro 18 columns----------------
colu18 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
       '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
       '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
       '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
       '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
       '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
       '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
       '' u (column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
       '' u (column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
       '' u (column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
       '' u (column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
       '' u (column(x)*xscale):(column(12+shift)*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
       '' u (column(x)*xscale):(column(13+shift)*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
       '' u (column(x)*xscale):(column(14+shift)*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
       '' u (column(x)*xscale):(column(15+shift)*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
       '' u (column(x)*xscale):(column(16+shift)*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
       '' u (column(x)*xscale):(column(17+shift)*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
       '' u (column(x)*xscale):(column(18+shift)*yscale)  t columnhead(18+shift) w l lt 9 lw 1"

####---------------macro 19 columns----------------
colu19 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
       '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
       '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
       '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
       '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
       '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
       '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
       '' u (column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
       '' u (column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
       '' u (column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
       '' u (column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
       '' u (column(x)*xscale):(column(12+shift)*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
       '' u (column(x)*xscale):(column(13+shift)*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
       '' u (column(x)*xscale):(column(14+shift)*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
       '' u (column(x)*xscale):(column(15+shift)*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
       '' u (column(x)*xscale):(column(16+shift)*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
       '' u (column(x)*xscale):(column(17+shift)*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
       '' u (column(x)*xscale):(column(18+shift)*yscale)  t columnhead(18+shift) w l lt 9 lw 1, \
       '' u (column(x)*xscale):(column(19+shift)*yscale)  t columnhead(19+shift) w l lt 1 lw 6"

####---------------macro 18 columns----------------
colu_sqrt18 = "u (column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(12+shift))*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(13+shift))*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(14+shift))*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(15+shift))*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(16+shift))*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(17+shift))*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(18+shift))*yscale)  t columnhead(18+shift) w l lt 9 lw 1"

####---------------macro 19 columns----------------
colu_sqrt19 = "u (column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
            '' u (column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(12+shift))*yscale)  t columnhead(12+shift) w l lt 3 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(13+shift))*yscale)  t columnhead(13+shift) w l lt 4 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(14+shift))*yscale)  t columnhead(14+shift) w l lt 5 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(15+shift))*yscale)  t columnhead(15+shift) w l lt 6 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(16+shift))*yscale)  t columnhead(16+shift) w l lt 7 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(17+shift))*yscale)  t columnhead(17+shift) w l lt 8 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(18+shift))*yscale)  t columnhead(18+shift) w l lt 9 lw 1, \
            '' u (column(x)*xscale):(sqrt(column(19+shift))*yscale)  t columnhead(19+shift) w l lt 1 lw 6"

####---------------macro 7 columns----------------
colu_sqrt7 = "u (column(x)*xscale):(sqrt(column(1 +shift))*yscale)   t columnhead(1 +shift) w l lc 1 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(4 +shift))*yscale)   t columnhead(4 +shift) w l lc 2 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(7 +shift))*yscale)   t columnhead(7 +shift) w l lc 3 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(9 +shift))*yscale)   t columnhead(9 +shift) w l lc 4 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)   t columnhead(11+shift) w l lc 5 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(13+shift))*yscale)   t columnhead(13+shift) w l lc 6 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(15+shift))*yscale)   t columnhead(15+shift) w l lc 7 lt 2"

####---------------macro 8 columns----------------
colu_sqrt8 = "u (column(x)*xscale):(sqrt(column(1 +shift))*yscale)   t columnhead(1 +shift) w l lc 1 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(4 +shift))*yscale)   t columnhead(4 +shift) w l lc 2 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(7 +shift))*yscale)   t columnhead(7 +shift) w l lc 3 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(9 +shift))*yscale)   t columnhead(9 +shift) w l lc 4 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)   t columnhead(11+shift) w l lc 5 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(13+shift))*yscale)   t columnhead(13+shift) w l lc 6 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(15+shift))*yscale)   t columnhead(15+shift) w l lc 7 lt 1, \
	   '' u (column(x)*xscale):(sqrt(column(19+shift))*yscale)   t columnhead(19+shift) w l lc 9 lt 2"

####---------------plot lagr----------------------
set output 'lagr.'.suffix
set ylabel 'R_{lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
#set logscale y 10
set nologscale x
x = 1
shift = 1
xscale = tscale
yscale = rscale

plot [@trange][@rrange] filename @jump @colu8

####---------------plot s,lagr----------------------
set output 'slagr.'.suffix

set ylabel 'R_{s,lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
#set logscale y 10
set nologscale x
x = 1
shift = 20
xscale = tscale
yscale = rscale

plot [@trange][@rrange] filename @jump @colu7

####---------------plot b,lagr----------------------
set output 'blagr.'.suffix

set ylabel 'R_{b,lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
#set logscale y 10
set nologscale x
x = 1
shift = 38
xscale = tscale
yscale = rscale

plot [@trange][@rrange] filename @jump @colu7

####---------------plot AVMASS------------------
set output 'avemass.'.suffix
set ylabel '<M> [M_{sun}]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 56
xscale = tscale
yscale = mscale

plot [@trange][@mrange] filename @jump @colu8

####---------------plot NPARTC------------------
set output 'npart.'.suffix
set ylabel 'NPART'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 75
xscale = tscale
yscale = 1

plot [@trange][@nrange] filename @jump @colu8

####---------------plot Vx------------------
set output 'vx.'.suffix
set ylabel '<V_x> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 94
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

####---------------plot Vy------------------
set output 'vy.'.suffix
set ylabel '<V_y> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 113
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

####---------------plot Vz------------------
set output 'vz.'.suffix
set ylabel '<V_z> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 132
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

####---------------plot V------------------
set output 'v.'.suffix
set ylabel '<V> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 151
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

####---------------plot Vr------------------
set output 'vr.'.suffix
set ylabel '<V_r> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 170
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

####---------------plot Vt------------------
set output 'vt.'.suffix
set ylabel '<V_T> [km/s]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 189
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

####---------------plot Sigma--------------------
set output 'sigma.'.suffix
set ylabel '\Sigma [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 208
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt8

####---------------plot Sigma_r--------------------
set output 'sigmar.'.suffix
set ylabel '\Sigma_{r} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 227
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt8

####---------------plot Sigma_t------------------
set output 'sigmat.'.suffix
set ylabel '\Sigma_{T} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 246
xscale = tscale
yscale = vscale

plot [@trange][@srange] filename @jump @colu_sqrt8

####---------------plot VROT------------------
set output 'vrot.'.suffix
set ylabel 'V_{ROT} [km/s]'
set xlabel 't [Myr]'
set nologscale y
set nologscale x
x = 1
shift = 265
xscale = tscale
yscale = vscale

plot [@trange][@vrange] filename @jump @colu8

