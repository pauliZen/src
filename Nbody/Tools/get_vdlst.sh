read -p 'Magnitude cut (24.0):' m
read -p 'Filter (V):' filter
[[ -z $filter ]] && filter='V'
[[ -z $m ]] && m='24.0'
ls vdf_${filter}_m$m*|cut -d'_' -f4|sort -n|awk -v f=$filter -v m=$m '{print "vdf_"f"_m"m"_"$1,$1}' >vdlst
