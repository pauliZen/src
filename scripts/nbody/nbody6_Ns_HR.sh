date=110710
for i in 150 300 500 700 1000
do
    rm -r CHR_$i
    mkdir CHR_$i
    cd CHR_$i
    for j in 0.38 0.77 1.69 3.83 7.66
    do
	mkdir $date'_'$j
	cd $date'_'$j
	echo 'rm -f fort.*'>>input.sh
	echo 'rm -f ESC'>>input.sh
	echo 'rm -f OUT3'>>input.sh
	echo 'rm -f HIARCH'>>input.sh
	echo 'rm -f ENERGY.dat'>>input.sh
	echo 'rm -f OUT9'>>input.sh
	echo 'rm -f *.out'>>input.sh
	echo 'rm -f HIDAT'>>input.sh
	echo 'rm -f ROCHE'>>input.sh
	echo 'rm -f COAL'>>input.sh
	echo 'rm -f COLL'>>input.sh
	echo 'rm -f BINEV'>>input.sh
	echo 'rm -rf graph'>>input.sh
	echo 'mkdir graph'>>input.sh
	echo 'nbody6_new <<EOF'>>input.sh
	echo 1 10000.0'                                         # KSTART, TCOMP'>>input.sh
	echo $i 1 5 78449 145 1'                               # N, NFIX, NCRIT, NRAND, NNBMAX, NRUN'>>input.sh
	echo 0.02 0.03 $j 2.0 20 10000. 2.0D-04 0.5 -1234'     # ETAI, ETAR, RS0, DTADJ, DELTAT, TCRIT, QE, RBAR, ZMBAR'>>input.sh
	echo 1 3 1 0 1 0 1 4 0 0''>>input.sh
	echo 0 1 0 1 1 0 1 1 3 4''>>input.sh
	echo 1 0 2 0 0 2 0 0 0 1''>>input.sh
	echo 1 0 2 1 0 0 0 1 0 1''>>input.sh
	echo 0 0 0 0 0 0 0 0 0 0''>>input.sh
	echo 5E-06 1E-04 0.2 1.0 1.0E-06 0.001'                 # DTMIN, RMIN, ETAU, ECLOSE, GMIN, GMAX'>>input.sh
	echo 2.3 5.0 0.2 `calc / $i 5` 0 0.02 0.0 10.0'                   # ALPHAS, BODY1, BODYN, NBIN0, NHI0, ZMET, EPOCH0, DTPLOT'>>input.sh
	echo 0.5 0.0 0.0 0.0 1.0'                               # Q, VXROT, VZROT, RTIDE, SMAX'>>input.sh
	echo 0.009696 -1.0 1.0 999.0 0 0 0'                     # SEMI0, ECC0, RATIO, RANGE, NSKIP, IDORM, ICIRC'>>input.sh
	echo 1 `calc / $i 2` 1.0E-3 1.0 0.5 0 10.0 1.0'                   # USEPLANET, NPLANET, MPLANET, RPLANET, QPLANET, VDIST, VMU, VSIG'>>input.sh
	echo 'EOF'>>input.sh
	echo 'run' $date , 'Rs0' $j ",Nstar" $i
	./input.sh>>run.log
	echo 'end run'
	cd ..
    done
    cd ..
done

