#draw all figures for run-020-020-1mil #
figdir=/home/lwang/Dropbox/Datas/BHdata/figures/
name='run-020-020-1mil'
if [[ -e 'run-020-020-1mil-select-star.index' ]]&&[[ -e 'run-020-020-1mil-dat.lst'  ]];then
    echo $name $figdir$name'/' "SdEvsEsGT12_"  "DdEvsEsGT12" "dEvsT_all" "EvsT_all" "Lchange" "Ldist" "LcumvsT" '7' '0.02' '0.02' "E150to100"
    drawdEgraph $name $figdir$name'/' "SdEvsEsGT12_"  "DdEvsEsGT12" "dEvsT_all" "EvsT_all" "Lchange" "Ldist" "LcumvsT" '7' '0.02' '0.02' "E150to100"
else
    echo 'no file'
fi
