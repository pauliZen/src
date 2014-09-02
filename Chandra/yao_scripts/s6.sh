cd ../sbp
ln -s ../spc/evt2_c7_srcless.fits
ln -s ../spc/ans30.reg
ln -s ../spc/box.reg

dmcopy "evt2_c7_srcless.fits[energy=700:7000][sky=region(box.reg)][bin x=::1,y=::1]" img_0.7-7.fits

xcen=`tail -1 box.reg |awk -F , '{print $1}'|tr --delete '[a-z]()'`
ycen=`tail -1 box.reg |awk -F , '{print $2}'|tr --delete '[a-z]()'`
xlen=`tail -1 box.reg |awk -F , '{print $3}'|tr --delete '[a-z]()'`
ylen=`tail -1 box.reg |awk -F , '{print $4}'|tr --delete '[a-z]()'`

x1=$(echo "$xcen-$xlen*.5"|bc)
x2=$(echo "$xcen+$xlen*.5"|bc)
y1=$(echo "$ycen-$ylen*.5"|bc)
y2=$(echo "$ycen+$ylen*.5"|bc)

echo $x1:$x2:#$xlen,$y1:$y2:#$ylen 

punlearn merge_all
merge_all evt2_c7_srcless.fits asol=../../secondary/asol.fits chip="0:3" xygrid="$x1:$x2:#$xlen,$y1:$y2:#$ylen" energy=7 expmap=exp_0.7-7.fits expcorr=expcorr_0.7-7.fits

punlearn dmextract
dmextract infile="img_0.7-7.fits[bin sky=@ans30.reg]" outfile=sbp.fits clobber=yes exp=exp_0.7-7.fits

punlearn dmtcalc
dmtcalc "sbp.fits" sbp_rmid.fits expression="rmid=(r[0]+r[1])/2,rerr=(r[1]-r[0])/2" clobber=yes

dmlist sbp_rmid.fits'[cols rmid,rerr,sur_flux]' data|tail -30|awk '{print $2,$3,$4}'> sur_flux.qdp


cd ..
ln -s ~/xdata/scripts/kt-30.py
ln -s ~/xdata/scripts/kt100.py
ln -s ~/xdata/scripts/dynamical_fit.out
ln -s ~/xdata/scripts/readkt.py
ln -s ~/xdata/scripts/readnorm.py
ln -s ~/xdata/scripts/fit-kt.cfg
ln -s ~/xdata/scripts/fit-ne.cfg
ln -s ~/xdata/scripts/clngfunc.py
ln -s ~/xdata/scripts/fit-ne-30-beforenorm.cfg
ln -s ~/xdata/scripts/rhodm.py
ln -s ~/xdata/scripts/fit-nfw.cfg
ln -s ~/xdata/scripts/nfw.py
ln -s ~/xdata/scripts/readflux.py
ln -s ~/xdata/scripts/fit-sur.cfg
ln -s ~/xdata/scripts/lumin.py
cd spc
ln -s ~/xdata/scripts/kt.tcl
ln -s ~/xdata/scripts/norm.tcl
ln -s ~/xdata/scripts/flux.tcl
