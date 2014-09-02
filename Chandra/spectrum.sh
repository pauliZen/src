cp ../lev2/acisf_pbk0.fits acisf_pbk0.fits
ln -sf ../light_curve/evt2_c7_clean.fits evt2_c7_srcless.fits
ln -sf ../light_curve/acis_bkg_reproj.fits acis_bkg_reproj.fits


for i in {1..6}
do
    let j=${i}+1
    mkdir $i
    head -$j ans6.reg |tail -1 >$i/ans6.reg
    cd $i

#SLOW#
    #punlearn specextract
    #specextract infile="../evt2_c7_srcless.fits[sky=region(ans6.reg)]" \
    #outroot=src \
    #bkgfile="../acis_bkg_reproj.fits[sky=region(ans6.reg)]" \
    #pbkfile="../acisf_pbk0.fits" \
    #grouptype=NUM_CTS binspec=20 \
    #verbose=5

#FAST#
    #pi: pulse invariant energy of event
punlearn dmextract
dmextract infile="../evt2_c7_srcless.fits[sky=region(ans6.reg)][bin pi]" \
outfile=src.pi \
wmap="[bin det=8]" \

punlearn mkwarf
mkwarf infile="src.pi[WMAP]" \
outfile=src.warf \
weightfile=src.wgt \
spectrumfile=none \
egridspec=0.5:11:0.01 \
pbkfile=../acisf_pbk0.fits \
threshold=0 \

punlearn mkrmf
mkrmf infile="CALDB" \
outfile=src.wrmf \
axis1="energy=0:1" \
axis2="pi=1:1024:1" \
weights=src.wgt \

#cp ../bkg.reg .
punlearn dmextract
dmextract infile= "../acis_bkg_reproj.fits[sky=region(ans6.reg)][bin pi]" \
outfile=src_bkg.pi \
wmap="[bin det=8]" \

punlearn dmgroup
dmgroup infile="src.pi[spectrum]" \
outfile=src_grp.pi \
grouptype=NUM_CTS \
xcolumn=channel \
ycolumn=counts \
binspec=20 \
grouptypeval= 15.000000 \
maxlength= 0.000000 \
clobber = yes \
verbose = 1 \

    r=`awk -F , '{print $4}' ans6.reg |tr -d ')'`
    echo $r
    dmhedit src_grp.pi filelist=none operation=add key="XFLT0001" value=$r datatype=double
    dmhedit src_grp.pi filelist=none operation=add key="XFLT0002" value=$r datatype=double
    dmhedit src_grp.pi filelist=none operation=add key="XFLT0003" value=0

    dmhedit src_grp.pi filelist=none operation=add key="BACKFILE" value="'$i/src_bkg.pi'"
    dmhedit src_grp.pi filelist=none operation=add key="ANCRFILE" value="'$i/src.warf'"
    dmhedit src_grp.pi filelist=none operation=add key="RESPFILE" value="'$i/src.wrmf'"
#dmextract "../evt2_c7_srcless.fits[energy=7000:10000][bin sky=@ans6.reg]" a.fits
#dmextract "../acis_bkg_reproj.fits[energy=7000:10000][bin sky=@ans6.reg]" b.fits
#n=`dmlist "a.fits[cols net_rate]" data|grep 1|awk '{print $2}'`
#m=`dmlist "b.fits[cols net_rate]" data|grep 1|awk '{print $2}'`
dmhedit src_grp.pi filelist=none operation=add key="BACKSCAL" value=1 datatype=double
dmhedit src_bkg.pi filelist=none operation=add key="BACKSCAL" value=1 datatype=double



cd ..
done

./spout.sh