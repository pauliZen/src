#startorootsplit-----------------------------------------#
#function: transform all large [0-9]*.dat to stardata.root
#          by stardatatoroot in this directory. The root #
#          file will be splited by 120 stars' data file  #
#Notes: should be used in the data directory. all root   #
#       file will be putted in the same directory        #

ls [0-9]*.dat>stardat.lst
split -l 120 stardat.lst -d -a 4
ls x[0-9][0-9][0-9][0-9] >splstardat.lst
dirname=`pwd -P|cut -d'/' -f4`
for ((j=1;j<=`wc -l splstardat.lst|cut -d' ' -f1`;j=j+1))
do
    nowlist=`head -$j splstardat.lst|tail -1`
    filename=`head -1 $nowlist|tail -1|cut -d'.' -f1`
    stardatatoroot $filename $dirname'-star-'$j create
    echo "create stardata"$j".root"
    for ((i=2;i<=`wc -l $nowlist|cut -d' ' -f1`;i=i+1))
    do
	filename=`head -$i $nowlist|tail -1|cut -d'.' -f1`
	stardatatoroot $filename $dirname'-star-'$j
	echo "update stardata"$j".root to "$filename
    done
done
rm x[0-9][0-9][0-9][0-9]
rm splstardat.lst
