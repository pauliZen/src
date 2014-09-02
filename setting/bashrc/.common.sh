#-------------environment------------#
#Folder:
[ -e ~/data ] && export data=~/data
[ -e ~/src ] && export src=~/src
[ -e ~/bin ] && export bin=~/bin

#PATH
[ -e ~/bin ] && export PATH=$PATH:$bin

#Lib
if [ -e ~/lib ]; then
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/lib
    DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/lib
    SHLIB_PATH=$SHLIB_PATH:~/lib
    LIBPATH=$LIBPATH:~/lib
fi

# force rm to check
alias rm='rm -i'

