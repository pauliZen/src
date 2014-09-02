colbias ("@4096fit.lst",
"@4096fit.lst//ol", bias="[4097:4107,*]", trim="[1:2048,*]", median=yes,
interactive=no, function="spline3", order=1, low_reject=3., high_reject=3.,
niterate=1, logfiles="", graphics="stdgraph", cursor="")

colbias ("@4096fit.lst",
"@4096fit.lst//or", bias="[4128:4138,*]", trim="[2049:4096,*]", median=yes,
interactive=no, function="spline3", order=1, low_reject=3., high_reject=3.,
niterate=1, logfiles="", graphics="stdgraph", cursor="")

imarith ("@4096fit.lst",
"-", "@4096fit.lst", "@4096fit.lst//black", title="@4096fit.lst//o", divzero=0.,
hparams="", pixtype="", calctype="", verbose=no, noact=no)

imcopy ("@4096fit.lst//ol",
"@4096fit.lst//black[1:2048,*]", verbose=yes)

imcopy ("@4096fit.lst//or",
"@4096fit.lst//black[2049:4096,*]", verbose=yes)

ccdproc ("@4096fit.lst//black",
output="@4096fit.lst//o", ccdtype="", max_cache=0, noproc=no, fixpix=no,
overscan=no, trim=yes, zerocor=no, darkcor=no, flatcor=no, illumcor=no,
fringecor=no, readcor=no, scancor=no, readaxis="line", fixfile="",
biassec=" ", trimsec="[1:4096,*]", zero="", dark="", flat="", illum="",
fringe="", minreplace=1., scantype="shortscan", nscan=1, interactive=no,
function="legendre", order=1, sample="*", naverage=1, niterate=1, low_reject=3.,
high_reject=3., grow=0.)


