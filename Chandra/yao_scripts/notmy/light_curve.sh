#No matter which ccd has your data, dmcopy it, and name it evt2_c7.fits; 
#>dmcopy "evt2.fits[ccd_id=7]" evt2_c7.fits
#Save in secondary.
#Circle the main source, make the format CIAO, and name it exclude.reg; save in secondary


cd ..
mkdir evt2 evt2/bkg evt2/evt evt2/img evt2/sbp evt2/spc
cd evt2/bkg
ln -sf ../../secondary/asol.fits
ln -sf ../../secondary/evt2_c7.fits
cd ../spc
ln -sf ../../secondary/exclude.reg
cd ../evt
ln -sf ../../secondary/evt2_c7.fits
ln -sf ../../secondary/exclude.reg

#celldetect in evt
punlearn celldetect
celldetect infile=evt2_c7.fits \
	outfile=src1.fits \
	regfile=src1.reg \
	clobber=yes

dmcopy "evt2_c7.fits[exclude sky=region(src1.reg)]" evt2_c7_srcless.fits clobber=yes

#lightcurve in evt
punlearn dmextract
dmextract "evt2_c7_srcless.fits[exclude sky=region(exclude.reg)][bin time=::200]" \
	outfile=lc_c7.fits \
	opt=ltc1 \
	clobber=yes

chips<<EOF
from lightcurves import *
lc_sigma_clip("lc_c7.fits")
lc_sigma_clip("lc_c7.fits", outfile="lc_c7.gti")
quit
EOF

dmcopy "evt2_c7_srcless.fits[@lc_c7.gti]" evt2_c7_srcless_lc.fits clobber=yes

#celldetect again
#punlearn celldetect
#celldetect infile=evt2_c7_srcless_lc.fits \
#	outfile=src.fits \
#	regfile=src.reg \
#	clobber=yes

dmcopy "evt2_c7_srcless_lc.fits" evt2_c7_srcless.fits clobber=yes


#specextract in bkg & spc/temp
cd ../bkg
#ln -sf `acis_bkgrnd_lookup evt2_c7.fits|head -1` acis_bkg.fits
acis_bkgrnd_lookup evt2_c7.fits>bkg.lis

dmmerge @bkg.lis acis_bkg_tmp.fits
dmcopy "acis_bkg_tmp.fits[status=0]" acis_bkg.fits clobber=yes
punlearn reproject_events
reproject_events infile="acis_bkg.fits[cols -time]" \
	outfile=acis_bkg_reproj.fits \
	aspect=asol.fits \
	match=evt2_c7.fits \
	random=0 \
	clobber=yes



cd ../spc
ln -s ../evt/evt2_c7_srcless.fits
ln -s ../bkg/acis_bkg_reproj.fits
#punlearn specextract
#specextract infile="evt2_c7_srcless.fits[sky=region(exclude.reg)]" \
#	outroot=src \
#	bkgfile="../bkg/acis_bkg_reproj.fits" \
#	pbkfile=../../secondary/acisf_pbk0.fits \
#	grouptype=NUM_CTS binspec=20 \
#	verbose=1 \
#	clobber=yes

ln -s ~/xdata/scripts/s3.sh
ln -s ~/xdata/scripts/s4.sh
ln -s ~/xdata/scripts/ans30.xcm
ln -s ~/xdata/scripts/ans6.xcm
ln -s ~/xdata/scripts/ans.tcl
