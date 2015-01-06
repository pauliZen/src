#!/bin/bash
#-Config-------------------------------
ID=1101110160
paswd=kiaalw515
model=1       # 0: free; 1: global
tcheckday=5m
tchecknight=15m
tretry=10m
tsuccesswait=30m
ttimeoutfree=5
ttimeoutglobal=10
webtestfree="http://www.baidu.com"
websavefree="index.baidu"
webpku="home.pku"
webtestglobal="http://www.ast.cam.ac.uk/~sverre/web/pages/nbody.htm"
websaveglobal="nbody.htm.bak"
webtestglobal2="http://www.gnu.org"
#--------------------------------------
date>>connect.log

function igconnecter()
{
    cmode=free
    if [ $model = 1 ];then
	cmode=global
    fi
    ipgwclient connect $ID $paswd $cmode>login.log
    loginflag=`egrep -c state=connected login.log`
    if [ $loginflag = 1 ]; then
	echo "connect successful "`date`>>connect.log
    else
	echo "*!connect unsuccessful, try disconnectall "`date`>>connect.log
	ipgwclient disconnectall $ID $paswd>login.log
	ipgwclient connect $ID $paswd $cmode>login.log
	loginflag=`egrep -c state=connected login.log`
	if [ $loginflag = 1 ]; then
	    echo "connect successful "`date`>>connect.log
	    sleep $tsuccesswait
	else
	    echo "**connect error, try connect later">>connect.log
	    sleep $tretry
	fi
    fi
}

while [ -e connect.log ]
do
#    [ -e /tmp/$websaveglobal ] && rm -f /tmp/$websaveglobal
#    [ -e /tmp/$websavefree ] && rm -f /tmp/$websavefree
    wget -q --tries=1 --timeout=$ttimeoutfree http://www.pku.edu.cn/ -O /tmp/$webpku &> /dev/null
    wget -q --tries=1 --timeout=$ttimeoutfree $webtestfree -O /tmp/$websavefree &> /dev/null
    wget -q --tries=1 --timeout=$ttimeoutglobal $webtestglobal -O /tmp/$websaveglobal &> /dev/null
#    wget -q --tries=1 --timeout=$ttimeoutglobal $webtestglobal2 -O /tmp/$websaveglobal &> /dev/null
    if [ -s /tmp/$websaveglobal ];then
	echo "connected now "`date`>>connect.log
	rm -f /tmp/$websaveglobal
	nowtime=`date +%H`
	if [[ $nowtime -ge 23 ]] || [[ $nowtime -le 3 ]]; then
	    sleep $tchecknight
	else
	    sleep $tcheckday
	fi
    else 
	if [ -s /tmp/$websavefree ];then
	    echo "free connected now "`date`>>connect.log
	    rm -f /tmp/$websavefree
	    if [ $model = 1 ]; then
		igconnecter
#		sh ~/src/scripts/sendip.sh
	    fi
	elif [ -s /tmp/$webpku ];then
	    echo "no connection, try connect "`date`>>connect.log
	    rm -f /tmp/$webpku
	    igconnecter
#	    sh ~/src/scripts/sendip.sh
	else
	    echo "no internet, try ifup "`date`>>connect.log
	    ifup eth0 >>connect.log
#	    sh ~/src/scripts/sendip.sh
	fi
    fi
    logline=`wc -l connect.log|cut -d' ' -f1`
    if [ $logline -ge 100000 ]; then
	rm -f connect.log
	date>>connect.log
    fi
done

