#Transform scan index file ("index") to index list file--#
echo 'Transform tree scan log file ("index") to index list file'
echo 'input log file, output log file'
read namein nameout
cat $namein |cut -d'*' -f3|egrep '  [0-9]+' > $nameout
