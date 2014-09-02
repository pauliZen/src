# compare the files BH1 and BH2 neighbor file------------#

echo "header of compared files '*'-BH(1/2)nb.recheck, input *. new file will be *-bh_nb.recheck"
read nameo
if [ -e $nameo-BH1nb.recheck ]; then
    cat $nameo-BH1nb.recheck >$nameo-bh_nb.recheck
    diff $nameo-BH1nb.recheck $nameo-BH2nb.recheck |egrep '>'|cut -d' ' -f2 >>$nameo-bh_nb.recheck
else
    echo "No such file"
fi
