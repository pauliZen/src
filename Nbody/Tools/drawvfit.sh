drawn_ns_nb=0    #fix np=1000 m1 p1, name rbar
drawn_mp_nsb=0   #fix np=1000, name rbar
drawn_nsb_t=0    #fix np=1000 m1 p1, name rbar
drawn_nsb_np=0   #fix m1 p2, name rbar
drawn_r_nsb=0    #fix np=1000, name m1p1
drawn_r_mp=0     #fix np=1000, name ns+nb
drawn_t_mp=1     #fix none, name np
drawn_t_mp1000=0 #fix none, name np=1000
drawn_t_np=0     #fix m1 p1, name np (if 1)
                 #fix nb0=0 m1 p1, name ns (if 2)

format='pdf'
figpath=/home/lwang/Dropbox/Datas/Planets/vfit/
figname=""
#tfit---------
#filelist=vfit.lst
#nsnpfit-------
#filelist=nsfit.lst
#(b/p)fit/(vinf/vp)fit----
filelist=celist.lst
#filelist=cemave.lst
rline='rbar d 0.001 3 0.5 1.0 2.0'
#drawopt: b, p, tm, t, vinf, vp, nsnp
drawopt='0 1 0 0 0 0 0'
drawlimit='chi2<100'
#drawlimit='ntot>30'

if [ $drawn_ns_nb = 1 ]; then
    for i in 1 2
    do
	for j in 1 2
	do
	    fignameprefix='np1000m'$i'p'$j
	    filenameprefix='vfit_'$fignameprefix
	    filename=$filenameprefix'.lst'
	    echo 'np==1000&&m1=='$i'&&p1=='$j >$filename
	    echo $rline >>$filename
	    echo 'ns n 0 3 500 1000 2000' >>$filename
	    echo 'nb n 0 6 0 100 250 200 500 400 1000' >>$filename
	    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
	done
    done
fi

if [ $drawn_mp_nsb = 1 ]; then
    fignameprefix='np1000'
    filename='vfit_'$fignameprefix'.lst'
    echo 'np==1000' >$filename
    echo $rline >>$filename
    echo 'm1+10*p1 n 0 4 11 12 21 22' >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi

if [ $drawn_r_nsb = 1 ]; then
    fignameprefix='np1000m'
    filename='vfit_t'$fignameprefix'.lst'
    echo 'np==1000' >$filename
    echo 'm1+10*p1 n 0 4 11 12 21 22' >>$filename
    echo $rline >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi

if [ $drawn_nsb_t = 1 ]; then
    for i in 1 2
    do
	for j in 1 2
	do
	    fignameprefix='np1000m'$i'p'$j
	    filenameprefix='vfit_t'$fignameprefix
	    filename=$filenameprefix'.lst'
	    echo 'np==1000&&m1=='$i'&&p1=='$j >$filename
	    echo $rline >>$filename
	    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
	    echo 'type n 0 15 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15' >>$filename
	    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
	done
    done
fi

if [ $drawn_t_mp = 1 ]; then
#    for i in 0 0.2 0.5
#    do
#	fignameprefix='nbvns'$i
        fignameprefix='all'
	filenameprefix='vfit_t'$fignameprefix
	filename=$filenameprefix'.lst'
#	echo 'nb/ns=='$i> $filename
	echo '1' > $filename
	echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
#    echo $rline >>$filename
#    echo '(ns+nb)/rbar**3 n 0 9 62 75 93 125 150 187 250 300 375 500 600 750 1000 1200 1500 2000 2400 3000 4000 4800 6000 ' >>$filename
	echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
	echo 'm1+10*p1 n 0 5 0 11 12 21 22' >>$filename
	drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
#    done
fi

if [ $drawn_t_np = 1 ]; then
    for i in 1 2
    do
	for j in 1 2
	do
	    fignameprefix='m'$i'p'$j
	filenameprefix='vfit_t'$fignameprefix
	filename=$filenameprefix'.lst'
	echo 'm1=='$i'&&p1=='$j >$filename
	echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
	echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
	echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
	drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
	done
    done
fi    

if [ $drawn_t_np = 2 ]; then
    for i in 1 2
    do
	for j in 1 2
	do
	    fignameprefix='nb0'$nn'm'$i'p'$j
	    filenameprefix='vfit_t'$fignameprefix
	    filename=$filenameprefix'.lst'
	    echo 'nb==0&&m1=='$i'&&p1=='$j >$filename
	    echo 'ns n 0 3 500 1000 2000' >>$filename
	    echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
	    echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
	    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
	done
    done
fi    

if [ $drawn_nsb_np = 1 ]; then
    for i in 1 2
    do
	for j in 1 2
	do
	    fignameprefix='m'$i'p'$j
	    filenameprefix='npfit_'$fignameprefix
	    filename=$filenameprefix'.lst'
	    echo 'm1=='$i'&&p1=='$j >$filename
	    echo $rline >>$filename
	    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
	    echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
	    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
	done
    done
fi

if [ $drawn_r_mp = 1 ]; then
    fignameprefix='np1000'
    filenameprefix='mrfit_'$fignameprefix
    filename=$filenameprefix'.lst'
    echo 'np==1000' >$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    echo $rline >>$filename
    echo 'm1+10*p1 n 0 5 0 11 12 21 22' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi

if [ $drawn_t_mp1000 = 1 ]; then
    fignameprefix='all'
    filenameprefix='vfit_t'$fignameprefix
    filename=$filenameprefix'.lst'
    echo '1' > $filename
    echo 'np n 0 1 1000' >>$filename
    echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
    echo 'm1+10*p1 n 0 5 0 11 12 21 22' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi
