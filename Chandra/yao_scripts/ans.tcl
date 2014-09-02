set ans 6

for {set i 1} {$i<=$ans} {incr i} {data $i:$i $i/src_grp.pi}

for {set i 1} {$i<=$ans} {incr i} {ignore $i:0.-.7 7.-**}

mo projct*wabs*apec
