make
make cleanall

./energy_divide 1 10 1000 10000 
./energy_divide 2 10 1000 10000 

./findpeaks 10 1 300 1200 
./findpeaks 15 1 1200 2700 
./findpeaks 10 2 700 1500 
./findpeaks 8 2 1500 2700 

./resolutionf 2 10 300 1200 15 1200 2700 1
./resolutionf 2 10 700 1500 8 1500 2700 2

./energy_divide 1 10 1000 10000
./energy_divide 2 10 1000 10000

./plot_histograms 1 10 1000
./plot_histograms 2 10 1000

./seg_ab_tot_single 1 500 2400
./seg_ab_tot_single 2 700 2700