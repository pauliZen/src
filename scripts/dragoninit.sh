bindir='/home/'`whoami`'/bin'
chkbin=`echo $PATH|egrep -c $bindir`
[ -e ~/bin ] || mkdir ~/bin
[ $chkbin = 1 ] || export PATH=$PATH:$chkbin

