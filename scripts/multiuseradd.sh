namelist='chuanwu liyun thijs weihao xiaojia zxc'
for i in $namelist
do
    useradd -U -d /home/$i -s /bin/bash -p $i"thijs" $i
done
