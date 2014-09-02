set ff [open kt-err.txt w]

tclout param 5
puts $ff $xspec_tclout

error 1. 5
tclout error 5
puts $ff $xspec_tclout

tclout param 13
puts $ff $xspec_tclout

error 1. 13
tclout error 13
puts $ff $xspec_tclout

tclout param 21
puts $ff $xspec_tclout

error 1. 21
tclout error 21
puts $ff $xspec_tclout

tclout param 29
puts $ff $xspec_tclout

error 1. 29
tclout error 29
puts $ff $xspec_tclout

tclout param 37
puts $ff $xspec_tclout

error 1. 37
tclout error 37
puts $ff $xspec_tclout

tclout param 45
puts $ff $xspec_tclout

error 1. 45
tclout error 45
puts $ff $xspec_tclout
