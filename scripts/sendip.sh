newip=`curl ipecho.net/plain`
if [ -e ~/.host_list ] ; then
    oldip=`egrep 'iplighter=' ~/.host_list|cut -d'=' -f2 |cut -d' ' -f1`
    if [[ $newip != $oldip ]] ;then
	sed -i "/iplighter=/s/[0-9\.\ ]*#/$newip\ #/" ~/.host_list
	scp ~/.host_list $lwpc:
	scp ~/.host_list $dragon:
	scp ~/.host_list $milky:
    fi
fi
