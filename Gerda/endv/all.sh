make
make cleanall
num=2
#./energy_divide 1 10 1000 `expr 10000 \* $num`
./energy_divide 2 10 1000 `expr 10000 \* $num`

#./findpeaks 10 1 `expr 300 \* $num` `expr 1200 \* $num`
#./findpeaks 15 1 `expr 1200 \* $num` `expr 2700 \* $num`
./findpeaks 10 2 `expr 700 \* $num` `expr 1500 \* $num`
./findpeaks 8 2 `expr 1500 \* $num` `expr 2700 \* $num`

#./resolutionf 2 10 `expr 300 \* $num` `expr 1200 \* $num` 15 `expr 1200 \* $num` `expr 2700 \* $num` 1
./resolutionf 2 10 `expr 700 \* $num` `expr 1500 \* $num` 8 `expr 1500 \* $num` `expr 2700 \* $num` 2

#./energy_divide 1 10 1000 10000
#./energy_divide 2 10 1000 10000

#./plot_histograms 1 10 1000
#./plot_histograms 2 10 1000

#./seg_ab_tot_single 1 300 2700
#./seg_ab_tot_single 2 700 2700