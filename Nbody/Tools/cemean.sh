#get cemean.root for v4----------------------------------#
#Need v4list for all pars without '_'--------------------#
#Need v4celist for all celist----------------------------#

[ -e v4list ] || return
[ -e v4celist ] || return


for i in 500 1000 2000
do
    egrep ^$i v4list >v4list_$i
    egrep ^$i v4celist >v4celist_$i
    cemean v4celist_$i v4cemean_$i.root v4list_$i 1
done
