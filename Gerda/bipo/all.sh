make
make cleanall

./create_histograms 1 1
./create_histograms 1 2
./create_histograms 2 1
./create_histograms 2 2

./plot_histograms 1 1
./plot_histograms 1 2
./plot_histograms 2 1
./plot_histograms 2 2

ls $gerda/data/histograms/
ls $gerda/data/plots/bi214/sii
ls $gerda/data/plots/bi214/siii
ls $gerda/data/plots/bi212/sii
ls $gerda/data/plots/bi212/siii
ls $gerda/data/table/bi214/sii
ls $gerda/data/table/bi214/siii
ls $gerda/data/table/bi212/sii
ls $gerda/data/table/bi212/siii
