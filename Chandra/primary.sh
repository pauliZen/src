#input this scripts in the first directory named obsid.

mv ./primary/* ./secondary/
cp $apw/ciao_level1_script.sh ./secondary/
rm -r primary
mv secondary/ lev2
cd ./lev2
./ciao_level1_script.sh
cd ..
mkdir light_curve
cp ./lev2/acis_dstrk_evt2.fits ./light_curve
cd light_curve
ln -sf $apw/lc_myc.sh
ln -sf $apw/lc_my.sh
ds9 acis_dstrk_evt2.fits &
emacs ccd.txt &

