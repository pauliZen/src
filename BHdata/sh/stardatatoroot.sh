#startoroot----------------------------------------------#
#function: transform all [0-9]*.dat.extra to stardata.root
#          by stardatatoroot in this directory           #
#New root name: stardata.root----------------------------#

#gunzip *.dat.gz

ls [0-9]*.dat.extra>stardat.lst
filename=`head -1 stardat.lst|tail -1|cut -d'.' -f1`
stardatatoroot $filename stardata create
echo "create stardata.root"
for ((i=2;i<=`wc -l stardat.lst|cut -d' ' -f1`;i=i+1))
do
    filename=`head -$i stardat.lst|tail -1|cut -d'.' -f1`
    stardatatoroot $filename stardata
    echo "update stardata.root to "$filename
done
