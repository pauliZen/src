set term pngcairo enhanced color dashed

set zeroaxis
set grid

set macro

tscale = 0.622

#set key autotitle columnhead

#----------------------mass fraction---------------------
set output 'binfm.png'

set xlabel 'Time [Myr]'
set ylabel 'Binary mass fraction'
shift = 162
shiftn = 108
shiftm = 54

plot [0:2500][0:0.2] 'lagr.snap.b' \
         u ($1*tscale):(column(shift+5 )/(column(shiftn+5 )*column(shiftm+5 ))) t columnheader(shiftm+5 ) w l lt 1 lc 2 lw 2 smooth csplines, \
      '' u ($1*tscale):(column(shift+8 )/(column(shiftn+8 )*column(shiftm+8 ))) t columnheader(shiftm+8 ) w l lt 1 lc 3 lw 2 smooth csplines, \
      '' u ($1*tscale):(column(shift+12)/(column(shiftn+12)*column(shiftm+12))) t columnheader(shiftm+12) w l lt 1 lc 4 lw 2 smooth csplines, \
      '' u ($1*tscale):(column(shift+14)/(column(shiftn+14)*column(shiftm+14))) t columnheader(shiftm+14) w l lt 1 lc 7 lw 2 smooth csplines 

#---------------------number fraction-----------------
set output 'binfn.png'

set xlabel 'Time [Myr]'
set ylabel 'Binary number fraction'
set key left bottom
shift = 180
shiftn = 108

plot [0:2500][0.03:0.07] 'lagr.snap.b' \
         u ($1*tscale):(column(shift+5 )/(column(shiftn+5 )-column(shift+5 ))) t columnheader(shift+5 ) w l lt 1 lc 2 lw 2 smooth csplines, \
      '' u ($1*tscale):(column(shift+8 )/(column(shiftn+8 )-column(shift+8 ))) t columnheader(shift+8 ) w l lt 1 lc 3 lw 2 smooth csplines, \
      '' u ($1*tscale):(column(shift+12)/(column(shiftn+12)-column(shift+12))) t columnheader(shift+12) w l lt 1 lc 4 lw 2 smooth csplines, \
      '' u ($1*tscale):(column(shift+14)/(column(shiftn+14)-column(shift+14))) t columnheader(shift+14) w l lt 1 lc 7 lw 2 smooth csplines 

#---------------------mass---------------------------
# set output 'binm.png'

#plot [0:2500][] 'lagr.snap.b' \
#         u ($1*tscale):(column(shift+5 )) t columnheader(shiftm+5 ) w l lt 2 lc 2 lw 2, \
#      '' u ($1*tscale):(column(shift+8 )) t columnheader(shiftm+8 ) w l lt 2 lc 3 lw 2, \
#      '' u ($1*tscale):(column(shift+12)) t columnheader(shiftm+12) w l lt 2 lc 4 lw 2, \
#      '' u ($1*tscale):(column(shift+14)) t columnheader(shiftm+14) w l lt 2 lc 7 lw 2


