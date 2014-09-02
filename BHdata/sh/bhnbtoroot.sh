#bhnbtoroot-------------------------------------------------#
#function: transform all bh_nb.dat to dirname-nb.root-------#
#          in dirlist.lst. then mv *.root to root directory-#
#Notes!:   Should be used in root directory and dirlist.lst-#
#          exist(directory name and neighbor number list)   #
#          Should exist root directory----------------------#

if [ -e dirlist.lst ]; then
    for ((i=1;i<=`wc -l dirlist.lst|cut -d' ' -f1`;i=i+1))
    do
	dirname=`head -$i dirlist.lst|tail -1|cut -d' ' -f1`
	neigh=`head -$i dirlist.lst|tail -1|cut -d' ' -f2`
	cd $dirname
	bhnbdatatoroot bh_nb $dirname'-nb' $neigh
	mv $dirname'-nb.root' ../root/
	cd ..
    done
else
    echo 'No dirlist.lst'
fi
