list='unpert touch peri tides3 fnuc fhalo fdisk xtrnlf xtrnlv nbpot tides2 chaos kstide kspred xcpred fchain kspert ksmod kslist kscorr zare tstab permit induce histab edot ecirc decide impact fpert flyby qtides physks ksphys hirect rkint himod higrow giant3 hicirc eccmod trflow star mrenv hrdiag trdot tcirc ksrect ksperi hut expand tpert xtrnlp stumpf resolv kspoly deform spiral kick ksapo matrix ksres2 giant chaos0 findj binev chrect inclin assess ksint'

checklist='NTOT NPAIRS NTTOT N NNBMAX NCRIT NFIX NMERGE NSUB IPHASE IFIRST ICOMP JCOMP ICLOSE JCLOSE JCMAX KSPAIR NRUN MODEL NC NZERO NBZERO NBIN0 NHI0 NAME0 NCH NCHAOS IDUM1 NNBOPT ETAI ETAR DTADJ DELTAT TCRIT QE RBAR ZMBAR DTMIN RMIN ETAU CMSEP2 ECLOSE GMIN GMAX ETA0 TWOPI ONE3 ONE6 ONE9 ONE12 TCR0 TRH BODYM BODY1 SMIN RMIN2 RMIN22 STEPJ ALPHA ZNBMIN ZNBMAX EBH TIME TADJ TNEXT CPU CPU0 CPUTOT ZMASS RSCALE TCR TRC ZKIN POT EBIN EBIN0 ESUB EMERGE ECOLL EDISS ESYNC ERROR ERRTOT DETOT ETCORR AZ PCRIT EBCH0 RTIDE TSCALE HT ETIDE EGRAV RSFAC RSPH2 RC RC2 RC2IN VC ZMC  RHOD RHOM RSMIN RMAX DMIN1 DMIN2 DMIN3 DMIN4 DMINC SBCOLL BBCOLL CHCOLL DELTAS TLASTT TLASTS TDUMP TOFF TTOT EBESC EMESC ESESC CLIGHT RZ TINY SMAX WTOT WTOT0 TCRITp NSTEPI NSTEPR NSTEPU NNPRED NBCORR NBFULL NBVOID NNTB NBSMIN NLSMIN NBDIS NBDIS2 NCMDER NBDER NFAST NBFAST NBLOCK NBPRED NICONV NCHAIN NSTEPC NKSTRY NKSREG NKSHYP NKSPER NPRECT NEWKS NKSMOD NTTRY NTRIP NQUAD NMERG NSTEPT NSTEPQ NDISS NTIDE NCOLL NSYNC NSESC NBESC NMESC NTIMER NSTEPS NPRINT NDUMP NBPREV NEWHI NSTEPB NBFLUX NMTRY NWARN NIRECT NURECT NBRECT NRRECT KSMAG NBLCKR NIRRF MP AP2 VIR MP0 MPDOT TDELAY RTIDE0 QVIR TPREV TBLOCK EPOCH0 ZMRG ZMHE ZMRS ZMWD ZMSN ZMNH ZMBH ZMDOT AU PC GM DAYS YRS SU SMU RAU TSTAR VSTAR STEPX TMDOT TPHYS TURN EMDOT ECDOT EKICK TPLOT DTPLOT XHYD YHEL ZMET SPNFAC IQCOLL NAS NBH NBKICK NBR NBRK NBS NCHA NCIRC NCOAL NCONT NDD NEMOD NGB NGLOB NGLOB0 NHE NHG NHI NHYP NKICK NMDOT NMS NNH NRG NRO NROCHE NRS NRSAVE NSHOCK NSLP NSN NSP NSPIR INSTAB NTZ NWD NCE NHYPC NBH0  NEINT IBLUE'

checklist1='KZ NEW2 BE CMR CMRDOT E TIDAL RDENS ORBITS GPRINT TLASTB SCOEFF NDUM NPOP DTK KVEC PLDUM ITYPE KSAVE NGDUM LISTR LISTD LISTV BODY RS STEP T0 STEPR T0R TIMENW RADIUS TEV TEV0 BODY0 EPOCH SPIN XSTAR ZLMSTY KSTAR ZPARS'

checklist2='X X0 X0DOT F XN XNDOT FDOT XDOT FI D1 D2 D3 FR D1R D2R D3R FIDOT D0 FRDOT D0R KTYPE'

for k in $list
do
# check whether file exist
    c=`ls *.f |egrep -c $k`
    if [ $c -gt 0 ] ;then
	i=$k.f
    else
	c=`ls *.F |egrep -c $k`
	if [ $c -gt 0 ] ;then
	    i=$k.F
	else
	    echo $i
	fi
    fi

# checklist
    for j in $checklist
    do 
	egrep -Hin "\<$j\ *=" $i|egrep -v "\w+\.[fF]:[0-9]+:[\*cC]"
#	egrep -Hin "^[\ 0-9]+call\ +\([a-z0-9_\+\-\*\/\(\)\,]*\<$j\>[a-z0-9_\+\-\*\/\(\)\,]*\)"
    done

# checklist1
    for j in $checklist1
    do 
	egrep -Hin "\<$j\([A-Za-z0-9_\+\-\*\/\ ]+\)\ *=" $i|egrep -v "\w+\.[fF]:[0-9]+:[\*cC]"
#	egrep -Hin "^[\ 0-9]+call\ +\([a-z0-9_\+\-\*\/\(\)\,]*\<$j\>[a-z0-9_\+\-\*\/\(\)\,]*\)"
    done

# checklist2    
    for j in $checklist2
    do 
	egrep -Hin "\<$j\([A-Za-z0-9_\+\-\*\/\ ]+,[A-Za-z0-9_\+\-\*\/\ ]+\)\ *=" $i|egrep -v "\w+\.[fF]:[0-9]+:[\*cC]"
#	egrep -Hin "^\ +call\ +\([a-z0-9_\+\-\*\/\(\)\,]*\<$j\>[a-z0-9_\+\-\*\/\(\)\,]*\)"
    done
done
