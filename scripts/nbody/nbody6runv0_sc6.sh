########-This script is written by Long Wang---------------------#
########-Version: 1.0--------------------------------------------#
###-Based on bash, calc(calculator developed by Long Wang)-------#
###-Make sure following shell commands can be used normally------#
###---rm, mv, mkdir, cd, ps, kill, date, sleep, jobs-------------#
###---echo, cut, egrep, cat, head, tail, sed --------------------#
###-Mark '# C' means this part can be changed--------------------#

###-Change-List--------------------------------------------------#
#1.Variable parameters-----------------------------------#
#2.Winput parameters and the order!!---------------------#
#3.Main function for loop -------------------------------#
#4.Curdir name-------------------------------------------#
#5.Name reference----------------------------------------#
#6.for loop done number----------------------------------#

#-Basic define-------------------------------------------# C
User=lwang                              #Username of computer users 
SRunNum=5                                  #run numbers together
Appname=nbody6p                           #program name
Stoptime=5                                #simulation max no response time(m)
sleeptime=10                              #only basic coefficient, time=sleeptime*N/100
#rand=7833                                  #rand initial seed 

#-Variable parameters define-----------------------------# C
#tcrit='10000.0 100000.0 1000000.0'
Nstar='500 1000 2000'               #Number of starn 1 i
#Rbar='0.466 1.112 2.117 4.997 9.057'        #Initial Radius 2 j
Rbar='0.5 1 2'        #Initial Radius 2 j
RatioNb='0 0.2 0.5'                            #Nbinary/Nstars r
RatioNpNs='0.5 1 2'                      #N_planets/stars s
#vdist='4'                                #vdist  0: normal, 4: eject l
#M1='1 2'                                   #Choose 1Ms or 0.6Ms
#P1='1 2'                                   #Choose delay or prompt
rand='3003 11611 56339 8387 323426 23435 835654 34352 362348 754230'                     #change random seed 5 m
#rand='303 11611 56339'
#Rmin='0.0001 0.001 0.01 0.1'
#Semi0='0.009696 0.001 0.03'

#-ratio for some parameters------------------------------# C
#RatioNpNs=1

#-Input parameters function------------------------------# C
###-Don't forget to change the order!!!------------------#
function winput()
{
    rmin0=`calc /p 2 $2 $1`
    echo 1 10000.0'                                         # KSTART, TCOMP'>input
    echo $1 1 20 $5 45 1'                               # N, NFIX, NCRIT, NRAND, NNBMAX, NRUN'>>input
    echo 0.01 0.01 0.3 2.0 `calc /p 1 $1 50 $2` 10000.0 2.0D-04 $2 -1'     # ETAI, ETAR, RS0, DTADJ, DELTAT, TCRIT, QE, RBAR, ZMBAR'>>input
    echo 1 2 1 0 1 0 1 4 0 0''>>input
    echo 0 1 0 1 1 0 1 1 3 4''>>input
    echo 1 0 2 0 0 2 0 0 0 1''>>input
    echo 1 0 2 1 0 0 0 1 0 1''>>input
    echo 0 0 0 0 0 0 0 0 0 0''>>input
    echo `calc \*\*p 2 $rmin0 1.5` $rmin0 0.1 1.0 1.0E-06 0.001'                 # DTMIN, RMIN, ETAU, ECLOSE, GMIN, GMAX'>>input
    echo 2.3 5.0 0.2 `calc \* $1 $3` 0 0.02 0.0 10.0'       # ALPHAS, BODY1, BODYN, NBIN0, NHI0, ZMET, EPOCH0, DTPLOT'>>input
    echo 0.5 0.0 0.0 0.0 1.0'                               # Q, VXROT, VZROT, RTIDE, SMAX'>>input
    echo 0.009696 -1.0 1.0 999.0 0 0 0'                     # SEMI0, ECC0, RATIO, RANGE, NSKIP, IDORM, ICIRC'>>input
    echo 1 `calc \* $1 $4` 0.001 1.0 0.5 0 10 0.1 1 1'                   # USEPLANET, NPLANET, MPLANET, RPLANET, QPLANET, VDIST, VMU, VSIG, M1, VPAR2'>>input
}

#-save input information to Info.txt---------------------#
echo '*=Variable parameters====================================*'>Info.txt
###-Synchronize with the above parameters----------------# C
#echo 'Total time: '$tcrit>>Info.txt
echo 'Number of stars: '$Nstar>>Info.txt
echo 'Initial Radius: '$Rbar>>Info.txt
echo 'Binary fraction: '$RatioNb>>Info.txt
echo 'Nplanets/Nstars ratio: '$RatioNpNs>>Info.txt
#echo 'Choose for vdist pars: '$vdist>>Info.txt
#echo 'Choose ejected planet host star mass: '$M1>>Info.txt
#echo 'Choose ejected planet phase (prompt/delayed): '$P1>>Info.txt
#echo 'Rmin: '$Rmin>>Info.txt
#echo 'Semi0: '$Semi0>>Info.txt
echo 'Random seed: '$rand>>Info.txt
###-Print the above information to screen----------------#
cat Info.txt
#-save directories name reference to Info.txt------------# 
echo '*=Output files directories name reference================*'>>Info.txt
echo '** Nstars_Rbar_RatioNb_RatioNpNs_NRAND'>>Info.txt   # C
#-!!Important: rand must be the last part in the name of directory----#

#-functions----------------------------------------------#
###-check and wait for running processes-----------------#
###-The maximum number of processes is 'SRunNum'---------#
###-The maximun time for one process is 'Stoptime'-------#

###-start new running function---------------------------#
function runprocess() #In: Appname; Outfile: joblist, run.log
{
    rundate=`date +%D`
    runtime=`date +%T`
    $Appname <input>run.log&
    runpid=`jobs -l|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    echo $runpid':'$1 >>../joblist
    echo 'Successful run at '`date`
}
function timecompare() #In: t1, t2 (t1>t2,unit:hh:mm); Print: t1-t2
{
    hour1=`echo $1|cut -d':' -f1`
    min1=`echo $1|cut -d':' -f2`
    hour2=`echo $2|cut -d':' -f1`
    min2=`echo $2|cut -d':' -f2`
    ttime1=`calc \* $hour1 60`
    ttime1=`calc + $ttime1 $min1`
    ttime2=`calc \* $hour2 60`
    ttime2=`calc + $ttime2 $min2`
    echo `calc - $ttime1 $ttime2`
}
function waitrun() #Infile: joblist; In: SRunNum, Stoptime, Appname; Outfile: joblist, Info.txt, nownstar; Out: crashnum; Call winput, timecompare
{
    while [ -e joblist ]
    do
	echo 'Running check'
	echo `cat joblist|wc -l`' running now'
	rm -f jobtmp
	if [ `cat joblist|wc -l` -ge 1 ]; then
	    for ((wi=1;wi<=`cat joblist|wc -l`;wi=wi+1))
	    do
		thisid=`head -$wi joblist|tail -1|cut -d':' -f1`
		thisname=`head -$wi joblist|tail -1|cut -d':' -f2`
		if [ `ps -p $thisid|wc -l` = 1 ]; then
		    echo $thisid' '$thisname' finished'
		else
		    cd $thisname
		    if [ -e run.log ]; then
			if [ `tail -1 run.log|egrep -c 'END RUN'` = 1 ];then
			    echo $thisid' '$thisname' end run'
			    cd ..
			else
			    runlogtime=`ls -l|egrep 'run.log'|sed 's/\([a-zA-Z]\+\) \+\(\w\+\) \([0-9]\+:[0-9]\+\)/|\1-\2-\3|/'|cut -d'|' -f2`
#			    runlogtime=`ls -l|egrep 'run.log$'|sed 's/\(\w\+-\w\+-\w\+\) \([0-9]\+:[0-9]\+\)/|\1-\2|/'|cut -d'|' -f2`
			    runlogday=`echo $runlogtime|cut -d'-' -f2`
			    runtottime=`echo $runlogtime|cut -d'-' -f3`
			    righttime=`date +%R`
			    if [ `date +%d` -ne $runlogday ]; then
				righttimeh=`date +%H`
				righttimem=`date +%M`
				righttimeh=`calc + $righttimeh 24`
				righttime=`echo $righttimeh':'$righttimem`
			    fi
			    deltat=`timecompare $righttime $runtottime`
			    echo $thisid' '$thisname' running. run response time difference: '$deltat'='$righttime'-'$runtottime
			    if [ $deltat -gt $Stoptime ]; then
				kill $thisid
				echo $thisid' '$thisname' no response, kill it'
				cd ..
				mv $thisname crash/
				crashnum=`calc + $crashnum 1`
			    else
				cd ..
				echo $thisid':'$thisname >>jobtmp
			    fi
			fi
		    else
			echo '!!!'$thisid' '$thisname'Error run, no run.log, restart it'
			winput `echo $thisname|sed 's/_/ /g'`
			rundate=`date +%D`
			runtime=`date +%T`
			$Appname <input>run.log&
			runpid=`jobs -l|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
			echo $runpid':'$thisname >>../jobtmp
			cd ..
			if [ `egrep -c $curdir Info.txt` = 0 ]; then
			    echo '** Newrun  '$curdir' '$rundate' '$runtime>>Info.txt
			fi
		    fi
		fi
	    done
	    rm -f joblist
	    if [ -e jobtmp ]; then
		cat jobtmp>joblist
		rm -f jobtmp
	    fi
	fi
	if [ -e joblist ]; then
	    if [ `cat joblist|wc -l` -ge $SRunNum ]; then
		echo '-------------now running:-------------'
		cat joblist
		echo '--------------------------------------'
		echo 'running number reach maximum, wait for '`calc \*n $sleeptime $nownstar`
		sleep `calc \*n $sleeptime $nownstar`
	    else
		echo '-------------now running:-------------'
		cat joblist
		echo '--------------------------------------'
		break
	    fi
	else
	    echo 'No running, continue...'
	    break
	fi
    done
}

function crashcheck() #In: randnew, curdir, crashlist; Out: randnew, curdir; Outfile: Info.txt
{
    while [ `egrep -c $curdir crashlist` -ge 1 ]
    do
	echo $curdir' is crash condition, ignore'
	if [ `egrep $curdir Info.txt|egrep -c Crash` = 0 ]; then
	    echo '*** Crash  '$curdir>>Info.txt
	    if [ -e $curdir ]; then
		cd $curdir
		if [ -e run.log ]; then
		    tail -1 run.log>>../Info.txt
		else
		    echo 'no run.log file'>>../Info.txt
		fi
		cd ..
	    else
		if [ -d crash ]; then
		    cd crash
		    if [ -d $curdir ];then
			cd $curdir
			if [ -e run.log ]; then
			    tail -1 run.log>>../../Info.txt
			else
			    echo 'no run.log file'>>../../Info.txt
			fi
			cd ..
		    fi
		    cd ..
		fi
	    fi
	fi
	randnew=`calc + $randnew 1000`
	curdir=`echo $curdir|sed "s/[0-9]\+$/$randnew/"`
    done
}

#-Old run check version (low efficiency)-----------------#
    # ps -U $User -o time,pid,comm|egrep $Appname>runcon
    # while [ `cat runcon|egrep -c $Appname` -ge $SRunNum ]
    # do
    # 	for ((ck=1;ck<=`cat runcon|egrep -c $Appname`;ck=ck+1))
    # 	do
    # 	    psid=`head -$ck runcon|tail -1|sed 's/\w\+/:&:/g'|cut -d':' -f10`
    # 	    pshour=`head -$ck runcon|tail -1|sed 's/\w\+/:&:/g'|cut -d':' -f2`
    # 	    psmin=`head -$ck runcon|tail -1|sed 's/\w\+/:&:/g'|cut -d':' -f5`
    # 	    pstime=`calc \* $pshour 60`
    # 	    pstime=`calc + $pstime $psmin`
    # 	    if [ $pstime -ge $Stoptime ];then
    # 		kill $psid
    # 		echo '!!'$psid' run time '$pstime' exceed time limit '$Stoptime', kill it' 
    # 	    fi
    # 	done
    # 	if [ `ps -U $User|egrep -c $Appname` -ge $SRunNum ];then
    # 	    echo 'wait for 5 minutes'
    # 	    sleep 3m
    # 	fi
    # 	ps -U $User -o etime,pid,comm|egrep $Appname>runcon
    # done
    # rm -f runcon


###-save first run input parameters to Info.txt----------#
function firstruninfo() #In: start; Outfile: Info.txt; Out: start; Call winput
{
    if [ $start = 1 ]; then
	winput `echo $1|sed 's/_/ /g'`
	echo '*=Input file of the first run============================*'>>Info.txt
	cat input>>Info.txt
	start=0
	rm -f input
	echo '*=Data List:=============================================*'>>Info.txt
    fi
}
###-End check--------------------------------------------#
function endcheck() #Infile: joblist; Call waitrun
{
    while [ -e joblist ]
    do
	waitrun
	if [ $crashnum -ne 0 ]; then
	    echo 'new crash case found'
	    break
	fi
	if [ -e joblist ]; then
	    sleep 2m
	else
	    break
	fi
    done
}
export winput
export timecompare
export waitrun
export endcheck
###-list file--------------------------------------------#
function listfile_sub() #In: name; Infile: $name; Outfile: $name.list
{
    du *_*_*/$1|sort -n|sed 's/\/[A-Za-z0-9_\.]\+/ /g'|sed 's/_/ /g' >$1'.list'
}

#-Loop for running (main process)------------------------#
start=1
crashnum=1
while [ $crashnum -ne 0 ]
do
    crashnum=0
    if [ -d crash ];then
	echo 'crash directory exist'
	ls crash>crashlist
    else
	mkdir crash
	ls crash>crashlist
    fi

###-Need to change when change variable parameters-------# C
    for i in $Nstar
    do
	for j in $Rbar
	do
	    for k in $RatioNb
	    do
		for n in $RatioNpNs
		do
		    for m in $rand
		    do
			curdir=$i'_'$j'_'$k'_'$n'_'$m
			nownstar=`calc /n $i 100`
###-End change part--------------------------------------#
		    firstruninfo $curdir
		    waitrun
		    randnew=$m
		    checkflag=1
		    while [ $checkflag = 1 ]
		    do
			crashcheck
			if [ -d $curdir ];then        
			    echo $curdir' exist, check if it end run'
			    cd $curdir 
			    if [ -e run.log ]; then
				echo 'run.log exist, continue'
				if [ `tail -1 run.log|egrep -c 'END RUN'` = 1 ];then
				    echo 'This is an end run'
				    cd ..
				    if [ `egrep -c $curdir Info.txt` = 0 ]; then
					echo '** Endrun  '$curdir>>Info.txt
				    fi
				    checkflag=0
				else
				    randnew=`calc + $randnew 1000`
				    cd ..
				    if [ -e joblist ];then
					if [ `egrep -c $curdir joblist` -ge 1 ]; then
					    echo $curdir' running now, ignore'
					    checkflag=0
					else
					    echo '!Crash run, restart with new NRAND='$randnew
					    if [ `egrep $curdir Info.txt|egrep -c Crash` = 0 ]; then
						echo '*** Crash  '$curdir>>Info.txt
						tail -1 $curdir/run.log >>Info.txt
					    fi
					    mv -b $curdir crash/
					    crashnum=`calc + $crashnum 1`
					fi
				    else
					echo '!Crash run, restart with new NRAND='$randnew
					if [ `egrep $curdir Info.txt|egrep -c Crash` = 0 ]; then
					    echo '*** Crash  '$curdir>>Info.txt
					fi
					mv -b $curdir crash/
					crashnum=`calc + $crashnum 1`
				    fi
				    curdir=`echo $curdir|sed "s/[0-9]\+$/$randnew/"`
				fi
			    else
				echo 'run.log does not exist, start run'
				rm -r *
				winput `echo $curdir|sed 's/_/ /g'`
				runprocess $curdir
				cd ..
				if [ `egrep -c $curdir Info.txt` = 0 ]; then
				    echo '** Newrun  '$curdir' '$rundate' '$runtime>>Info.txt
				fi
				checkflag=0
			    fi
			else
			    echo 'Now: '$curdir
			    mkdir $curdir
			    cd $curdir
			    winput `echo $curdir|sed 's/_/ /g'`
			    runprocess $curdir
			    cd ..
			    if [ `egrep -c $curdir Info.txt` = 0 ]; then
				echo '** Newrun  '$curdir' '$rundate' '$runtime>>Info.txt
			    fi
			    checkflag=0
			fi
		    done
		    		    
###-Need to change when change variable parameters-------# C
		    done
		done
	    done
	done
    done
#-End change part----------------------------------------#    
    echo 'End cycle, Checked crash old run number is '$crashnum

#-End----------------------------------------------------#
    endcheck
    
done
if [ -d graph ]; then
    echo 'graph dir exist'
else
    mkdir graph
    echo 'creat graph dir'
fi
if [ -d mathedata ]; then
    echo 'mathedata dir exist'
else
    mkdir mathedata
    echo 'mathedata dir exist'
fi
listfile_sub OUT3
listfile_sub reg_body.out
listfile_sub reg_single.out

echo 'All finished'
