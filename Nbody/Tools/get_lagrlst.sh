tlst='0 50 100 1000 2000 4000 6000'

rm -f lagr.lst

for i in $tlst
do
    awk -v t=$i '{if (NR>2&&($1-t)**2<1E-4) {for (i=2;i<NF;i=i+8) { for (j=i;j<i+8;j++) {printf "%s ",$j}; printf "\n"}}}' lagr.snap >lagr.$i
    echo "lagr.$i" >> lagr.lst
done
