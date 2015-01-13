egrep -i 'Warning: Citation' warning |cut -d'`' -f2|cut -d"'" -f1 |sort|uniq>list

cp reference.bk.tex ref.tex

[ -e rtmp.tex ] && rm -i rtmp.tex

lst=`cat list`
for i in $lst
do
    sed -n "/$i/ p" reference.bk.tex >>rtmp.tex
    echo '' >>rtmp.tex
    sed -i "/$i/ d" ref.tex 
done
