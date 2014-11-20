reset

set term postscript landscape enhanced color "Text" 16
set output 'event.ps'
filename='event'

set key autotitle columnhead

do for [i=2:16] {
   plot filename u 1:i w lp
}

plot filename u 1:17 w lp title 'kw = 1', \
           '' u 1:18 w lp title 'kw = 2', \
           '' u 1:19 w lp title 'kw = 3', \
           '' u 1:20 w lp title 'kw = 4', \
           '' u 1:21 w lp title 'kw = 5', \
           '' u 1:22 w lp title 'kw = 6', \
           '' u 1:23 w lp title 'kw = 7', \
           '' u 1:24 w lp title 'kw = 8', \
           '' u 1:25 w lp title 'kw = 9', \
           '' u 1:26 w lp title 'kw = 10', \
           '' u 1:27 w lp title 'kw = 11', \
           '' u 1:28 w lp title 'kw = 12', \
           '' u 1:29 w lp title 'kw = 13', \
           '' u 1:30 w lp title 'kw = 14', \
           '' u 1:31 w lp title 'kw = 15'
exit
