#######################################################
####Auto chandra ACIS data basic procession script#####
####By Gu Junhua 2007.2 ###############################
####Based on CIAO 4.1 threads##########################
####Debugged by Yao Mengyu#############################
#######################################################

#To run this script, following files are required:
#evt1,asol,flt1,msk1,pbk0,bias
#output file name:evt2.fits
gunzip *gz


rm -f acisf_evt1.fits acisf_flt1.fits acisf_bpix1.fits acisf_msk1.fits acisf_pbk0.fits asol.fits


ln -sf `ls|grep pcadf|grep asol1` asol.fits
ln -sf `ls|grep acisf|grep evt1` acisf_evt1.fits
ln -sf `ls|grep acisf|grep msk1` acisf_msk1.fits
ln -sf `ls|grep acisf|grep bpix1` acisf_bpix1.fits
ln -sf `ls|grep acisf|grep flt1` acisf_flt1.fits
ln -sf `ls|grep acisf|grep pbk0` acisf_pbk0.fits
ls |grep acisf|grep bias>bias_files.lis
ls pcad*asol*>asols.lis

echo "reseting status..."

#   -- Remove the acis_detect afterglow Correction 
#   -- see http://cxc.harvard.edu/ciao/threads/acisdetectafterglow/

punlearn dmtcalc
#pset dmtcalc infile=acisf_evt1.fits
#pset dmtcalc outfile=acis_status_reseted.fits
#pset dmtcalc expression="status=status,status=X15F,status=X14F,status=X13F,status=X12F"
dmtcalc infile=acisf_evt1.fits outfile=acis_status_reseted.fits\
    expression="status=status,status=X15F,status=X14F,status=X13F,status=X12F" clobber=yes verbose=5

#   -- Identify and flag "hot" pixels and cosmic-ray "afterglows".
#   -- see http://cxc.harvard.edu/ciao/ahelp/acis_run_hotpix.html

echo "creating new bad pixel file..."
punlearn acis_run_hotpix
#pset acis_run_hotpix infile=acis_status_reseted.fits
#pset acis_run_hotpix outfile=acis_new_bpix1.fits
#pset acis_run_hotpix badpixfile=acisf_bpix1.fits
#pset acis_run_hotpix biasfile=@bias_files.lis
#pset acis_run_hotpix maskfile=acisf_msk1.fits
#pset acis_run_hotpix pbkfile=acisf_pbk0.fits
acis_run_hotpix infile=acis_status_reseted.fits \
    outfile=acis_new_bpix1.fits\
    badpixfile=acisf_bpix1.fits\
    biasfile=@bias_files.lis\
    maskfile=acisf_msk1.fits\
    pbkfile=acisf_pbk0.fits\
    clobber=yes verbose=2


punlearn acis_process_events

echo "recreating evt1 file..."

if dmkeypar acisf_evt1.fits DATAMODE echo+|grep VFAINT>/dev/null
    then
    echo "VFAINT mode"
    punlearn acis_process_events
    pset acis_process_events clobber=yes
    acis_process_events clobber=yes\
	infile=acisf_evt1.fits\
	outfile=acis_new_evt1.fits\
	badpixfile=acis_new_bpix1.fits\
	acaofffile=@asols.lis\
	eventdef=")stdlev1"\
	check_vf_pha=yes \
	trail=0.027
else
    echo "FAINT mode"
    acis_process_events infile=acisf_evt1.fits outfile=acis_new_evt1.fits badpixfile=acis_new_bpix1.fits acaofffile=@asols.lis eventdef=")stdlev1" clobber=yes
    
fi


echo "creating evt2 file"
punlearn dmcopy
dmcopy "acis_new_evt1.fits[EVENTS][grade=0,2,3,4,6,status=0]"\
    acis_flt_evt1.fits clobber=yes
punlearn dmcopy
dmcopy "acis_flt_evt1.fits[EVENTS][@acisf_flt1.fits][cols -phas]" acis_evt2.fits clobber=yes verbose=5

echo "destreaking..."
punlearn destreak
destreak infile=acis_evt2.fits outfile=acis_dstrk_evt2.fits clobber=yes verbose=5

