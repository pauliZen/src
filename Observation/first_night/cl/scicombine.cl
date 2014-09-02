!rm -f Usci*odfsec.fit

imcombine ("@Udodfse.lst//b",
"Uscidodfsebc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="@Uscaled.txt", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF,
hthreshold=INDEF, nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3.,
rdnoise="0.", gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)

imcombine ("@Uiodfse.lst//b",
"Usciiodfsebc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="@Uscalei.txt", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF,
hthreshold=INDEF, nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3.,
rdnoise="0.", gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)

imcombine ("@Umodfse.lst//b",
"Uscimodfsebc.fit", headers=" ", bpmasks="", rejmasks="", nrejmasks="",
expmasks="", sigmas="", imcmb="$I", logfile="STDOUT", combine="median",
reject="none", project=no, outtype="real", outlimits="", offsets="none",
masktype="none", maskvalue="0", blank=0., scale="@Uscalem.txt", zero="none",
weight="none", statsec="", expname="", lthreshold=INDEF,
hthreshold=INDEF, nlow=1, nhigh=1, nkeep=1, mclip=yes, lsigma=3., hsigma=3.,
rdnoise="0.", gain="1.", snoise="0.", sigscale=0.1, pclip=-0.5, grow=0.)



