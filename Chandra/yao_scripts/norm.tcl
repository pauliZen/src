set ff [open norm-err.txt w]

tclout param 8
puts $ff $xspec_tclout

error 1. 8
tclout error 8
puts $ff $xspec_tclout

tclout param 16
puts $ff $xspec_tclout

error 1. 16
tclout error 16
puts $ff $xspec_tclout

tclout param 24
puts $ff $xspec_tclout

error 1. 24
tclout error 24
puts $ff $xspec_tclout

tclout param 32
puts $ff $xspec_tclout

error 1. 32
tclout error 32
puts $ff $xspec_tclout

tclout param 40
puts $ff $xspec_tclout

error 1. 40
tclout error 40
puts $ff $xspec_tclout

tclout param 48
puts $ff $xspec_tclout

error 1. 48
tclout error 48
puts $ff $xspec_tclout
