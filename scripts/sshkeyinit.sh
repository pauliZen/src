function check_dragon()
{
    myusername=`whoami`
    dhost=10.0.1.3
    if [[ $1 = update ]]; then
	scp $myusername@$dhost:/opt/dlist ~/.ssh/dragon.list
    fi
    [ -e ~/.ssh/dragon.list ] || scp $myusername@$dhost:/opt/dragon.list ~/.ssh/dragon.list
    if [ -e ~/.ssh/dragon.list ]; then
	dlist=`cat ~/.ssh/dragon.list`
	rm -f ~/.ssh/check.list
	for i in $dlist
	do
	    ihost=`echo $i|cut -d':' -f2`
	    iname=`echo $i|cut -d':' -f1`
	    if [[ $iname.kiaa != `hostname` ]] ;then
		[ -e ~/.ssh/authorized_keys ] || echo " ">~/.ssh/authorized_keys
		if [ -e ~/.ssh/authorized_keys ]; then
		    chmod 644 ~/.ssh/authorized_keys
		    if [ `egrep -c $iname ~/.ssh/authorized_keys` -eq 0 ] ; then
			echo 'Download id_rsa.pub from '$iname'. Please input your user password if needed, maybe you also need to generate rsa key again.'
			echo -e '\033[31mPS: If you find no response, please input Enter three times (many be more) until password input notice appear again\033[0m'
			ssh $myusername@$ihost "[ -e ~/.ssh/id_rsa.pub ] || ssh-keygen -t rsa && chmod 700 ~/.ssh"
			scp $myusername@$ihost:.ssh/id_rsa.pub ~/.ssh/id_rsa_$iname.pub
			if [ -e ~/.ssh/id_rsa_$iname.pub ] ;then
	    		    cat ~/.ssh/id_rsa_$iname.pub >> ~/.ssh/authorized_keys
			    echo $iname'_suc'>>~/.ssh/check.list
			    echo 'Add '$iname' to authorized list'
			else
			    echo 'Failed, maybe you need to ask manager for help'
			    echo $iname'_fail'>>~/.ssh/check.list
			fi
		    else
			echo $iname'_exist'>>~/.ssh/check.list
		    fi
		fi
	    fi
	done
    fi
}    

if [ -e ~/.ssh/id_rsa -a -e ~/.ssh/id_rsa.pub ] ; then
    if [ -e ~/.ssh/check.list ] ;then
	[ `egrep -c '_fail' ~/.ssh/check.list` -ge 1 ] && check_dragon
    else
	check_dragon
    fi
else
    echo "Now will generate ssh-key, Please input Enter when input is needed (3 times)"
    ssh-keygen -t rsa
    chmod 700 ~/.ssh
    check_dragon
fi
    
