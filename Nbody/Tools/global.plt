reset

set term postscript landscape enhanced color "Text" 16
set output 'global.ps'
filename='global'

set key autotitle columnhead

do for [i=3:71] {
   plot filename u 2:i w lp
}

exit
