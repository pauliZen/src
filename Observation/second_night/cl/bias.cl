imcombine ("@bias.lst",
"biasc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="", expmasks="",
sigmas="", imcmb="$I", logfile="STDOUT", combine="median", reject="none",
project=no, outtype="real", outlimits="", offsets="none", masktype="none",
maskvalue="0", blank=0., scale="none", zero="none", weight="none", statsec="",
expname="", lthreshold=INDEF, hthreshold=INDEF, nlow=1, nhigh=1, nkeep=1,
mclip=yes, lsigma=3., hsigma=3., rdnoise="0.", gain="1.", snoise="0.",
sigscale=0.1, pclip=-0.5, grow=0.)

imarith ("@flati.lst",
"-", "biasc.fit", "@flati.lst//b", title=" ", divzero=0., hparams="",
pixtype="", calctype="", verbose=no, noact=no)

normalize ("@flati.lst//b",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")

imcombine ("@flati.lst//b",
"flatibc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="none", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF, hthreshold=INDEF,
nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3., rdnoise="0.",
gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)

ccdproc ("flatibc.fit",
output="flatibct.fit", ccdtype=" ", max_cache=0, noproc=no, fixpix=no,
overscan=no, trim=yes, zerocor=no, darkcor=no, flatcor=no, illumcor=no,
fringecor=no, readcor=no, scancor=no, readaxis="line", fixfile="",
biassec=" ", trimsec="[1:4096,*]", zero="", dark="", flat="", illum="",
fringe="", minreplace=1., scantype="shortscan", nscan=1, interactive=no,
function="legendre", order=1, sample="*", naverage=1, niterate=1,
low_reject=3., high_reject=3., grow=0.)

normalize ("flatibct.fit",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")



