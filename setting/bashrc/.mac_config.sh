#emacs
if [ -e /Applications/Emacs.app ]; then
    emacsname=/Applications/Emacs.app/Contents/MacOS/Emacs
    alias emacs=$emacsname' -nw -q'

# emacs GUI
    function emacx(){
	argu=''
	until [[ `echo $1` == '' ]]
	do
	    argu=$argu' '$1
	    shift
	done
	$emacsname $argu &
    }
    export emacx
fi

#list
alias ll='ls -lt'

#color for terminal
export CLICOLOR=1
export LSCOLORS=ExFxCxDxBxegedabagacad

export LC_CTYPE="en_US.UTF-8"

#DictUnifer
[ -e /opt/sdconv ] && alias dictunifer='/opt/sdconv/convert'
#pgplot library
[ -e /opt/pgplot ] && export PGPLOT_DIR=/opt/pgplot              
#CUDA
[ -e /Developer/NVIDIA/CUDA-5.0/bin ] && export PATH=/Developer/NVIDIA/CUDA-5.0/bin:$PATH        
[ -e /Developer/NVIDIA/CUDA-5.0/lib ] && export DYLD_LIBRARY_PATH=/Developer/NVIDIA/CUDA-5.0/lib:$DYLD_LIBRARY_PATH
#slog2sdk
[ -e /opt/slog2sdk ] && PATH=$PATH:/opt/slog2sdk/bin
#root
[ -e /opt/root/bin/thisroot.sh ] && . /opt/root/bin/thisroot.sh && alias root='root -l'
#[ -d /opt/root/test ]
#	    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$i/test/
#	    DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$i/test/
#	    SHLIB_PATH=$SHLIB_PATH:$i/test/
#	    LIBPATH=$LIBPATH:$i/test/
#sbcl
[ -d /usr/local/lib/sbcl ] && export SBCL_HOME=/usr/local/lib/sbcl
#scheme
[ -e /Applications/MIT-GNU-Scheme.app/Contents/Resources/mit-scheme ] && PATH=$PATH:/Applications/MIT-GNU-Scheme.app/Contents/Resources && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/Applications/MIT-GNU-Scheme.app/Contents/Resources/lib
#mathematica
mathematica_path=/Applications/Mathematica.app/Contents/MacOS/
[ -e $mathematica_path/Mathematica ] && alias mathematica='$mathematica_path/Mathematica &'
[ -e $mathematica_path/MathKernel ] && alias mathkernel='$mathematica_path/MathKernel'
#clang-openmp
# if [ -d /opt/cang-omp ]; then
#     CLANG_HOME=/opt/clang-omp
#     OPENMP_HOME=
#     export PATH=$CLANG_HOME/bin:$PATH
#     export C_INCLUDE_PATH=$CLANG_HOME/include:$C_INCLUDE_PATH
#     export CPLUS_INCLUDE_PATH=$CLANG_HOME/include:$CPLUS_INCLUDE_PATH
#     export LIBRARY_PATH=$CLANG_HOME/lib:$LIBRARY_PATH
#     export DYLD_LIBRARY_PATH=$CLANG_HOME/lib:$DYLD_LIBRARY_PATH
# fi
#pkg-config
#if [ -d /opt/pkg-config ] ; then
#    export PKG_CONFIG=/opt/pkg-config/bin/pkg-config
#    export PATH=/opt/pkg-config/bin:$PATH
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
#fi
#wxWidgets
if [ -e /opt/wxWidgets ] ; then
    wxWidgets_HOME=/opt/wxWidgets
    export PATH=$wxWidgets_HOME/bin:$PATH
    export C_INCLUDE_PATH=$wxWidgets_HOME/include:$C_INCLUDE_PATH
    export CPLUS_INCLUDE_PATH=$wxWidgets_HOME/include:$CPLUS_INCLUDE_PATH
    export DYLD_LIBRARY_PATH=$wxWidgets_HOME/lib:$DYLD_LIBRARY_PATH
    export LIBRARY_PATH=$wxWidgets_HOME/lib:$LIBRARY_PATH
fi
if [ -d /Library/Frameworks/QtCore.framework ]; then
    QT_HOME=/Library/Frameworks
    QTLST=`ls -d $QT_HOME/Qt*.framework/Headers|awk '{print "-I"$1}'`
    export QT_CFLAGS=`echo $QTLST`
    QTLST="-F$QT_HOME "`ls $QT_HOME|egrep Qt|cut -d'.' -f1|awk '{print "-framework "$1}'`
    export QT_LIBS=`echo $QTLST`
#    QT_LIBS=`'-L'$QT_HOME/lib' '`ls $QT_HOME/lib |egrep '\.la'|awk '{print "-l"$1}'|sed -e 's/lib//g' -e '/_debug/ d' -e 's/.la//g'`
#    export PATH=$QT_HOME/bin:$PATH
#    export C_INCLUDE_PATH=$QT_HOME/include:$C_INCLUDE_PATH
#    export CPLUS_INCLUDE_PATH=$QT_HOME/include:$CPLUS_INCLUDE_PATH
#    export LIBRARY_PATH=$QT_HOME/lib:$LIBRARY_PATH
#    export DYLD_LIBRARY_PATH=$QT_HOME/lib:$DYLD_LIBRARY_PATH
#    [ -d /opt/pkg-config ] && export PKG_CONFIG_PATH=$QT_HOME/lib/pkgconfig:$PKG_CONFIG_PATH 
fi
  
#proxy
function sps()
{
    iname='lwpc'
    iport=8087
    igo=0
    ioff=0
    iauto=0
    ihelp=0
    ikill=1
    netname="Wi-Fi"
    until [[ `echo $1` == '' ]]
    do
	case $1 in
	    -h) ihelp=1;break;;
	    -i) iname='lwpcin';shift;;
	    -p) shift;iport=$1;shift;;
	    -g) igo=1;shift;;
	    -o) ioff=1;shift;;
	    -l) netname='USB Ethernet';shift;;
	    -P) netname='PPPoE';shift;;
	    -a) iauto=1;shift;;
	    -k) ikill=0;shift;;
	    *) iname=$1;shift;;
	esac
    done
    if [ $ihelp = 1 ]; then
	echo 'sps [option] [server name]'
	echo '---option---'
	echo '   -p: set port to forward instead of 8087'
	echo '   -g: set port forwarding for 8087 port from server. if the server already have http(https) proxy on port 8087(like goagent), this option can be used'
	echo '   -o: remove socks and web proxy'
	echo '   -l: set proxy for USB Ethernet instead of Wi-Fi'
	echo '   -a: set autoproxyurl to 127.0.0.1/goagent.pac'
    else
	ihost=`findip $iname`
	iuid=`ps ax|egrep "ssh -f -[DL] $iport"|egrep -v 'egrep'|awk '{print $1}'`
	[[ $iuid != '' ]] && echo 'Port '$iport' already in use, try to kill the present port forwarding for it' && kill $iuid
	if [ $ikill = 1 ]; then
	    klist=`ssh $ihost 'ps ax'|egrep 'tail -f /etc/motd'|awk '{print $1}'`
	    [[ $klist != '' ]] && ssh $ihost kill $klist
	fi
	if [ $ioff = 1 ]; then
	    sudo networksetup -setsocksfirewallproxystate "$netname" "off"
	    sudo networksetup -setwebproxystate "$netname" "off"
	    sudo networksetup -setsecurewebproxystate "$netname" "off"
	    sudo networksetup -setautoproxystate "$netname" "off"
	elif [ $iauto = 1 ]; then
	    sudo networksetup -setsocksfirewallproxystate "$netname" "off"
	    sudo networksetup -setwebproxystate "$netname" "off"
	    sudo networksetup -setsecurewebproxystate "$netname" "off"
	    sudo networksetup -setautoproxyurl "$netname" "127.0.0.1/goagent.pac"
	elif [ $igo = 0 ]; then
	    ssh -f -D $iport $ihost tail -f /etc/motd
	    [ `ps ax|egrep "ssh -f -D $iport"|egrep -v 'egrep'|wc -l` = 1 ] || return
	    echo 'Dynamical forwarding: '$ihost' --> 127.0.0.1:'$iport
	    sudo networksetup -setwebproxystate "$netname" "off"
	    sudo networksetup -setsecurewebproxystate "$netname" "off"
	    sudo networksetup -setsocksfirewallproxy "$netname" "127.0.0.1" $iport
	    sudo networksetup -setautoproxystate "$netname" "off"
	else
	    ssh -f -L $iport:127.0.0.1:8087 $ihost tail -f /etc/motd
	    [ `ps ax|egrep "ssh -f -L $iport"|egrep -v 'egrep'|wc -l` = 1 ] || return
	    echo 'Port forwarding: '$ihost':8087 --> 127.0.0.1:'$iport
	    sudo networksetup -setwebproxy "$netname" "127.0.0.1" $iport
	    sudo networksetup -setsecurewebproxy "$netname" "127.0.0.1" $iport
	    sudo networksetup -setsocksfirewallproxystate "$netname" "off"
	    sudo networksetup -setautoproxystate "$netname" "off"
	fi
    fi
}

#host change
function ip64()
{
    [ -e /etc/hosts.ipv4 ] && [ -e /etc/hosts.ipv6 ] || return
    case $1 in
	-i) sudo cp /etc/hosts.ipv4 /etc/hosts ; echo 'host->ipv4';;
	-g) sudo cp /etc/hosts.google /etc/hosts ; echo 'host->ipv4.google';;
	-h) echo '-i host->ipv4; -g host->ipv4.google default: host->ipv6';;
	*) sudo cp /etc/hosts.ipv6 /etc/hosts ; echo 'host->ipv6';;
    esac
}

#mount ntfs
function mntfs()
{
    [[ $1 == '' ]] && return
    devpath=`diskutil info /Volumes/$1|egrep 'Device Node'|awk '{print $3}'`
    [[ $devpath == '' ]] && return
    sudo umount /Volumes/$1
    [[ -e /Volumes/$1 ]] || mkdir /Volumes/$1
    sudo mount -t ntfs -o nobrowse,rw $devpath /Volumes/$1
}

