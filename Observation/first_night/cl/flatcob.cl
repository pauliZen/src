normalize ("@flatd.lst",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")

imcombine ("@flatd.lst",
"flatdodc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="none", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF, hthreshold=INDEF,
nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3., rdnoise="0.",
gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)

normalize ("flatdodc.fit",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")

normalize ("@flati.lst",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")

imcombine ("@flati.lst",
"flatiodc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="none", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF, hthreshold=INDEF,
nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3., rdnoise="0.",
gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)

normalize ("flatiodc.fit",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")

normalize ("@flatm.lst",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")

imcombine ("@flatm.lst",
"flatmodc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="none", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF, hthreshold=INDEF,
nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3., rdnoise="0.",
gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)

normalize ("flatmodc.fit",
norm=INDEF, sample_secti="[]", lower=INDEF, upper=INDEF, keeplog=")_.keeplog",
logfile=")_.logfile", imfd="")
