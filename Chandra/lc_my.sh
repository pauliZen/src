#ccd.txt contains ccd_id.
#make link to evt2 and asol
ln -sf ../lev2/acis_dstrk_evt2.fits evt2.fits
cp ../lev2/asol.fits asols.fits
cp ../lev2/asols.lis asols.lis

#restrict the ACIS-id chip and the 0.5-7 keV energy range.outfile=evt2_c7.fits
dmcopy "evt2.fits[energy=500:7000,ccd_id=`head -1 ccd.txt |tail -1`]" evt2_c7.fits
dmcopy "evt2_c7.fits[bin sky=8]" img8_c7.fits

#Find the background file.
acis_bkgrnd_lookup evt2_c7.fits>bkg.lis

#sources remove outfile=evt2_c7_bg.fits; source:src.fits
punlearn celldetect
celldetect infile=evt2_c7.fits \
	outfile=src.fits \
	regfile=src.reg \
	clobber=yes

dmcopy "evt2_c7.fits[exclude sky=region(src.reg)]" evt2_c7_bg.fits clobber=yes

#creat light_curve outfile=evt2_c7_bg.lc
punlearn dmextract
dmextract "evt2_c7_bg.fits[bin time=::259.28]" \
      outfile=lc_c7.fits \
      opt=ltc1 \
      clobber=yes

#lc_clean routine outfile=evt2_c7_clean.fits
chips<<EOF
from lightcurves import *
lc_sigma_clip("lc_c7.fits", outfile="evt2_c7_bg.gti")
quit
EOF
dmcopy "evt2_c7_bg.fits[@evt2_c7_bg.gti]" evt2_c7_clean.fits

dmmerge @bkg.lis merge_bg.fits
dmcopy "merge_bg.fits[status=0]" acis_bkg.fits clobber=yes

punlearn reproject_events
reproject_events infile="acis_bkg.fits[cols -time]" \
	outfile=acis_bkg_reproj.fits \
	aspect=asols.fits \
	match=evt2_c7_clean.fits \
	random=0 \
	clobber=yes

#lightcurve outfile=evt2_c7_clean.fits

#emacs history.txt &
mkdir ../sp
ln -sf $apw/spectrum.sh ../sp/spectrum.sh
ln -sf $apw/spout.sh ../sp/spout.sh