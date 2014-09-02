echo 'Name'
read name
du *_*_*/$name|sort -n|sed 's/\/[A-Za-z0-9_\.]\+/ /g'|sed 's/_/ /g' >$name'.list'
