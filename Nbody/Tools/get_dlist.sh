read -p 'Time scaling (1.0):' tscale
[[ -z $tscale ]] && tscale=1.0

ls data_*|sed -n '/data_[0-9]\+.[0-9]\+$/ p'|cut -d'_' -f2|sort -n|awk -v tscale=$tscale '{printf "data_%s %d\n",$1,$1*tscale+0.5}' >dlist
