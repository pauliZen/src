#startoroot for extra------------------------------------#
#function: transform all large [0-9]*.dat.extra to root  #
#          by stardatatoroot. file will be store in root #
#          directory.                                    #
#Notes: should be used in root directory                 #
#       file will be putted in the same directory        #

rootdir="/data/lwang/BHdata/nonrot/"
ls $rootdir|egrep run>dirlist.lst

if [ -e dirlist.lst ]; then
    tnum=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$tnum;i=i+1))
    do
	nowdir=`head -$i dirlist.lst|tail -1`
	if [ -e $rootdir$nowdir ];then
	    ls $rootdir$nowdir$'/'[0-9]*.dat.extra>stardat.lst
	    filename=`head -1 stardat.lst|tail -1|cut -d'.' -f1`
	    datafilename=`head -1 stardat.lst|tail -1|cut -d'.' -f1|sed s:$rootdir$nowdir$"/"::g`
	    stardatatoroot $filename './'$nowdir'-star-extra' create "P"$datafilename
#	    echo "create "$filename'-star-extra.root'
	    for ((j=2;j<=`wc -l stardat.lst|cut -d' ' -f1`;j=j+1))
	    do
		filename=`head -$j stardat.lst|tail -1|cut -d'.' -f1`
		datafilename=`head -$j stardat.lst|tail -1|cut -d'.' -f1|sed s:$rootdir$nowdir$"/"::g`
		stardatatoroot $filename './'$nowdir'-star-extra' update "P"$datafilename
#		echo "update "$nowdir'-star-extra.root '$j".root to "$filename
	    done
	else
	    echo "no such directory: "$rootdir$nowdir
	fi
    done
else
    echo 'no dirlist.lst'
fi
rm -f stardat.lst
