totalenergychange run-020-020-1mil P0000 P0010 E010to000 "Energy&L_data_of_P0010_and_P0000"
for ((i=20;i<100;i=i+10))
do
    j=`calc - $i 10`
    echo $i' to '$j
    totalenergychange run-020-020-1mil P00$j P00$i E0$i"to0"$j "Energy&L_data_of_P00"$j"_and_P00"$i
done
for ((i=100;i<160;i=i+10))
do
    j=`calc - $i 10`
    echo $i' to '$j
    totalenergychange run-020-020-1mil P0$j P0$i E$i"to"$j "Energy&L_data_of_P0"$j"_and_P0"$i
done
