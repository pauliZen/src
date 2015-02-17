#set term gif size 900,900 font ',22'
set term pngcairo enhanced color dashed size 1200,1000 font ',22'

suffix='png'

set macro

cplot="plot [0:100][] for [i=@range] word(tlst,i) u 1:@ncol:(ftime(i)) w l t '' lt 1 lc pal z, \
               word(tlst,1) u 1:@ncol w l t '0 Myr' lt 2 lc 0 lw 4.0"

tlst=system("cat rdist.lst|cut -d ' ' -f1")
tt=system("cat rdist.lst|cut -d ' ' -f2")

tscale = 0.5506

range = "2:25"
set colorbox
set cbrange [0.5:2500]
set logscale zcb

ftime(i) = 1000.0**((i-2.0)/20.0)*tscale

set xlabel 'r [pc]'
set cblabel 'T [Myr]'

#-------------------------------------------------------
set output 'rdist_nmsl.'.suffix
set ylabel 'Cumulative number of main sequences (0.08-0.4 M_{sun})'
ncol = "2"
@cplot

#-------------------------------------------------------
set output 'rdist_msl.'.suffix
set ylabel 'Cumulative mass of main sequences (0.08-0.4 M_{sun})'
ncol = "3"
@cplot

#-------------------------------------------------------
set output 'rdist_nmsm.'.suffix
set ylabel 'Cumulative number of main sequences (0.4-0.7 M_{sun})'
ncol = "4"
@cplot

#-------------------------------------------------------
set output 'rdist_msm.'.suffix
set ylabel 'Cumulative mass of main sequences (0.4-0.7 M_{sun})'
ncol = "5"
@cplot

#-------------------------------------------------------
set output 'rdist_nmsh.'.suffix
set ylabel 'Cumulative number of main sequences (0.7-100 M_{sun})'
ncol = "6"
@cplot

#-------------------------------------------------------
set output 'rdist_msh.'.suffix
set ylabel 'Cumulative mass of main sequences (0.7-100 M_{sun})'
ncol = "7"
@cplot

#-------------------------------------------------------
set output 'rdist_nrg.'.suffix
set ylabel 'Cumulative number of red giant'
ncol = "8"
@cplot

#-------------------------------------------------------
set output 'rdist_rg.'.suffix
set ylabel 'Cumulative mass of red giant'
ncol = "9"
@cplot
	       
#-------------------------------------------------------
set output 'rdist_nrgb.'.suffix
set ylabel 'Cumulative number of RGB'
ncol = "14"
@cplot

#-------------------------------------------------------
set output 'rdist_rgb.'.suffix
set ylabel 'Cumulative mass of RGB'
ncol = "15"
@cplot

#-------------------------------------------------------
set output 'rdist_nwd.'.suffix
set ylabel 'Cumulative number of WD'
ncol = "16"
@cplot

#-------------------------------------------------------
set output 'rdist_wd.'.suffix
set ylabel 'Cumulative mass of WD'
ncol = "17"
@cplot

#-------------------------------------------------------
set output 'rdist_nns.'.suffix
set ylabel 'Cumulative number of NS'
ncol = "18"
@cplot

#-------------------------------------------------------
set output 'rdist_ns.'.suffix
set ylabel 'Cumulative mass of NS'
ncol = "19"
@cplot

#-------------------------------------------------------
set output 'rdist_nbh.'.suffix
set ylabel 'Cumulative number of BH'
ncol = "20"
@cplot

#-------------------------------------------------------
set output 'rdist_bh.'.suffix
set ylabel 'Cumulative mass of BH'
ncol = "21"
@cplot
