#set term pngcairo enhanced color dashed
set term epscairo enhanced color dashed size 14,10 font ',24'
#set term pngcairo enhanced color dashed size 1400,1000 font ',24'
#set term postscript landscape enhanced color "Text" 16
#set output 'data.py.ps'
suffix='eps'
#set output 'data.'.suffix

#set zeroaxis
#set grid
#set pointsize 1.0
#set mxtics 10
#set mytics 10
set macro
#set key autotitle columnhead

rscale = 1.0
tscale = 5.506190205940E-01
mscale = 1.0
vscale = 1.0

filename = 'lagr.bh.snap'
jump = "every ::1"
#jump = ""

####---------------macro 5 columns----------------
colu5 =  "u (column(x)*xscale):(column(1+shift)*yscale)    t columnhead(1+shift)  w l lc 1 lt type lw 4, \
       '' u (column(x)*xscale):(column(4+shift)*yscale)    t columnhead(4+shift)  w l lc 2 lt type lw 4, \
       '' u (column(x)*xscale):(column(7+shift)*yscale)    t columnhead(7+shift)  w l lc 3 lt type lw 4, \
       '' u (column(x)*xscale):(column(11+shift)*yscale)   t columnhead(11+shift) w l lc 4 lt type lw 4, \
       '' u (column(x)*xscale):(column(15+shift)*yscale)   t columnhead(15+shift) w l lc 5 lt type lw 4"

#colu5 =  "u (column(x)*xscale):((column(1+shift)>0.e-10)?column(1+shift)*yscale:1/0)    t columnhead(1+shift)  w l lc 1 lt type lw 4, \
#       '' u (column(x)*xscale):((column(4+shift)>0.e-10)?column(4+shift)*yscale:1/0)    t columnhead(4+shift)  w l lc 2 lt type lw 4, \
#       '' u (column(x)*xscale):((column(7+shift)>0.e-10)?column(7+shift)*yscale:1/0)    t columnhead(7+shift)  w l lc 3 lt type lw 4, \
#       '' u (column(x)*xscale):((column(11+shift)>0.e-10)?column(11+shift)*yscale:1/0)   t columnhead(11+shift) w l lc 4 lt type lw 4, \
#       '' u (column(x)*xscale):((column(15+shift)>0.e-10)?column(15+shift)*yscale:1/0)   t columnhead(15+shift) w l lc 5 lt type lw 4"

colu52 =" u (column(x)*xscale):(column(1+shift2)*yscale)    t title2 w l lc 1 lt type2 lw 4, \
       '' u (column(x)*xscale):(column(4+shift2)*yscale)    t '' w l lc 2 lt type2 lw 4, \
       '' u (column(x)*xscale):(column(7+shift2)*yscale)    t '' w l lc 3 lt type2 lw 4, \
       '' u (column(x)*xscale):(column(11+shift2)*yscale)   t '' w l lc 4 lt type2 lw 4, \
       '' u (column(x)*xscale):(column(15+shift2)*yscale)   t '' w l lc 5 lt type2 lw 4"

#colu52 =" u (column(x)*xscale):((column(1+shift2)>0.e-10)?column(1+shift2)*yscale:1/0)    t title2 w l lc 1 lt type2 lw 4, \
#       '' u (column(x)*xscale):((column(4+shift2)>0.e-10)?column(4+shift2)*yscale:1/0)    t '' w l lc 2 lt type2 lw 4, \
#       '' u (column(x)*xscale):((column(7+shift2)>0.e-10)?column(7+shift2)*yscale:1/0)    t '' w l lc 3 lt type2 lw 4, \
#       '' u (column(x)*xscale):((column(11+shift2)>0.e-10)?column(11+shift2)*yscale:1/0)   t '' w l lc 4 lt type2 lw 4, \
#       '' u (column(x)*xscale):((column(15+shift2)>0.e-10)?column(15+shift2)*yscale:1/0)   t '' w l lc 5 lt type2 lw 4"


####---------------macro 12 columns----------------
colu12 = "u (column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

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

####---------------macro 12 columns----------------
colu_sqrt12 = "u (column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

####---------------macro 12 columns----------------
colu_r12 = "u (1/column(x)*xscale):(column(1+shift)*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (1/column(x)*xscale):(column(2+shift)*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (1/column(x)*xscale):(column(3+shift)*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (1/column(x)*xscale):(column(4+shift)*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (1/column(x)*xscale):(column(5+shift)*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (1/column(x)*xscale):(column(6+shift)*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (1/column(x)*xscale):(column(7+shift)*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (1/column(x)*xscale):(column(8+shift)*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (1/column(x)*xscale):(column(9+shift)*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (1/column(x)*xscale):(column(10+shift)*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (1/column(x)*xscale):(column(11+shift)*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

####---------------macro 12 columns----------------
colu_r_sqrt12 = "u (1/column(x)*xscale):(sqrt(column(1+shift))*yscale)   t columnhead(1+shift) w l lt 1 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(2+shift))*yscale)   t columnhead(2+shift) w l lt 2 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(3+shift))*yscale)   t columnhead(3+shift) w l lt 3 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(4+shift))*yscale)   t columnhead(4+shift) w l lt 4 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(5+shift))*yscale)   t columnhead(5+shift) w l lt 5 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(6+shift))*yscale)   t columnhead(6+shift) w l lt 6 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(7+shift))*yscale)   t columnhead(7+shift) w l lt 7 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(8+shift))*yscale)   t columnhead(8+shift) w l lt 8 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(9+shift))*yscale)   t columnhead(9+shift) w l lt 9 lw 4, \
           '' u (1/column(x)*xscale):(sqrt(column(10+shift))*yscale)  t columnhead(10+shift) w l lt 1 lw 1, \
           '' u (1/column(x)*xscale):(sqrt(column(11+shift))*yscale)  t columnhead(11+shift) w l lt 2 lw 1"

xr=""
yr=""

####---------------plot lagr----------------------
# set output 'lagr.'.suffix
# set ylabel 'R_{lagr} [pc]'
# set xlabel 't [Myr]'
# set autoscale
# #set logscale y 10
# set nologscale x
# x = 1
# shift = 1
# xscale = tscale
# yscale = rscale
#
# plot [@xr][@yr] filename @jump @colu18

####---------------plot star,bh lagr----------------------
set output 'lagr.'.suffix

set ylabel 'R_{lagr} [pc]'
set xlabel 't [Myr]'
set autoscale
set logscale y 10
set nologscale x
x = 1
shift = 19
shift2 = 37
type = 1
type2 = 2
title2 = 'BH'
xscale = tscale
yscale = rscale
xr=""
yr="2E-3:2E3"

plot [@xr][@yr] filename @jump @colu5, \
                '' @colu52

xr=""
yr=""
####---------------plot AVMASS------------------
# set output 'avemass.'.suffix
# set ylabel '<M> [M_{sun}]'
# set xlabel 't [Myr]'
# set autoscale
# set nologscale y
# set nologscale x
# x = 1
# shift = 55
# xscale = tscale
# yscale = mscale
#
# plot [@xr][@yr] filename @jump @colu18

####---------------plot s,AVMASS------------------
set output 'avemass.'.suffix
set ylabel '<M_s> [M_{sun}]'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 73
shift2 = 91
type = 1
type2 = 2
title2 = 'BH'
xscale = tscale
yscale = mscale

plot [@xr][@yr] filename @jump @colu5, \
                      '' @colu52

####---------------plot NPARTC------------------
# set output 'npart.'.suffix
# set ylabel 'N'
# set xlabel 't [Myr]'
# set autoscale
# set nologscale y
# set nologscale x
# x = 1
# shift = 109
# xscale = tscale
# yscale = 1
#
# plot [@xr][@yr] filename @jump @colu18

####---------------plot s,NPARTC------------------
set output 'npart.'.suffix
set ylabel 'N_{s}'
set xlabel 't [Myr]'
set autoscale
set nologscale y
set nologscale x
x = 1
shift = 127
shift = 145
type = 1
type2 = 2
title2 = 'BH'
xscale = tscale
yscale = 1

plot [@xr][@yr] filename @jump @colu5, \
                      '' @colu52

#####---------------plot Vx------------------
#set output 'vx.'.suffix
#set ylabel '<V_x> [km/s]'
#set xlabel 't [Myr]'
#set autoscale
#set nologscale y
#set nologscale x
#x = 1
#shift = 94
#xscale = tscale
#yscale = vscale
#
#plot [@xr][@yr] filename @jump @colu19
# 
#####---------------plot Vy------------------
#set output 'vy.'.suffix
#set ylabel '<V_y> [km/s]'
#set xlabel 't [Myr]'
#set autoscale
#set nologscale y
#set nologscale x
#x = 1
#shift = 113
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu19
# 
#####---------------plot Vz------------------
#set output 'vz.'.suffix
#set ylabel '<V_z> [km/s]'
#set xlabel 't [Myr]'
#set autoscale
#set nologscale y
#set nologscale x
#x = 1
#shift = 132
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu19
# 
#####---------------plot V------------------
#set output 'v.'.suffix
#set ylabel '<V> [km/s]'
#set xlabel 't [Myr]'
#set autoscale
#set nologscale y
#set nologscale x
#x = 1
#shift = 151
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu19
# 
#####---------------plot Vr------------------
#set output 'vr'.suffix
#set ylabel '<V_r> [km/s]'
#set xlabel 't [Myr]'
#set autoscale
#set nologscale y
#set nologscale x
#x = 1
#shift = 170
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu19
# 
#####---------------plot Vt------------------
#set output 'vt.'.suffix
#set ylabel '<V_T> [km/s]'
#set xlabel 't [Myr]'
#set autoscale
#set nologscale y
#set nologscale x
#x = 1
#shift = 189
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu19
# 
#####---------------plot Sigma--------------------
#set output 'sigma.'.suffix
#set ylabel '\Sigma [km/s]'
#set xlabel 't [Myr]'
#set nologscale y
#set nologscale x
#x = 1
#shift = 208
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu_sqrt19
# 
#####---------------plot Sigma_r--------------------
#set output 'sigmar.'.suffix
#set ylabel '\Sigma_{r} [km/s]'
#set xlabel 't [Myr]'
#set nologscale y
#set nologscale x
#x = 1
#shift = 227
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu_sqrt19
# 
#####---------------plot Sigma_t------------------
#set output 'sigmat.'.suffix
#set ylabel '\Sigma_{T} [km/s]'
#set xlabel 't [Myr]'
#set nologscale y
#set nologscale x
#x = 1
#shift = 246
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu_sqrt19
# 
#####---------------plot VROT------------------
#set output 'vrot.'.suffix
#set ylabel 'V_{ROT} [km/s]'
#set xlabel 't [Myr]'
#set nologscale y
#set nologscale x
#x = 1
#shift = 265
#xscale = tscale
#yscale = vscale
# 
#plot [@xr][@yr] filename @jump @colu19

