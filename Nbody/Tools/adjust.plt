#set term pngcairo

plot 'adjust' u 3:17 t 'EKIN'  , \
           '' u 3:19 t 'POT'   , \
           '' u 3:21 t 'ETIDE' , \
           '' u 3:25 t 'EBIN'  , \
           '' u 3:27 t 'EMERGE', \
           '' u 3:29 t 'ESUB'  , \
           '' u 3:31 t 'ECOLL' , \
           '' u 3:33 t 'EMDOT' , \
           '' u 3:35 t 'ECDOT'
