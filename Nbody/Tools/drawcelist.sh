drawv0=1
drawv4=1
drawv42000=0
drawsample=0
drawselect='0 0 0 0 0 0 0 0 1'
fitrootname='new2_'

figdir='/home/lwang/Dropbox/Datas/Planets/'

if [ $drawv0 = 1 ]; then
    ls *v0_celist.root>celist_v0.lst
    v0list=`cat celist_v0.lst`

    for i in $v0list
    do
	figname=`echo $i|cut -d'_' -f1-4`
	echo $i >tmplist
	ns=`echo $i|cut -d'_' -f1`
	[ $ns == 2000 ] && drawcelist tmplist $figdir $figname $drawselect 1 $fitrootname'_v0fit.root' 100
	[ $ns == 1000 ] && drawcelist tmplist $figdir $figname $drawselect 1 $fitrootname'_v0fit.root' 100
	[ $ns == 500 ] && drawcelist tmplist $figdir $figname $drawselect 1 $fitrootname'_v0fit.root' 100
	rm -f tmplist
    done
fi

if [ $drawv4 = 1 ]; then
    ls *v4_celist.root>celist_v4.lst
    v4list=`cat celist_v4.lst`

    for i in $v4list
    do
	fignameprefix=`echo $i|cut -d'_' -f1-4`
	for m in 1 2
	do
	    for p in 1 2
	    do
		echo $i >tmplist
		figname=$fignameprefix'_m'$m'p'$p
		ns=`echo $i|cut -d'_' -f1`
		[ $ns == 2000 ] && drawcelist tmplist $figdir $figname $drawselect 'm1=='$m'&&p1=='$p $fitrootname'_v4fit.root' 100
		[ $ns == 1000 ] && drawcelist tmplist $figdir $figname $drawselect 'm1=='$m'&&p1=='$p $fitrootname'_v4fit.root' 100
		[ $ns == 500 ] && drawcelist tmplist $figdir $figname $drawselect 'm1=='$m'&&p1=='$p $fitrootname'_v4fit.root' 100
		rm -f tmplist
	    done
	done
    done
fi

if [ $drawv42000 = 1 ]; then
    ls 2000_2*v4_celist.root>celist_v4.lst
    v4list=`cat celist_v4.lst`

    for i in $v4list
    do
	fignameprefix=`echo $i|cut -d'_' -f1-4`
	for m in 1 2
	do
	    for p in 1 2
	    do
		echo $i >tmplist
		figname=$fignameprefix'_m'$m'p'$p
		drawcelist tmplist $figdir $figname 1 1 1 1 1 1 'm1=='$m'&&p1=='$p celist_v4fit.root 10
		rm -f tmplist
	    done
	done
    done
fi

if [ $drawsample = 1 ]; then
    samplelist='1000_0.5_0.5_2v4 2000_0.5_0.5_2v4 2000_0.5_0.5_1v4 2000_0.5_0_2v4 2000_1_0.5_2v4'
    for i in $samplelist
    do
	echo $i'_celist.root'>tmplist
	figname=$i'_m1p1'
	drawcelist tmplist $figdir $figname 0 0 0 0 0 0 0 0 1 'm1==1&&p1==1' sample_celist_vfit.root 100
    done
    echo '2000_0.5_0.5_2v4_celist.root'>tmplist
    drawcelist tmplist $figdir '2000_0.5_0.5_2v4_m1p2' 0 0 0 0 0 0 0 0 1 'm1==1&&p1==2' sample_celist_vfit_test.root 100
fi
