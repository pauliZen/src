#Draw delta vs. alpha for star and bh contour------------#
#Need drawlist.lst, [dirname]-result.root----------------#
#Need run drawall for generating langle tree before------#
#Need run in root directory to store root file-----------#
#Save name: Alpha_delta_i/o.eps--------------------------#

drawdir=/home/lwang/Dropbox/Datas/BHdata/figures/

if [ -e drawlist.lst ]; then
    for ((i=1; i<=`wc -l drawlist.lst|cut -d' ' -f1`;i=i+1))
    do
	line=`head -$i drawlist.lst|tail -1`
	idir=`echo $line|cut -d' ' -f1`
	ibh1=`echo $line|cut -d' ' -f2`
	ibh2=`echo $line|cut -d' ' -f3`
	rinf=`echo $line|cut -d' ' -f4`
	drawangle $idir"-result.root" $ibh1 $ibh2 $rinf $drawdir$idir/ langle 0 0 0 0 1 0 0 0
    done
else
    echo 'No drawlist.lst'
fi
