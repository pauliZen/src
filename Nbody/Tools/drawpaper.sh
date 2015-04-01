#draw figures for FFplanet paper
draw_ce=0
drawn_nsnp=0
drawn_p=0
drawn_tf=0
drawn_vp=0
drawn_step3=0
drawn_count=0
drawn_fcount=1

figdir='/home/lwang/Dropbox/Datas/Planets/'
#2000_05_05_2v4_m1p1_(p/t/vinf/vp/vp_p).pdf-------------------------------#
#2000_05_0_2v4_m1p1_(p/t/vinf/vp/vp_p).pdf-------------------------------#
samplelist='2000_0.5_0.5_2v4 2000_0.5_0_2v4'
if [ $draw_ce = 1 ]; then
    for i in $samplelist
    do
	echo $i'_celist.root'>tmplist
	figname=$i'_m1p2'
	drawcelist tmplist $figdir $figname 0 1 1 1 1 0 1 0 0 'm1==1&&p1==2' sample_celist_vfit.root 100
    done
fi

#counter number dist------------------------------------------#
samplelist='2000_0.5_0.5_2v4 1000_0.5_0.5_2v4 2000_2_0.5_2v4 2000_0.5_0_2v4 2000_0.5_0.5_0.5v4'
if [ $drawn_count = 1 ]; then
    for i in $samplelist
    do
	echo $i'_celist.root'>tmplist
	figname=$i'_m1p2'
	drawcelist tmplist $figdir $figname 0 0 0 0 0 0 0 0 1 'm1==1&&p1==2' sample_celist_vfit.root 100
    done
    echo '2000_0.5_0.5_2v0_celist.root'>tmplist
    drawcelist tmplist $figdir '2000_0.5_0.5_2v0' 0 0 0 0 0 0 0 0 1 '1' sample_celist_vfit.root 100
fi
	

format='pdf'
figpath=/home/lwang/Dropbox/Datas/Planets/vfit/
drawlimit='chi2<100'
rline='rbar d 0.001 3 0.5 1.0 2.0'
#mp11_nsnp1000.pdf -> /Users/wanglong/Dropbox/Datas/Planets//vfit/m1+10*p1_11_scalensslope_offsetnp1000m.pdf
#rbar_05_nsm1p1.pdf
#rbar_05_nsnp1000.pdf
drawopt='0 0 0 0 0 0 1 0'
filelist=nsfit.lst
if [ $drawn_nsnp = 1 ]; then
    fignameprefix='np1000m'
    filename='vfit_t'$fignameprefix'.lst'
    echo 'np==1000' >$filename
    echo 'm1+10*p1 n 0 1 21' >>$filename
    echo $rline >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit

    fignameprefix='np1000'
    filename='vfit_'$fignameprefix'.lst'
    echo 'np==1000' >$filename
    echo 'rbar d 0.001 1 0.5' >>$filename
    echo 'm1+10*p1 n 0 4 0 11 12 22' >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit

    fignameprefix='m1p2'
    filenameprefix='npfit_'$fignameprefix
    filename=$filenameprefix'.lst'
    echo 'm1==1&&p1==2' >$filename
    echo 'rbar d 0.001 1 0.5' >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi


#vfit-----------------------------------------------------#
#np_1000_pslope_norm_rhoall.pdf 
#np_1000_vcut.pdf
#np_1000_vinfmax.pdf
#np_1000_vpmax.pdf
drawopt='0 1 0 0 1 1 0 0'
filelist=celist.lst
if [ $drawn_p = 1 ]; then
    fignameprefix='all'
    filenameprefix='vfit_t'$fignameprefix
    filename=$filenameprefix'.lst'
    echo '1' > $filename
    echo 'np n 0 1 1000' >>$filename
    echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
    echo 'm1+10*p1 n 0 5 0 11 12 21 22' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi


#vfit----------------------------------------------------#
#rbar_05_vpvcnp1000m1p1.pdf
drawopt='0 0 0 0 0 1 0 0'
drawlimit='chi2<1000'
filelist=celist.lst
if [ $drawn_vp = 1 ]; then
    fignameprefix='np1000m1p2'
    filenameprefix='vfit_t'$fignameprefix
    filename=$filenameprefix'.lst'
    echo 'np==1000&&m1==1&&p1==2' >$filename
    echo 'rbar d 0.001 1 0.5' >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    echo 'type n 0 15 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi

#vfit----------------------------------------------------#
#np_1000_tf_10all.pdf
#np_1000_tf_50all.pdf
#np_1000_tf_90all.pdf
drawlimit='ntot>30'
filelist=cemave.lst
drawopt='0 0 1 0 0 0 0 0'
if [ $drawn_tf = 1 ]; then
    fignameprefix='all'
    filenameprefix='vfit_t'$fignameprefix
    filename=$filenameprefix'.lst'
    echo '1' > $filename
    echo 'np n 0 1 1000' >>$filename
    echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
    echo 'm1+10*p1 n 0 4 0 11 12 22' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi

figpath='/home/lwang/Dropbox/Datas/Planets/step3_'$format'/'
#rbar_05_np1000.pdf
#rbar_10_np1000.pdf
#rbar_20_np1000.pdf
if [ $drawn_step3 = 1 ]; then
    fignameprefix='np1000'
    filename='step3_'$fignameprefix'.lst'
    echo 'np==1000' >$filename
    echo $rline >>$filename
    echo 'm1+10*p1 n 0 4 0 11 12 22' >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    drawstep3 'hnps' 'step3.lst' $figpath $fignameprefix'.'$format $filename 0
#    drawstep3 -l $figpath $fignameprefix'_r.'$format $filename 1
fi

#ecfrac.pdf
figpath='/home/lwang/Dropbox/Datas/Planets/counts/'
filelist=ceclst
drawopt='0 0 0 0 0 0 0 2'
drawlimit='1'
if [ $drawn_fcount = 1 ]; then
    fignameprefix='all'
    filenameprefix='vfit_t'$fignameprefix
    filename=$filenameprefix'.lst'
    echo '1' > $filename
    echo 'np n 0 1 1000' >>$filename
    echo 'type n 0 7 1 2 3 4 5 6 10' >>$filename
    echo 'm1+10*p1 n 0 4 0 11 12 22' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi

drawopt='0 0 0 0 0 0 0 2'
if [ $drawn_fcount = 2 ]; then
    fignameprefix=''
    filenameprefix='vfit_t'$fignameprefix
    filename=$filenameprefix'.lst'
    echo '1' > $filename
    echo 'np n 0 1 1000' >>$filename
    echo 'np n 0 1 1000' >>$filename
    echo 'm1+10*p1 n 0 4 0 11 12 22' >>$filename
    drawvfit $figpath $fignameprefix'.'$format $filelist $filename $drawopt $drawlimit
fi
