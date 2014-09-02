#emacs
if [ `ls /usr/bin|egrep -c ^emacs[0-9\-]` -gt 0 ]; then
    emacsname=`ls /usr/bin|egrep ^emacs[0-9\-]|head -1`
    alias emacs=$emacsname' -nw -q'

# emacs GUI
    function emacx(){
	argu=''
	nox=0
	until [[ `echo $1` == '' ]]
	do
	    case $1 in
		-nw) argu=$argu' '$1;shift; nox=1;;
		*) argu=$argu' '$1; shift;;
	    esac
	done
	if [ $nox = 1 ]; then
	    $emacsname $argu
	else
	    $emacsname $argu &
	fi
    }
    export emacx
fi

#For hugepage
export HUGETLB_MORECORE=yes                                      
#GPU cuda
[ -e /usr/local/cuda_sdk ] && PATH=$PATH:/usr/local/cuda_sdk/C/bin/linux/release/
[ -e /usr/local/cuda ] && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64
#root
[ -e /opt/root/bin/thisroot.sh ] && . /opt/root/bin/thisroot.sh && alias root='root -l'
#[ -d /opt/root/test ]
#	    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$i/test/
#	    DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$i/test/
#	    SHLIB_PATH=$SHLIB_PATH:$i/test/
#	    LIBPATH=$LIBPATH:$i/test/
#scisoft
[ -d /scisoft/bin ] && export SCISOFT_IGNORE_SELINUX_WARNING=1 && . /scisoft/bin/Setup.bash
[ -e /usr/bin/gnuplot ] && alias gnuplot='/usr/bin/gnuplot'
#mit-scheme
[ -d /opt/mit-scheme ] && PATH=$PATH:/opt/mit-scheme/bin && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/mit-scheme/lib
#libgd
[ -d /opt/libgd ] && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/libgd/lib && PATH=$PATH:/opt/libgd/bin
#nemo
[ -d /opt/nemo ] && PATH=$PATH:/opt/nemo/bin
#open
alias go='gnome-open'
#rotate screen
#xrandr -o left,right
