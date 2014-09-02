#for i in {101..130}
#do
#    let j=${i}-99
#    mkdir $i
#    head -$j ans30.reg |tail -1 >$i/ans30.reg
#    cd $i
    
    #punlearn specextract
    #specextract infile="../evt2_c7_srcless.fits[sky=region(ans30.reg)]" \
    #outroot=src \
    #bkgfile="../acis_bkg_reproj.fits[sky=region(ans30.reg)]" \
    #pbkfile="../../../secondary/acisf_pbk0.fits" \
    #grouptype=NUM_CTS binspec=20 \
    #verbose=5

punlearn dmextract
dmextract infile="evt2_c7_srcless.fits[sky=region(tempavg.reg)][bin pi]" \
outfile=src.pi \
wmap="[bin det=8]" \

punlearn mkwarf
mkwarf infile="src.pi[WMAP]" \
outfile=src.warf \
weightfile=src.wgt \
spectrumfile=none \
egridspec=0.5:11:0.01 \
pbkfile=../../secondary/acisf_pbk0.fits \
threshold=0 \

punlearn mkrmf
mkrmf infile="CALDB" \
outfile=src.wrmf \
axis1="energy=0:1" \
axis2="pi=1:1024:1" \
weights=src.wgt \

punlearn dmextract
dmextract infile= "acis_bkg_reproj.fits[sky=region(tempavg.reg)][bin pi]" \
outfile=src_bkg.pi \
wmap="[bin det=8]" \

punlearn dmgroup
dmgroup infile="src.pi[spectrum]" \
outfile=src_grp.pi \
grouptype=NUM_CTS \
xcolumn=channel \
ycolumn=counts \
binspec=30 \
grouptypeval= 15.000000 \
maxlength= 0.000000 \
clobber = yes \
verbose = 1 \

    r=`cat tempavg.reg|grep annu|awk -F , '{print $4}'|tr -d ')'`
    echo $r
    dmhedit src_grp.pi filelist=none operation=add key="XFLT0001" value=$r datatype=double
    dmhedit src_grp.pi filelist=none operation=add key="XFLT0002" value=$r datatype=double
    dmhedit src_grp.pi filelist=none operation=add key="XFLT0003" value=0

    dmhedit src_grp.pi filelist=none operation=add key="BACKFILE" value="'src_bkg.pi'"
    dmhedit src_grp.pi filelist=none operation=add key="ANCRFILE" value="'src.warf'"
    dmhedit src_grp.pi filelist=none operation=add key="RESPFILE" value="'src.wrmf'"

dmhedit src_grp.pi filelist=none operation=add key="BACKSCAL" value=1 datatype=double
dmhedit src_bkg.pi filelist=none operation=add key="BACKSCAL" value=1 datatype=double

#cd ..
#done

