set term pngcairo enhanced color dashed size 1200,1000 font ',20'

set macro

tscale = 0.55062

cplot=" u ($1*tscale):($17==5?$13*(1-$14):1/0):($23/100):6 w p lc pal z ps var pt 6 t 'First AGB', \
    ''  u ($1*tscale):($17==6?$13*(1-$14):1/0):($23/100):6 w p lc pal z ps var pt 7 t 'Second AGB', \
    ''  u ($1*tscale):($17==0?$13*(1-$14):1/0):($23/100):6 w p lc pal z ps var pt 5 t 'MS', \
    ''  u ($1*tscale):($17==4?$13*(1-$14):1/0):($23/100):6 w p lc pal z ps var pt 4 t 'RG'"
#    ''  u ($1*tscale+10):($13*(1-$14)):($6/$5)  w labels "

aeplot="u ($17==5?$13:1/0):14:($23/100):(($7*$7+$8*$8+$9*$9)**0.5) w p lc pal z ps var pt 6 t 'First AGB', \
    ''  u ($17==6?$13:1/0):14:($23/100):(($7*$7+$8*$8+$9*$9)**0.5) w p lc pal z ps var pt 7 t 'Second AGB', \
    ''  u ($17==0?$13:1/0):14:($23/100):(($7*$7+$8*$8+$9*$9)**0.5) w p lc pal z ps var pt 5 t 'MS', \
    ''  u ($17==4?$13:1/0):14:($23/100):(($7*$7+$8*$8+$9*$9)**0.5) w p lc pal z ps var pt 4 t 'RG'"


set xlabel 'Time [Myr]'
set cblabel 'Mass [M_{sun}]'
set ylabel 'Pericenter distance [AU]'

#----------------------------------
set output 'xlb_wd.png'
set cbrange [0.08:2.5]
#set logscale zcb
set title 'WD X-ray binary'

plot [][] 'xlb_wd' @cplot

#----------------------------------
set output 'xlb_bh.png'
set cbrange [0.08:40]
set title 'BH X-ray binary'

plot [][] 'xlb_bh' @cplot

#--------------------------------------
set cbrange [0:100]
#set logscale zcb
set cblabel 'Distance to the center [pc]'
set xlabel 'Semi-major axis [AU]'
set ylabel 'Eccentricity'
set key right bottom

#------------------------------------
set output 'xlb_wd_ae.png'

set title ''
plot [0:40][0:1] 'xlb_wd' @aeplot

#------------------------------------
set output 'xlb_bh_ae.png'

set title ''
plot [0:40][0:1] 'xlb_bh' @aeplot


