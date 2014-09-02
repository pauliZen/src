split_num=6

ls |egrep [0-9\.]_[0-9\,]+_[0-9\.]>filelist
flnum=`wc -l filelist|cut -d' ' -f1`
pernum=`expr $flnum / $split_num + 1`

split -l $pernum filelist -d -a 1 list"."

for ((i=0;i<$split_num;i=i+1))
do
    trans_hfm list"."$i 1>>trans_hfm_$i.log 2>>trans_hfm_$i.log&
done
