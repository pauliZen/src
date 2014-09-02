set ff [open flux-err.txt w]

flux .7 7. err 1000 68
set num 6
for {set i 1} {$i<=$num} {incr i} {tclout flux $i
puts $ff $xspec_tclout}
