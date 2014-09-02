#replace filename in queue
function replace_name()
{
    until [[ `echo $1` == '' ]]
    do
        case $1 in
            -g) shift; rtimes=$1; shift;;
            -r) shift; originname=$1; shift;;
            -o) shift; oldchars=$1; shift;;
            -t) shift; newname=$1; shift;;
        esac
    done
    echo 'replace start number = '$rtimes
    echo 'search regexp = '$originname
    echo 'old chars = '$oldchars
    echo 'replaced by = '$newname
    echo 'Continue?(y/n)'
    read flag
    [[ $flag == 'y' ]] || return
    flist=`ls |egrep "$originname"`
    for i in $flist
    do
        taskfile=`echo $i|sed s/$oldchars/$newname/"$rtimes"`
        echo $i'->'$taskfile
        mv $i $taskfile
    done
}
