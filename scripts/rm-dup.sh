echo 'filename outfilename'
read infile outfile
sort -k1,6 -n $infile|uniq -c|sed 's/\ \+/|/g'|cut -d'|' -f3 >$outfile
