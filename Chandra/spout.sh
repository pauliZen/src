mkdir data
mkdir sct
cd sct
ln -s $apw/dp/dynamical_fit.out
ln -s $apw/dp/readkt.py
ln -s $apw/dp/readnorm.py
ln -s $apw/dp/fit-kt.cfg
ln -s $apw/dp/fit-ne.cfg
ln -s $apw/dp/clngfunc.py
ln -s $apw/dp/rhodm.py
ln -s $apw/dp/fit-nfw.cfg
ln -s $apw/dp/nfw.py
ln -s $apw/dp/readflux.py
ln -s $apw/dp/fit-sur.cfg
ln -s $apw/dp/lumin.py
cd ..
ln -s $apw/dp/kt.tcl
ln -s $apw/dp/norm.tcl
ln -s $apw/dp/flux.tcl
ln -s $apw/dp/dataout.sh