xspec<<EOF
@ans6.xcm
fit
@kt.tcl
@flux.tcl
@norm.tcl
EOF
mv kt-err.txt data/
mv flux-err.txt data/
mv norm-err.txt data/
