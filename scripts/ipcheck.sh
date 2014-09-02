waittime=240m
while [ -e ~/.host_list ]
do
    sh ~/src/scripts/sendip.sh 1>send.log 2>&1
    sleep $waittime
done
