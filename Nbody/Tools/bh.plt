#set term postscript landscape enhanced color "Text" 16
#set term pngcairo enhanced color dashed
set term epscairo enhanced color dashed

set zeroaxis

set macro

tscale1=0.622
mscale1=474603
rscale1=9.375

tscale2=0.55062
mscale2=606363
rscale2=9.375

tscale3=0.1382
mscale3=606363
rscale3=3.730335

tscale4=0.54381
mscale4=606363
rscale4=9.29757

set xlabel "Time [Myr]"

ms1="R7_KTG93/bh_score"
ms2="R7_IMF2001/bh_score"
ms3="R3_IMF2001/bh_score"
ms4="R7_ROT/bh_score"

mb1="R7_KTG93/bh_bcore"
mb2="R7_IMF2001/bh_bcore"
mb3="R3_IMF2001/bh_bcore"
mb4="R7_ROT/bh_bcore"

rc1=2.25
rc2=2.09258189
rc3=8.56220511e-01
rc4=3.74210106

mc1=3.65444310e+04
mc2=5.80373161e-01
mc3=2.37354154e-01
mc4=1.09146691

##-------------rc/rc0----------
set output 'rc.eps'
set ylabel "R_{c}/R_{c,0}"
plot [0:1000][] \
   ms1 u ($1*tscale1):($2/rc1)	                  w l lt 1 lc 1 title 'R7\_KTG93' , \
   ms2 u ($1*tscale2):($2/rc2)			  w l lt 1 lc 2 title 'R7\_IMF2001', \
   ms3 u ($1*tscale3):($2/rc3)			  w l lt 1 lc 3 title 'R3\_IMF2001', \
   ms4 u ($1*tscale4):($2/rc4)			  w l lt 1 lc 4 title 'R7\_ROT'

##-------------mc/mc0----------
set output 'mc.eps'
set ylabel 'M_{c}/M_{c,0}'
plot [0:1000][] \
   ms1 u ($1*tscale1):($3/mc1)			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   ms2 u ($1*tscale2):($3/mc2)			  w l lt 1 lc 2 title 'R7\_IMF2001', \
   ms3 u ($1*tscale3):($3/mc3)			  w l lt 1 lc 3 title 'R3\_IMF2001', \
   ms4 u ($1*tscale4):($3/mc4)			  w l lt 1 lc 4 title 'R7\_ROT'

##--------------sbhmc/mc-------------
set output 'sbhmc_mc.eps'
set ylabel 'M_{sbh,c}/M_{c}'
plot [0:1000][] \
   ms1 u ($1*tscale1):($5/$3)			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   ms2 u ($1*tscale2):($5/$3/mscale2*rscale2)	  w l lt 1 lc 2 title 'R7\_IMF2001', \
   ms3 u ($1*tscale3):($5/$3/mscale3*rscale3)	  w l lt 1 lc 3 title 'R3\_IMF2001', \
   ms4 u ($1*tscale4):($5/$3/mscale4*rscale4)	  w l lt 1 lc 4 title 'R7\_ROT'	, \

##-------------bbhmc/mc--------
set output 'bbhmc_mc.eps'
set ylabel 'M_{bbh,c}/M_{c}'
plot [0:1000][] \
   mb1 u ($1*tscale1):($7/$3)			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   mb2 u ($1*tscale2):($7/$3/mscale2*rscale2)	  w l lt 1 lc 2 title 'R7\_IMF2001', \
   mb3 u ($1*tscale3):($7/$3/mscale3*rscale3)	  w l lt 1 lc 3 title 'R3\_IMF2001', \
   mb4 u ($1*tscale4):($7/$3/mscale4*rscale4)	  w l lt 1 lc 4 title 'R7\_ROT'

##-------------dbhm/bbhm--------
set output 'dbhm_bbhm.eps'
set ylabel 'M_{dbh}/M_{bbh}'
plot [0:1000][] \
   mb1 u ($1*tscale1):($9/$5)			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   mb2 u ($1*tscale2):($9/$5)           	  w l lt 1 lc 2 title 'R7\_IMF2001', \
   mb3 u ($1*tscale3):($9/$5)           	  w l lt 1 lc 3 title 'R3\_IMF2001', \
   mb4 u ($1*tscale4):($9/$5)           	  w l lt 1 lc 4 title 'R7\_ROT'

##-------------sbhn--------
set output 'sbhn.eps'
set ylabel 'N_{sbh}'
plot [0:1000][] \
   ms1 u ($1*tscale1):8				  w l lt 1 lc 1 title 'R7\_KTG93' , \
   ms2 u ($1*tscale2):8				  w l lt 1 lc 2 title 'R7\_IMF2001', \
   ms3 u ($1*tscale3):8				  w l lt 1 lc 3 title 'R3\_IMF2001', \
   ms4 u ($1*tscale4):8				  w l lt 1 lc 4 title 'R7\_ROT'

##-------------bbhn--------
set output 'bbhn.eps'
set ylabel 'N_{bbh}'
plot [0:1000][] \
   mb1 u ($1*tscale1):6   			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   mb2 u ($1*tscale2):6   			  w l lt 1 lc 2 title 'R7\_IMF2001', \
   mb3 u ($1*tscale3):6   			  w l lt 1 lc 3 title 'R3\_IMF2001', \
   mb4 u ($1*tscale4):6   			  w l lt 1 lc 4 title 'R7\_ROT'

##-------------dbhn--------
set output 'dbhn.eps'
set ylabel 'N_{dbh}'
plot [0:1000][] \
   mb1 u ($1*tscale1):10 			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   mb2 u ($1*tscale2):10 			  w l lt 1 lc 2 title 'R7\_IMF2001', \
   mb3 u ($1*tscale3):10 			  w l lt 1 lc 3 title 'R3\_IMF2001', \
   mb4 u ($1*tscale4):10 			  w l lt 1 lc 4 title 'R7\_ROT'

##--------------sbhnc/nc-------------
set output 'sbhnc_nc.eps'
set ylabel 'N_{sbh,c}/N_{c}'
plot [0:1000][] \
   ms1 u ($1*tscale1):($6/$4)			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   ms2 u ($1*tscale2):($6/$4)           	  w l lt 1 lc 2 title 'R7\_IMF2001', \
   ms3 u ($1*tscale3):($6/$4)           	  w l lt 1 lc 3 title 'R3\_IMF2001', \
   ms4 u ($1*tscale4):($6/$4)           	  w l lt 1 lc 4 title 'R7\_ROT'	, \

##--------------bbhnc/nc-------------
set output 'bbhnc_nc.eps'
set ylabel 'N_{bbh,c}/N_{c}'
plot [0:1000][] \
   mb1 u ($1*tscale1):($8/$4)			  w l lt 1 lc 1 title 'R7\_KTG93' , \
   mb2 u ($1*tscale2):($8/$4)			  w l lt 1 lc 2 title 'R7\_IMF2001', \
   mb3 u ($1*tscale3):($8/$4)			  w l lt 1 lc 3 title 'R3\_IMF2001', \
   mb4 u ($1*tscale4):($8/$4)			  w l lt 1 lc 4 title 'R7\_ROT'	, \

