/* ARWV.f -- translated by f2c (version 20090411).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal x[600], v[600], wttl, m[200], xc[600], wc[600], mc[200], xi[
	    600], vi[600], mass, rinv[19900], rsum;
    integer iname[200], n;
} dataforroutines1_;

#define dataforroutines1_1 dataforroutines1_

struct {
    doublereal mmij, cmx[3], cmv[3], energy, energr, chtime;
} dataforchainroutinestwo_;

#define dataforchainroutinestwo_1 dataforchainroutinestwo_

struct {
    doublereal ee, cmethod[3], clight;
    integer nofbh;
} softening_;

#define softening_1 softening_

struct {
    doublereal taika, timecomparison;
} timecommon_;

#define timecommon_1 timecommon_

struct {
    doublereal spin[3];
} spincommon_;

#define spincommon_1 spincommon_

union {
    struct {
	doublereal tolerance;
    } _1;
    struct {
	doublereal eps;
    } _2;
} tolerancecommon_;

#define tolerancecommon_1 (tolerancecommon_._1)
#define tolerancecommon_2 (tolerancecommon_._2)

struct {
    doublereal gamma, h__;
    integer iwr;
} diagnostics_;

#define diagnostics_1 diagnostics_

struct {
    doublereal tkin, upot, dskin, dspot;
} justforfun_;

#define justforfun_1 justforfun_

struct {
    integer index4output[200], n_ini__;
} outputindex_;

#define outputindex_1 outputindex_

struct {
    integer icollision, ione, itwo, iwarning;
} collision_;

#define collision_1 collision_

union {
    struct {
	doublereal gtime;
    } _1;
    struct {
	doublereal g;
    } _2;
} deroftime_;

#define deroftime_1 (deroftime_._1)
#define deroftime_2 (deroftime_._2)

struct {
    doublereal omec[40000]	/* was [200][200] */;
} omegacoefficients_;

#define omegacoefficients_1 omegacoefficients_

struct {
    doublereal aitemax;
    integer itemax, itemax_used__;
} itemaxcommon_;

#define itemaxcommon_1 itemaxcommon_

struct {
    doublereal rw, fr, frm, akiih[3];
} turhia_;

#define turhia_1 turhia_

struct {
    doublereal wttlinc, xcinc[600], wcinc[600], cmxinc[3], cmvinc[3], 
	    energyinc, energrinc, chtimeinc, spininc[3];
} incrementcommon_;

#define incrementcommon_1 incrementcommon_

struct {
    doublereal ww[600], wttlw, cmvw[3], spinw[3];
} vwcommon_;

#define vwcommon_1 vwcommon_

struct {
    doublereal rijnotneeded;
} notneeded_;

#define notneeded_1 notneeded_

struct {
    doublereal dv2[3], dv4[3], dv5[3];
} deeveet_;

#define deeveet_1 deeveet_

struct {
    doublereal a1, a2, a2p5, a3, a3p5, b1, b2, b2p5, b3, b3p5;
} outpa1a2ctc_;

#define outpa1a2ctc_1 outpa1a2ctc_

struct {
    doublereal zero;
} mita_;

#define mita_1 mita_

struct {
    integer ikir;
} apuindex_;

#define apuindex_1 apuindex_

struct {
    integer iei;
} eitoimi_;

#define eitoimi_1 eitoimi_

union {
    struct {
	doublereal beta, ma, mb;
	integer itoo, iw, jw, n_alku__;
    } _1;
    struct {
	doublereal betaa, ma, mb;
	integer itoo, iw, jw, n_alku__;
    } _2;
} toolarge_;

#define toolarge_1 (toolarge_._1)
#define toolarge_2 (toolarge_._2)

struct {
    integer ncfunc;
} diagno_;

#define diagno_1 diagno_

/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__5 = 5;
static integer c__9 = 9;
static doublereal c_b41 = 2.5;
static integer c__6 = 6;
static integer c__66 = 66;
static integer c__71 = 71;
static integer c__72 = 72;
static integer c__73 = 73;
static integer c__74 = 74;
static integer c__75 = 75;
static integer c__76 = 76;
static integer c__200 = 200;
static doublereal c_b243 = 3.;
static integer c__88 = 88;
static integer c__2 = 2;
static doublereal c_b341 = .666667;

/* Subroutine */ int notatallneeded_(void)
{
/*       ARCCOM2e2.CH =filename */
/* just has the ARCCOM2e2.CH */
/* the relative spin of M(1) !Spin=spin*G* */
    return 0;
} /* notatallneeded_ */

/*          IMPLICIT REAL*8 (A-H,M,O-Z) ! this is in 'ARCCOM2e2.CH' */
/*       ARCCOM.CH =filename */
/* Main program */ int MAIN__(void)
{
    /* Format strings */
    static char fmt_123[] = "(1x,\002T: \002,1p,g20.6,\002 dE/U=\002,1p,g10."
	    "2,\002 dSdot/sdotU=\002,1p,g10.2,\002   d(RxV)/Am=\002,1p,g10.2"
	    ",\002 Nb=\002,0p,1x,i3)";
    static char fmt_234[] = "(1x,f18.6,1p,600g13.5)";
    static char fmt_171[] = "(1x,f12.3,201g18.10)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;
    olist o__1;

    /* Builtin functions */
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_open(olist *);
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen);
    double log(doublereal);
    integer e_wsfe(void), s_wsle(cilist *), e_wsle(void);

    /* Local variables */
    static doublereal am_error__;
    extern /* Subroutine */ int reduce2cm_(doublereal *, doublereal *, 
	    integer *, doublereal *);
    static doublereal g[3];
    static integer i__, j, k, l;
    static doublereal g0[3];
    static integer i0, j0;
    static doublereal tolerance, ai[200], al, ei[200], qi, mw, rs, vw[3], xw[
	    3];
    extern /* Subroutine */ int constantsofmotion_(doublereal *, doublereal *,
	     doublereal *);
    static doublereal sp0;
    static integer nbh, ixc;
    static doublereal omi[200], ooi[200], moi, spa, dsp, tqi, xwr[600];
    extern /* Subroutine */ int chainevolve_(integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal cmet[3];
    extern doublereal cdot_(doublereal *, doublereal *);
    static doublereal unci[200], time, tmax, soft, cmvx[3], cmxx[3];
    static integer ksmx;
    extern /* Subroutine */ int findbinaries_(doublereal *);
    static doublereal ener0, ener1, alfai;
    extern /* Subroutine */ int flush_(integer *);
    static doublereal stepr, cangmo, deltat;
    static logical newreg;
    extern doublereal square_(doublereal *, doublereal *);
    extern /* Subroutine */ int elmnts_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer n_calls__;
    static char outfile[22];

    /* Fortran I/O blocks */
    static cilist io___3 = { 1, 5, 0, 0, 0 };
    static cilist io___14 = { 0, 5, 0, 0, 0 };
    static cilist io___28 = { 0, 6, 0, fmt_123, 0 };
    static cilist io___45 = { 0, 66, 0, fmt_234, 0 };
    static cilist io___46 = { 0, 71, 0, fmt_171, 0 };
    static cilist io___47 = { 0, 72, 0, fmt_171, 0 };
    static cilist io___48 = { 0, 73, 0, fmt_171, 0 };
    static cilist io___49 = { 0, 74, 0, fmt_171, 0 };
    static cilist io___50 = { 0, 75, 0, fmt_171, 0 };
    static cilist io___54 = { 0, 76, 0, 0, 0 };



/* the relative spin of M(1) !Spin=spin*G* */
/* used in diagno */
/* ,dum(3) */
L666:
/* jump here to start a new simulation in the same run */
    collision_1.icollision = 0;
    time = 0.f;
    deltat = 1.f;
    diagnostics_1.iwr = 1;
/*         Initial values,   UNITS:  G=1 */
/* write some info ( set -1 to not to get that..) */
    i__1 = s_rsle(&io___3);
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&diagnostics_1.iwr, (ftnlen)sizeof(
	    integer));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&dataforroutines1_1.n, (ftnlen)sizeof(
	    integer));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__1, (char *)&deltat, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__1, (char *)&tmax, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__1, (char *)&stepr, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__1, (char *)&soft, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__3, (char *)&cmet[0], (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__1, (char *)&softening_1.clight, (ftnlen)sizeof(
	    doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__9, &c__1, outfile, (ftnlen)22);
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&ixc, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&nbh, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__3, (char *)&spincommon_1.spin[0], (ftnlen)sizeof(
	    doublereal));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_lio(&c__5, &c__1, (char *)&tolerance, (ftnlen)sizeof(doublereal)
	    );
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = e_rsle();
    if (i__1 != 0) {
	goto L999;
    }
/*                                          stepr is now obsolete */

    tolerancecommon_2.eps = tolerance;
    if (dataforroutines1_1.n < 2) {
	s_stop("", (ftnlen)0);
    }
/* Computing 2nd power */
    d__1 = soft;
    softening_1.ee = d__1 * d__1;
/* square of soft(ening) */
    o__1.oerr = 0;
    o__1.ounit = 66;
    o__1.ofnmlen = 22;
    o__1.ofnm = outfile;
    o__1.orl = 0;
    o__1.osta = 0;
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    dataforroutines1_1.mass = 0.f;
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	s_rsle(&io___14);
	do_lio(&c__5, &c__1, (char *)&dataforroutines1_1.m[i__ - 1], (ftnlen)
		sizeof(doublereal));
	for (k = 1; k <= 3; ++k) {
	    do_lio(&c__5, &c__1, (char *)&dataforroutines1_1.x[l + k - 1], (
		    ftnlen)sizeof(doublereal));
	}
	for (k = 1; k <= 3; ++k) {
	    do_lio(&c__5, &c__1, (char *)&dataforroutines1_1.v[l + k - 1], (
		    ftnlen)sizeof(doublereal));
	}
	e_rsle();
	dataforroutines1_1.mass += dataforroutines1_1.m[i__ - 1];
	outputindex_1.index4output[i__ - 1] = i__;
/* initialize output index (to be modified i */
    }
    outputindex_1.n_ini__ = dataforroutines1_1.n;
    reduce2cm_(dataforroutines1_1.x, dataforroutines1_1.m, &
	    dataforroutines1_1.n, cmxx);
/* in this version output is in cm a */
    reduce2cm_(dataforroutines1_1.v, dataforroutines1_1.m, &
	    dataforroutines1_1.n, cmvx);
    for (k = 1; k <= 3; ++k) {
	cmxx[k - 1] = 0.;
	cmvx[k - 1] = 0.;
    }
    ener0 = 0.;
    newreg = TRUE_;
    ksmx = 1000000;
/* only this many steps without return */
    n_calls__ = 0;
/* removable ! */
    goto L200;
L100:
    chainevolve_(&dataforroutines1_1.n, dataforroutines1_1.x, 
	    dataforroutines1_1.v, dataforroutines1_1.m, &time, &deltat, &
	    tolerancecommon_2.eps, &newreg, &ksmx, &soft, cmet, &
	    softening_1.clight, &ixc, &nbh, spincommon_1.spin, cmxx, cmvx);
    ++n_calls__;
/* removable ! */
    if (n_calls__ > 10) {
	deltat = abs(deltat);
    }
/*               NOTE: STEP replaced with TOL (=EPS) */
/*        Diagnostics */
/* removable! */
    constantsofmotion_(&ener1, g, &al);
/*               This only works AFTER at least one call of 'chainevolve' */
/* Tkin and Upot evaluated */
    if (ener0 == 0.f) {
	ener0 = ener1;
/* INITIALIZE */
	softening_1.cmethod[2] *= abs(ener0);
/* !!! */
	g0[0] = g[0];
	g0[1] = g[1];
	g0[2] = g[2];
	cangmo = pow_dd(&dataforroutines1_1.mass, &c_b41) * sqrt(al) / abs(
		ener1);
/* Ener1 only here */
    }
    am_error__ = sqrt(square_(g, g0)) / cangmo;
    s_wsfe(&io___28);
    do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
    d__1 = log((justforfun_1.tkin - dataforchainroutinestwo_1.energy - 
	    dataforchainroutinestwo_1.energr) / justforfun_1.upot);
    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    d__2 = justforfun_1.dskin / justforfun_1.dspot - 1;
    do_fio(&c__1, (char *)&d__2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&am_error__, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&dataforroutines1_1.n, (ftnlen)sizeof(integer));
    e_wsfe();
/*  /twopi */
/* logH = the */
/* print time, logH, N (of bodies left) */
    flush_(&c__6);
L200:
    if (diagnostics_1.iwr > -2) {
	i__1 = outputindex_1.n_ini__ * 3;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xwr[i__ - 1] = 1e9f;
/* put all outside */
	}
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = outputindex_1.index4output[i__ - 1];
/* take still existing particles 2 correct indi */
	    j0 = j * 3 - 3;
	    i0 = i__ * 3 - 3;
	    for (k = 1; k <= 3; ++k) {
		xwr[j0 + k - 1] = dataforroutines1_1.x[i0 + k - 1] + cmxx[k - 
			1];
/*                          or replce cmxx(k) by  -x(k) if U want */
/*                          origin (se also subroutine MERGE_I1_I */
/* add centre-of-mass (remove cmxx if U */
	    }
/* k */
	}
/* i */
	flush_(&c__66);
    }
/*   IF YOU WANT ORBITAL ELEMENTS WITH RESPECT TO THE CENTRAL BH, activate the statements below */
/* iwr.gt.-2 */
    if (diagnostics_1.iwr > -1) {
	i__1 = outputindex_1.n_ini__;
	for (j = 2; j <= i__1; ++j) {
	    ai[j - 1] = 0.;
	    ei[j - 1] = 0.;
	    unci[j - 1] = 0.;
	    omi[j - 1] = 0.;
	    ooi[j - 1] = 0.;
	}
	i__1 = dataforroutines1_1.n;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    i0 = i__ * 3 - 3;
	    for (k = 1; k <= 3; ++k) {
		xw[k - 1] = dataforroutines1_1.x[i0 + k - 1] - 
			dataforroutines1_1.x[k - 1];
		vw[k - 1] = dataforroutines1_1.v[i0 + k - 1] - 
			dataforroutines1_1.v[k - 1];
	    }
	    mw = dataforroutines1_1.m[0] + dataforroutines1_1.m[i__ - 1];
/*       Orbital elements with respect to the central body. */
	    j = outputindex_1.index4output[i__ - 1];
	    elmnts_(xw, vw, &mw, &ai[j - 1], &ei[j - 1], &moi, &unci[j - 1], &
		    omi[j - 1], &ooi[j - 1], &alfai, &qi, &tqi);
	}
/*           if(abs(moi).gt.2.5)then */
/* i=2,N */
	s_wsfe(&io___45);
	do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	i__1 = outputindex_1.n_ini__ * 3;
	for (k = 1; k <= i__1; k += 3) {
	    do_fio(&c__1, (char *)&xwr[k - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xwr[k], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xwr[k + 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
	s_wsfe(&io___46);
	do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	i__1 = outputindex_1.n_ini__;
	for (k = 2; k <= i__1; ++k) {
	    do_fio(&c__1, (char *)&ai[k - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
/* a   write orbital eleme */
	s_wsfe(&io___47);
	do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	i__1 = outputindex_1.n_ini__;
	for (k = 2; k <= i__1; ++k) {
	    do_fio(&c__1, (char *)&ei[k - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
/* e */
	s_wsfe(&io___48);
	do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	i__1 = outputindex_1.n_ini__;
	for (k = 2; k <= i__1; ++k) {
	    do_fio(&c__1, (char *)&unci[k - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
/* i */
	s_wsfe(&io___49);
	do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	i__1 = outputindex_1.n_ini__;
	for (k = 2; k <= i__1; ++k) {
	    do_fio(&c__1, (char *)&omi[k - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
/* \Omega */
	s_wsfe(&io___50);
	do_fio(&c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	i__1 = outputindex_1.n_ini__;
	for (k = 2; k <= i__1; ++k) {
	    do_fio(&c__1, (char *)&ooi[k - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
/* \omega */
	spa = sqrt(cdot_(spincommon_1.spin, spincommon_1.spin));
	if (sp0 == 0.f) {
	    sp0 = spa;
	}
	dsp = spa - sp0;
	s_wsle(&io___54);
	do_lio(&c__5, &c__1, (char *)&time, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__3, (char *)&spincommon_1.spin[0], (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&dsp, (ftnlen)sizeof(doublereal));
	e_wsle();
/* spin(k), k=1,3 of M1  (|spin|<1) */
	flush_(&c__71);
	flush_(&c__72);
	flush_(&c__73);
	flush_(&c__74);
	flush_(&c__75);
	flush_(&c__76);
	flush_(&c__66);
/*           end if ! abs(moi)>2.5 */
	if (diagnostics_1.iwr > 1) {
	    findbinaries_(&time);
	}
/* this is usually unimpor */
    }
/* iwr>-1 */
/* Computing 2nd power */
    d__1 = softening_1.clight;
    rs = (dataforroutines1_1.m[0] + dataforroutines1_1.m[1]) * 2 / (d__1 * 
	    d__1);
    if (time < tmax) {
	goto L100;
    } else {
	goto L666;
    }
L999:
    return 0;
} /* MAIN__ */

doublereal cdot_(doublereal *a, doublereal *b)
{
    /* System generated locals */
    doublereal ret_val;

    /* Parameter adjustments */
    --b;
    --a;

    /* Function Body */
    ret_val = a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    return ret_val;
} /* cdot_ */

/* ---------------------------------------------------------- */
/*    RELEVANT ROUTINES START HERE */
/* ----------------------------------------------------------- */
/*        THIS IS THE MAIN SUBROUTINE. */
/* Subroutine */ int chainevolve_(integer *nn, doublereal *xx, doublereal *vx,
	 doublereal *mx, doublereal *time, doublereal *deltat, doublereal *
	tol, logical *newreg, integer *ksmx, doublereal *soft, doublereal *
	cmet, doublereal *cl, integer *ixc, integer *nbh, doublereal *spini, 
	doublereal *cmxx, doublereal *cmvx)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static doublereal step_now__;
    static integer i__, k;
    extern /* Subroutine */ int merge_i1_i2__(doublereal *), arc_(integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static integer knx;
    static doublereal step, wknx, tstep, tnext, tnext0;
    static integer nmerger;

/* THIS ROUTINE CHANGED TO A STAND ALONE */
/*         INCLUDE 'mergearc.inc' */
/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --cmvx;
    --cmxx;
    --spini;
    --cmet;
    --mx;
    --vx;
    --xx;

    /* Function Body */
    tnext0 = *time + *deltat;
    wknx = tnext0 / *deltat;
    knx = (integer) (tnext0 / *deltat + .1);
    tnext = knx * *deltat;
    tstep = tnext - *time;
/*        ala{humpuuki} */
/*         tstep=deltat */
/*         if(RINV(1).ne.0.0)then */
/*         tstep=tstep/(rinv(1)+rinv(2)) */
/*         tstep=max(tstep,1.e-5) */
/*         end if */
/*        loppu{humpuuki} */
    nmerger = 0;
/* no mergers yet */
L10:
    arc_(nn, &xx[1], &vx[1], &mx[1], time, &tstep, tol, newreg, ksmx, soft, &
	    cmet[1], cl, ixc, nbh, &spini[1], &cmxx[1], &cmvx[1]);

    if (step > 0.f) {
	step_now__ = step;
    }
/* save step */
    if (collision_1.icollision != 0) {
/* handle a collison */
	++nmerger;
	merge_i1_i2__(time);
/* merge the two particles */
	*newreg = TRUE_;
/* chain has changed */
	*nn = dataforroutines1_1.n;
/* copy new chain */
	i__1 = *nn;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    mx[i__] = dataforroutines1_1.m[i__ - 1];
	    for (k = 1; k <= 3; ++k) {
		xx[i__ * 3 - 3 + k] = dataforroutines1_1.x[i__ * 3 - 3 + k - 
			1];
		vx[i__ * 3 - 3 + k] = dataforroutines1_1.v[i__ * 3 - 3 + k - 
			1];
	    }
	}
/* done copying new chain */
	tstep = tnext - *time;
/* chain integration */
/* set time step to continue */
	if (abs(tstep) > *deltat * 1e-6f && *nn > 1) {
	    goto L10;
	}
    }
    step = step_now__;
/* restore the earlier step */
    return 0;
} /* chainevolve_ */

/* Subroutine */ int merge_i1_i2__(doublereal *time)
{
    /* Format strings */
    static char fmt_234[] = "(1x,f18.6,1p,600g13.5)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l, i0, j0;
    static doublereal sm[200], xr[600], xdr[600];
    static integer iwr;
    static doublereal xwr[600], ywr[600];
    static integer i1wr, i2wr;
    static doublereal mkax, myks;
    extern /* Subroutine */ int flush_(integer *);
    static integer i_delay__;

    /* Fortran I/O blocks */
    static cilist io___75 = { 0, 66, 0, fmt_234, 0 };
    static cilist io___76 = { 0, 66, 0, fmt_234, 0 };
    static cilist io___85 = { 0, 6, 0, 0, 0 };
    static cilist io___86 = { 0, 67, 0, 0, 0 };
    static cilist io___87 = { 0, 6, 0, 0, 0 };


/* time only for write(66.... */
/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/* --------------------------------------------4 MOVIE ------------------------- */
    if (iwr > -2) {
/* Set IWR=-2 if you do not want this */
	i__1 = outputindex_1.n_ini__ * 3;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xwr[i__ - 1] = 1e9f;
	}
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = outputindex_1.index4output[i__ - 1];
	    j0 = j * 3 - 3;
	    i0 = i__ * 3 - 3;
	    for (k = 1; k <= 3; ++k) {
		xwr[j0 + k - 1] = dataforroutines1_1.x[i0 + k - 1] + 
			dataforchainroutinestwo_1.cmx[k - 1];
		ywr[j0 + k - 1] = xwr[j0 + k - 1];
		if (i__ == collision_1.ione || i__ == collision_1.itwo) {
		    ywr[j0 + k - 1] = 1e9f;
		}
/* this moves the body */
	    }
/* k */
	}
/* i */
	for (i_delay__ = 1; i_delay__ <= 33; ++i_delay__) {
/* make the movie flash in case of a merger */
	    s_wsfe(&io___75);
	    do_fio(&c__1, (char *)&(*time), (ftnlen)sizeof(doublereal));
	    i__1 = outputindex_1.n_ini__ * 3;
	    for (k = 1; k <= i__1; k += 3) {
		do_fio(&c__1, (char *)&xwr[k - 1], (ftnlen)sizeof(doublereal))
			;
		do_fio(&c__1, (char *)&xwr[k], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&xwr[k + 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_wsfe();
	    s_wsfe(&io___76);
	    do_fio(&c__1, (char *)&(*time), (ftnlen)sizeof(doublereal));
	    i__1 = outputindex_1.n_ini__ * 3;
	    for (k = 1; k <= i__1; k += 3) {
		do_fio(&c__1, (char *)&ywr[k - 1], (ftnlen)sizeof(doublereal))
			;
		do_fio(&c__1, (char *)&ywr[k], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ywr[k + 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_wsfe();
	}
	flush_(&c__66);
    }
/* -------------------------------------------------------------------------------- */
/* iwr.gt.-2 */
    l = 0;
    i__1 = collision_1.ione - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sm[i__ - 1] = dataforroutines1_1.m[i__ - 1];
	for (k = 1; k <= 3; ++k) {
	    xr[i__ * 3 - 3 + k - 1] = dataforroutines1_1.x[i__ * 3 - 3 + k - 
		    1];
	    xdr[i__ * 3 - 3 + k - 1] = dataforroutines1_1.v[i__ * 3 - 3 + k - 
		    1];
	}
    }
    myks = dataforroutines1_1.m[collision_1.ione - 1];
    mkax = dataforroutines1_1.m[collision_1.itwo - 1];
    sm[collision_1.ione - 1] = dataforroutines1_1.m[collision_1.ione - 1] + 
	    dataforroutines1_1.m[collision_1.itwo - 1];
    for (k = 1; k <= 3; ++k) {
	xr[collision_1.ione * 3 - 3 + k - 1] = (dataforroutines1_1.m[
		collision_1.ione - 1] * dataforroutines1_1.x[(
		collision_1.ione - 1) * 3 + k - 1] + dataforroutines1_1.m[
		collision_1.itwo - 1] * dataforroutines1_1.x[(
		collision_1.itwo - 1) * 3 + k - 1]) / sm[collision_1.ione - 1]
		;
	xdr[collision_1.ione * 3 - 3 + k - 1] = (dataforroutines1_1.m[
		collision_1.ione - 1] * dataforroutines1_1.v[(
		collision_1.ione - 1) * 3 + k - 1] + dataforroutines1_1.m[
		collision_1.itwo - 1] * dataforroutines1_1.v[(
		collision_1.itwo - 1) * 3 + k - 1]) / sm[collision_1.ione - 1]
		;
/* L6: */
    }
    i__1 = collision_1.itwo - 1;
    for (i__ = collision_1.ione + 1; i__ <= i__1; ++i__) {
	sm[i__ - 1] = dataforroutines1_1.m[i__ - 1];
	for (k = 1; k <= 3; ++k) {
	    xr[i__ * 3 - 3 + k - 1] = dataforroutines1_1.x[i__ * 3 - 3 + k - 
		    1];
	    xdr[i__ * 3 - 3 + k - 1] = dataforroutines1_1.v[i__ * 3 - 3 + k - 
		    1];
	}
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = collision_1.itwo; i__ <= i__1; ++i__) {
	outputindex_1.index4output[i__ - 1] = outputindex_1.index4output[i__];
    }
    i__1 = dataforroutines1_1.n;
    for (i__ = collision_1.itwo + 1; i__ <= i__1; ++i__) {
	sm[i__ - 2] = dataforroutines1_1.m[i__ - 1];
	for (k = 1; k <= 3; ++k) {
	    xr[i__ * 3 - 6 + k - 1] = dataforroutines1_1.x[i__ * 3 - 3 + k - 
		    1];
	    xdr[i__ * 3 - 6 + k - 1] = dataforroutines1_1.v[i__ * 3 - 3 + k - 
		    1];
	}
    }
/*         MOVE THE REDUCED SYSTEM TO M,X,V */
    l = 0;
/*         New value of the number of bodies. */
    --dataforroutines1_1.n;
    if (collision_1.itwo <= softening_1.nofbh) {
	--softening_1.nofbh;
    }
/* # of BH's reduced! */
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dataforroutines1_1.m[i__ - 1] = sm[i__ - 1];
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.x[i__ * 3 - 3 + k - 1] = xr[i__ * 3 - 3 + k - 
		    1];
	    dataforroutines1_1.v[i__ * 3 - 3 + k - 1] = xdr[i__ * 3 - 3 + k - 
		    1];
/* L7: */
	}
/* L8: */
    }
    collision_1.icollision = 0;
    i1wr = outputindex_1.index4output[collision_1.ione - 1];
    i2wr = outputindex_1.index4output[collision_1.itwo - 1];
/* ?? wrong ?? because already change */
    s_wsle(&io___85);
    do_lio(&c__9, &c__1, " Merge:", (ftnlen)7);
    do_lio(&c__3, &c__1, (char *)&i1wr, (ftnlen)sizeof(integer));
    i__1 = i2wr - 1;
    do_lio(&c__3, &c__1, (char *)&i__1, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, "  N, NBH=", (ftnlen)9);
    do_lio(&c__3, &c__1, (char *)&dataforroutines1_1.n, (ftnlen)sizeof(
	    integer));
    do_lio(&c__3, &c__1, (char *)&softening_1.nofbh, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, " masses ", (ftnlen)8);
    do_lio(&c__5, &c__1, (char *)&myks, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&mkax, (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___86);
    do_lio(&c__9, &c__1, " merge ", (ftnlen)7);
    do_lio(&c__3, &c__1, (char *)&collision_1.ione, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&collision_1.itwo, (ftnlen)sizeof(integer));
    e_wsle();
    collision_1.ione = 0;
    collision_1.itwo = 0;
    if (dataforroutines1_1.n == 1) {
	s_wsle(&io___87);
	do_lio(&c__9, &c__1, " Only one body left!", (ftnlen)20);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    return 0;
} /* merge_i1_i2__ */

/* Subroutine */ int arc_(integer *nn, doublereal *xx, doublereal *vx, 
	doublereal *mx, doublereal *time, doublereal *deltat, doublereal *tol,
	 logical *newreg, integer *ksmx, doublereal *soft, doublereal *cmet, 
	doublereal *cl, integer *ixc, integer *nbh, doublereal *spini, 
	doublereal *cmxx, doublereal *cmvx)
{
    /* Initialized data */

    static integer ntrue = 0;
    static integer nfalse = 0;
    static integer nwritten = 0;

    /* Format strings */
    static char fmt_1232[] = "(1x,g12.4,\002 I-CHAIN\002,20i3)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    extern /* Subroutine */ int initialstepsize_(doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *);
    static integer i_switch__;
    extern /* Subroutine */ int findchainindices_(void);
    static integer i__, j, k;
    static doublereal y[1500];
    extern /* Subroutine */ int omegacoef_(void), estimatestepsize_(
	    doublereal *, doublereal *);
    static doublereal d1, d2, g0[3], f1, f2;
    extern /* Subroutine */ int iterate2exacttime_(doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), 
	    checkswitchingconditions_(logical *);
    static doublereal x1, x2;
    extern doublereal wfunction_(void);
    extern /* Subroutine */ int initializexcandwc_(void);
    static integer kw;
    static doublereal sy[1500];
    extern /* Subroutine */ int constantsofmotion_(doublereal *, doublereal *,
	     doublereal *);
    static logical mustswitch;
    extern /* Subroutine */ int putytoxcwc_(doublereal *, integer *);
    static doublereal dlt, stw;
    extern /* Subroutine */ int updatexandv_(void);
    static doublereal alag;
    extern /* Subroutine */ int chaintransformation_(void);
    static integer nvar;
    static doublereal yold[1500], step, mmss, cht_0__, step2;
    static integer ncall;
    static doublereal s_old__, stime;
    static integer nzero;
    extern /* Subroutine */ int takeyfromxcwc_(doublereal *, integer *);
    static doublereal dltime, stimex;
    static integer ksteps;
    extern /* Subroutine */ int obtainorderofy_(doublereal *), difsyab_(
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *);

    /* Fortran I/O blocks */
    static cilist io___91 = { 0, 6, 0, 0, 0 };
    static cilist io___92 = { 0, 6, 0, 0, 0 };
    static cilist io___93 = { 0, 6, 0, 0, 0 };
    static cilist io___94 = { 0, 6, 0, 0, 0 };
    static cilist io___95 = { 0, 6, 0, 0, 0 };
    static cilist io___96 = { 0, 6, 0, 0, 0 };
    static cilist io___97 = { 0, 6, 0, 0, 0 };
    static cilist io___98 = { 0, 6, 0, 0, 0 };
    static cilist io___99 = { 0, 6, 0, 0, 0 };
    static cilist io___100 = { 0, 6, 0, 0, 0 };
    static cilist io___101 = { 0, 6, 0, 0, 0 };
    static cilist io___102 = { 0, 6, 0, 0, 0 };
    static cilist io___103 = { 0, 6, 0, 0, 0 };
    static cilist io___104 = { 0, 6, 0, 0, 0 };
    static cilist io___105 = { 0, 6, 0, 0, 0 };
    static cilist io___106 = { 0, 6, 0, 0, 0 };
    static cilist io___110 = { 0, 6, 0, 0, 0 };
    static cilist io___111 = { 0, 6, 0, 0, 0 };
    static cilist io___112 = { 0, 6, 0, fmt_1232, 0 };
    static cilist io___133 = { 0, 6, 0, fmt_1232, 0 };
    static cilist io___142 = { 0, 6, 0, 0, 0 };


/*        BETTER TO USE CM-coords & vels for XX & VX and CMXX CMVX */
/*        FOR CM-position (needed in the Perturbations routine). */
/* ----------------------------------------------------------------- */
/*        NOTE: some variables (eg. Energy and EnerGR are only in the */
/*        common. The internal NB-energy = ENERGY+EnerGR  (should be) */
/*        Energy= integrated E-value (excluding grav.radiation) */
/*        EnerGr= Energy radiated away (grav.radiation if Clight.ne.0.0) */
/*        CHAIN INTEGRATION. Perturbations & CM-motion included (in principle). */
/*        NN=# of bodies; XX=(cm)coords, VX=(cm)vels, MX=masses, */
/* c        CMXX=coords of CM, CMVX=vels of CM ! removed */
/*        TIME=time, dettaT=time interval */
/*        STEP=stepsize (set=0 initially) */
/*        NEWREG=.true. iff chain membership has changed */
/*        KSMX=max # of steps without return (use some large # ) */
/*        soft =optional softening( U=1/sqrt(r**2+soft**2) ) */
/*        cmet= 3-d vector that determines the method: */
/*         (1,0,0) =logH, (0,1,0)=TTL,(0,0,1)=DIFSY2 without t-tranformation */

/*        cl=speed of light */
/*        NOTE: cl=0 => no relativistic terms !!! */
/*        Ixc = 1 => exact time, =0 no exact time but return after CHTIME>DELTAT */
/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --cmvx;
    --cmxx;
    --spini;
    --cmet;
    --mx;
    --vx;
    --xx;

    /* Function Body */
/*          Initial constants of motion */
    if (*newreg) {
	++ntrue;
    } else {
	++nfalse;
    }
    if (ntrue > nfalse + 10 && nwritten == 0) {
	nwritten = 1;
	s_wsle(&io___91);
	do_lio(&c__9, &c__1, "\a", (ftnlen)1);
	do_lio(&c__9, &c__1, "\a", (ftnlen)1);
	e_wsle();
	s_wsle(&io___92);
	do_lio(&c__9, &c__1, " NEWREG should be set .TRUE. only", (ftnlen)33);
	e_wsle();
	s_wsle(&io___93);
	do_lio(&c__9, &c__1, " in the very beginning of a new simulation", (
		ftnlen)42);
	e_wsle();
	s_wsle(&io___94);
	do_lio(&c__9, &c__1, " NOT at every step!! (May reduce accuracy!!)", (
		ftnlen)44);
	e_wsle();
	s_wsle(&io___95);
	do_lio(&c__9, &c__1, " even if it may look like the contrary.", (
		ftnlen)39);
	e_wsle();
    }
    if (*nn > 200) {
	s_wsle(&io___96);
	do_lio(&c__9, &c__1, " THIS CODE CAN HANDLE ONLY ", (ftnlen)27);
	do_lio(&c__3, &c__1, (char *)&c__200, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, " BODIES ", (ftnlen)8);
	e_wsle();
	s_wsle(&io___97);
	do_lio(&c__9, &c__1, " Yuo are trying to use N=", (ftnlen)25);
	do_lio(&c__3, &c__1, (char *)&(*nn), (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___98);
	do_lio(&c__9, &c__1, " Try increasing NMX in ARCCOM2e2.CH ", (ftnlen)
		36);
	e_wsle();
	s_wsle(&io___99);
	do_lio(&c__9, &c__1, " and increase some (large) dimensions elsewhere"
		, (ftnlen)47);
	e_wsle();
	s_wsle(&io___100);
	do_lio(&c__9, &c__1, " in the same proportion.  STOPPING", (ftnlen)34)
		;
	e_wsle();
	s_stop("", (ftnlen)0);
    }
/*           if(cmet(1).eq.0.0 .and. cmet(2).ne.0.0)then */
/*           write(6,*)' In this version cmethod(1) should not  be zero' */
/*           write(6,*)' if cmethod(2).ne.0.0 ' */
/*           write(6,*)cmet,' = cmethod(k),k=1,3 ' */
/*           write(6,*)' STOPPING ' */
/*           STOP */
/*           end if */
    if (*deltat == 0.f && *ixc == 1) {
	s_wsle(&io___101);
	do_lio(&c__9, &c__1, " You cannot use DELTA=0 and Ixc=1 ", (ftnlen)34)
		;
	e_wsle();
	s_wsle(&io___102);
	do_lio(&c__9, &c__1, " since then every output will be at time=0 ", (
		ftnlen)43);
	e_wsle();
	s_wsle(&io___103);
	do_lio(&c__9, &c__1, " STOPPING ", (ftnlen)10);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    if (cmet[1] + cmet[2] + cmet[3] == 0.f) {
	s_wsle(&io___104);
	do_lio(&c__9, &c__1, " You have not defined the time-transformation", 
		(ftnlen)45);
	e_wsle();
	s_wsle(&io___105);
	do_lio(&c__5, &c__3, (char *)&cmet[1], (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, " = cmethod(k),k=1,3 ", (ftnlen)20);
	e_wsle();
	s_wsle(&io___106);
	do_lio(&c__9, &c__1, " STOPPING ", (ftnlen)10);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    dataforchainroutinestwo_1.chtime = 0.f;
    collision_1.icollision = 0;
    timecommon_1.taika = *time;
/* to common */
    softening_1.nofbh = *nbh;
/* - " - */
    if (*newreg) {
/*           step=0 */
	collision_1.iwarning = 0;
	itemaxcommon_1.itemax = 12;
	itemaxcommon_1.itemax_used__ = 0;
/* Computing 2nd power */
	d__1 = *soft;
	softening_1.ee = d__1 * d__1;
/* to common */
	for (k = 1; k <= 3; ++k) {
	    spincommon_1.spin[k - 1] = spini[k];
/* SPIN */
	    softening_1.cmethod[k - 1] = cmet[k];
/* -"- */
	}
	softening_1.clight = *cl;
/* -"- */
	dataforroutines1_1.n = *nn;
	dataforroutines1_1.mass = 0.;
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dataforroutines1_1.m[i__ - 1] = mx[i__];
	    dataforroutines1_1.mass += dataforroutines1_1.m[i__ - 1];
	}
	dataforchainroutinestwo_1.mmij = 0.f;
	i__1 = dataforroutines1_1.n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = dataforroutines1_1.n;
	    for (j = i__ + 1; j <= i__2; ++j) {
		dataforchainroutinestwo_1.mmij += dataforroutines1_1.m[i__ - 
			1] * dataforroutines1_1.m[j - 1];
	    }
	}
	dataforchainroutinestwo_1.mmij /= dataforroutines1_1.n * (
		dataforroutines1_1.n - 1) / 2.;
	i__1 = dataforroutines1_1.n * 3;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dataforroutines1_1.x[i__ - 1] = xx[i__];
	    dataforroutines1_1.v[i__ - 1] = vx[i__];
	}
	if (dataforchainroutinestwo_1.mmij == 0.f) {
	    s_wsle(&io___110);
	    do_lio(&c__9, &c__1, "You have at most one non-zero mass => t'=1"
		    "/0 and", (ftnlen)48);
	    e_wsle();
	    s_wsle(&io___111);
	    do_lio(&c__9, &c__1, "this does not work", (ftnlen)18);
	    e_wsle();
	    s_stop("", (ftnlen)0);
	}
	findchainindices_();
	if (diagnostics_1.iwr > 0) {
	    s_wsfe(&io___112);
	    do_fio(&c__1, (char *)&(*time), (ftnlen)sizeof(doublereal));
	    i__1 = dataforroutines1_1.n;
	    for (kw = 1; kw <= i__1; ++kw) {
		do_fio(&c__1, (char *)&dataforroutines1_1.iname[kw - 1], (
			ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	}
	initializexcandwc_();
	constantsofmotion_(&dataforchainroutinestwo_1.energy, g0, &alag);
	dataforchainroutinestwo_1.energr = 0.;
/* energy radiated away */
	deroftime_1.gtime = 1 / alag;
	for (k = 1; k <= 3; ++k) {
	    dataforchainroutinestwo_1.cmx[k - 1] = cmxx[k];
	    dataforchainroutinestwo_1.cmv[k - 1] = cmvx[k];
	}
	omegacoef_();
	stime = 0.f;
	*newreg = FALSE_;
	dataforroutines1_1.wttl = wfunction_();
	mmss = 0.;
	i__1 = dataforroutines1_1.n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = dataforroutines1_1.n;
	    for (j = i__ + 1; j <= i__2; ++j) {
		mmss += dataforroutines1_1.m[i__ - 1] * dataforroutines1_1.m[
			j - 1];
	    }
	}
	takeyfromxcwc_(y, &nvar);
	i__1 = nvar;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    sy[i__ - 1] = 0.;
	}
	if (step == 0.f) {
	    initialstepsize_(dataforroutines1_1.x, dataforroutines1_1.v, 
		    dataforroutines1_1.m, &dataforroutines1_1.n, &
		    softening_1.ee, &step);
	}
/* New */
	stimex = step;
	tolerancecommon_2.eps = *tol;
	ncall = 0;
    }
/* NEWREG */
    ksteps = 0;
    nzero = 0;
    stw = stimex;
/* Computing MIN */
    d__1 = abs(step), d__2 = abs(stimex) * 2;
    step = min(d__1,d__2);
    stimex = 0.;
L777:
    ++ksteps;
    takeyfromxcwc_(y, &nvar);
    obtainorderofy_(sy);
    stime = 0.;
    f1 = dataforchainroutinestwo_1.chtime - *deltat;
/* for exact time */
    d1 = deroftime_1.gtime;
    dltime = -f1;
    takeyfromxcwc_(yold, &nvar);
    difsyab_(&nvar, &tolerancecommon_2.eps, sy, &step, &stime, y);
    i_switch__ = 1;
    putytoxcwc_(y, &nvar);
    if (step == 0.f) {
	s_stop("", (ftnlen)0);
    }
    checkswitchingconditions_(&mustswitch);
    if (mustswitch) {
	i_switch__ = 0;
	chaintransformation_();

	dataforroutines1_1.wttl = wfunction_();
/* this may not be necessary, but probably O */
	takeyfromxcwc_(y, &nvar);
	if (diagnostics_1.iwr > 0) {
	    s_wsfe(&io___133);
	    d__1 = *time + dataforchainroutinestwo_1.chtime;
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    i__1 = dataforroutines1_1.n;
	    for (kw = 1; kw <= i__1; ++kw) {
		do_fio(&c__1, (char *)&dataforroutines1_1.iname[kw - 1], (
			ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	}
    }
/* MUST SWITCH */
    f2 = dataforchainroutinestwo_1.chtime - *deltat;
/* for exact time itera */
    d2 = deroftime_1.gtime;
    x1 = -stime;
    x2 = 0.f;
    dlt = *deltat;
/* for short */
    if (dataforchainroutinestwo_1.chtime < dlt && ksteps < *ksmx && 
	    collision_1.icollision == 0) {
	goto L777;
    }
    if (ksteps < *ksmx && *ixc > 0 && collision_1.icollision == 0) {
/* Integrate TO approximate EXACT OUTPUTTIME */
	if (*ixc == 1) {
/* approx outputtime with Stumpff-Weiss-prici */
	    if (abs(f1) < abs(f2) * i_switch__) {
/*           if(1.eq.2)then */
/* I_switch prevents use of */
		putytoxcwc_(yold, &nvar);
		obtainorderofy_(sy);
		d__1 = -f1;
		estimatestepsize_(&d__1, &step2);
		cht_0__ = dataforchainroutinestwo_1.chtime;
		s_old__ = step2;
		difsyab_(&nvar, &tolerancecommon_2.eps, sy, &step2, &stime, 
			yold);
		putytoxcwc_(yold, &nvar);
	    } else {
		d__1 = -f2;
		estimatestepsize_(&d__1, &step2);
		obtainorderofy_(sy);
		cht_0__ = dataforchainroutinestwo_1.chtime;
		s_old__ = step2;
		difsyab_(&nvar, &tolerancecommon_2.eps, sy, &step2, &stime, y)
			;
		putytoxcwc_(y, &nvar);
	    }
	    stimex += stime;
/* 4 estimating max next step */
	} else if (*ixc == 2) {
/* Iteration to exact time */
	    iterate2exacttime_(y, &nvar, deltat, &f1, &d1, &f2, &d2, &x1, &x2)
		    ;
	}
    }
    if (stimex == 0.f) {
	stimex = step;
    }
    updatexandv_();
    i__1 = dataforroutines1_1.n * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xx[i__] = dataforroutines1_1.x[i__ - 1];
	vx[i__] = dataforroutines1_1.v[i__ - 1];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	spini[i__] = spincommon_1.spin[i__ - 1];
	cmxx[i__] = dataforchainroutinestwo_1.cmx[i__ - 1];
	cmvx[i__] = dataforchainroutinestwo_1.cmv[i__ - 1];
    }
    *time += dataforchainroutinestwo_1.chtime;
    if (dataforchainroutinestwo_1.chtime < 0.f) {
	s_wsle(&io___142);
	do_lio(&c__5, &c__1, (char *)&(*time), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&dataforchainroutinestwo_1.chtime, (
		ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "  t  cht <0!", (ftnlen)12);
	e_wsle();
    }
    return 0;
} /* arc_ */

/* Subroutine */ int iterate2exacttime_(doublereal *y0, integer *nvar, 
	doublereal *deltat, doublereal *f1, doublereal *d1, doublereal *f2, 
	doublereal *d2, doublereal *x1, doublereal *x2)
{
    /* Initialized data */

    static doublereal tiny = 1e-6;

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer i__, k;
    static doublereal y[1500];
    static integer iskeleita;
    static doublereal tolerance, hs;
    static integer it;
    static doublereal sy[1500], dx1, dx2;
    extern /* Subroutine */ int putytoxcwc_(doublereal *, integer *), 
	    updatexandv_(void);
    static doublereal fnew, step, test, xnew, dfnew, stime, sfinal, steppi;
    extern /* Subroutine */ int obtainorderofy_(doublereal *), difsyab_(
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *);

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --y0;

    /* Function Body */
    iskeleita = 0;
    it = 0;
    hs = (d__1 = *x1 - *x2, abs(d__1));
L1111:
    ++it;
    i__1 = *nvar;
    for (i__ = 1; i__ <= i__1; ++i__) {
	y[i__ - 1] = y0[i__];
    }
    stime = 0.;
    dx1 = -(*f1) / *d1;
    dx2 = -(*f2) / *d2;
    if (abs(dx1) < abs(dx2)) {
	xnew = *x1 + dx1;
    } else {
	xnew = *x2 + dx2;
    }

    test = (*x1 - xnew) * (xnew - *x2);
    if (test < -tiny * hs || it + 1 == (it + 1) / 5 * 5) {
	xnew = (*x1 + *x2) / 2;
/* bisect if out of interval */
    }
    sfinal = xnew;
    putytoxcwc_(y, nvar);
/* -------------------------------------------------------------------------- */
    obtainorderofy_(sy);
    tolerancecommon_2.eps = tolerance;
/* in common */
    steppi = 0.;
    for (k = 1; k <= 5; ++k) {
	step = sfinal - stime;
	if (abs(step) > abs(hs) * .001f || k == 1) {
/* !!! */
	    steppi = step;
	    difsyab_(nvar, &tolerancecommon_2.eps, sy, &step, &stime, y);
	    ++iskeleita;
/*                   it=it+1 */
	} else {
	    goto L222;
	}
    }
L222:
    putytoxcwc_(y, nvar);
    updatexandv_();
    fnew = dataforchainroutinestwo_1.chtime - *deltat;
    dfnew = deroftime_1.gtime;
/*         keep it bracketed */
    if (*f1 * fnew <= 0.f) {
	*f2 = fnew;
	*d2 = dfnew;
	*x2 = xnew;
    } else {
	*f1 = fnew;
	*d1 = dfnew;
	*x1 = xnew;
    }
    if ((d__1 = *deltat - dataforchainroutinestwo_1.chtime, abs(d__1)) > *
	    deltat * .001f && it < 100) {
	goto L1111;
    }
/* ONE FINAL STEP SHOULD BE HERE (if above not-so-accurate test) */
/* -------------------------------------------------------------------- */
    i__1 = *nvar;
    for (i__ = 1; i__ <= i__1; ++i__) {
	y0[i__] = y[i__ - 1];
    }
    putytoxcwc_(y, nvar);
    updatexandv_();
    return 0;
} /* iterate2exacttime_ */

/* Subroutine */ int leapfrog_(doublereal *step, integer *leaps, doublereal *
	stime)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    extern /* Subroutine */ int wcmotion_(doublereal *), xcmotion_(doublereal 
	    *);
    static integer k;
    static doublereal h2, hs;
    extern /* Subroutine */ int putv2w_(void);

    putv2w_();
    hs = *step;
    h2 = hs / 2;
    xcmotion_(&h2);
    *stime += h2;
    i__1 = *leaps - 1;
    for (k = 1; k <= i__1; ++k) {
	wcmotion_(&hs);
	xcmotion_(&hs);
	*stime += hs;
    }
    wcmotion_(&hs);
    xcmotion_(&h2);
    *stime += h2;
    return 0;
} /* leapfrog_ */

doublereal wfunction_(void)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal rij, omega;
    extern doublereal square_(doublereal *, doublereal *);

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    omega = 0.;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = dataforroutines1_1.n;
	for (j = i__ + 1; j <= i__2; ++j) {
	    if (omegacoefficients_1.omec[i__ + j * 200 - 201] != 0.f) {
		rij = sqrt(square_(&dataforroutines1_1.x[i__ * 3 - 3], &
			dataforroutines1_1.x[j * 3 - 3]));
		omega += omegacoefficients_1.omec[i__ + j * 200 - 201] / rij;
	    }
	}
    }
    ret_val = omega;
    return ret_val;
} /* wfunction_ */

/* Subroutine */ int omegacoef_(void)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i__, j, icount;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    icount = 0;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = dataforroutines1_1.n;
	for (j = i__ + 1; j <= i__2; ++j) {
/*        if(1.e-3*mmij.gt.m(i)*m(j).and.cmethod(2).ne.0.0)then */
	    if (dataforroutines1_1.m[i__ - 1] + dataforroutines1_1.m[j - 1] > 
		    0.f && softening_1.cmethod[1] != 0.f) {
		omegacoefficients_1.omec[i__ + j * 200 - 201] = 
			dataforchainroutinestwo_1.mmij;
		omegacoefficients_1.omec[j + i__ * 200 - 201] = 
			dataforchainroutinestwo_1.mmij;
		++icount;
	    } else {
		omegacoefficients_1.omec[i__ + j * 200 - 201] = 0.;
		omegacoefficients_1.omec[j + i__ * 200 - 201] = 0.;
	    }
	}
    }
    if ((real) icount == 0.f) {
	softening_1.cmethod[1] = 0.;
    }
/* all terms zero anyway */
    return 0;
} /* omegacoef_ */

/* Subroutine */ int xcmotion_(doublereal *hs)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, k, l, i0;
    extern /* Subroutine */ int evaluatev_(doublereal *, doublereal *);
    static doublereal dt, te;

    /* Fortran I/O blocks */
    static cilist io___175 = { 0, 6, 0, 0, 0 };


/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    te = -dataforchainroutinestwo_1.energy - dataforchainroutinestwo_1.energr;
    if (softening_1.cmethod[0] != 0.) {
	evaluatev_(dataforroutines1_1.v, dataforroutines1_1.wc);
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i0 = i__ * 3 - 3;
/* Computing 2nd power */
	    d__1 = dataforroutines1_1.v[i0];
/* Computing 2nd power */
	    d__2 = dataforroutines1_1.v[i0 + 1];
/* Computing 2nd power */
	    d__3 = dataforroutines1_1.v[i0 + 2];
	    te += dataforroutines1_1.m[i__ - 1] * (d__1 * d__1 + d__2 * d__2 
		    + d__3 * d__3) / 2;
	}
    }
/* cmethod(1).ne.0.0d0 */
    deroftime_2.g = 1 / (te * softening_1.cmethod[0] + 
	    dataforroutines1_1.wttl * softening_1.cmethod[1] + 
	    softening_1.cmethod[2]);
/* = t' */
    if (deroftime_2.g < 0.f && diagnostics_1.iwr > 0) {
	s_wsle(&io___175);
	d__1 = 1 / deroftime_2.g;
	do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, " tdot <0 ! ", (ftnlen)11);
	e_wsle();
	return 0;
/* seriously wrong, but may work (this step gets rejected) */
    }
    dt = *hs * deroftime_2.g;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    incrementcommon_1.xcinc[l + k - 1] += dataforroutines1_1.wc[l + k 
		    - 1] * dt;
	    dataforroutines1_1.xc[l + k - 1] += dataforroutines1_1.wc[l + k - 
		    1] * dt;
	}
    }
    incrementcommon_1.chtimeinc += dt;
    dataforchainroutinestwo_1.chtime += dt;
    for (k = 1; k <= 3; ++k) {
	incrementcommon_1.cmxinc[k - 1] += dt * dataforchainroutinestwo_1.cmv[
		k - 1];
	dataforchainroutinestwo_1.cmx[k - 1] += dt * 
		dataforchainroutinestwo_1.cmv[k - 1];
    }
    return 0;
} /* xcmotion_ */

/* Subroutine */ int putv2w_(void)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	vwcommon_1.ww[i__ - 1] = dataforroutines1_1.wc[i__ - 1];
    }
    vwcommon_1.wttlw = dataforroutines1_1.wttl;
    for (k = 1; k <= 3; ++k) {
	vwcommon_1.spinw[k - 1] = spincommon_1.spin[k - 1];
	vwcommon_1.cmvw[k - 1] = dataforchainroutinestwo_1.cmv[k - 1];
    }
    return 0;
} /* putv2w_ */

/* Subroutine */ int coordinatedependentperturbations_(doublereal *acc)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal);

    /* Local variables */
    static doublereal truetime;
    static integer i__, k;
    static doublereal s, s1, s2;
    static integer ic, ki;
    static doublereal rr;
    static integer ic0;
    extern doublereal t0p_(integer *);
    static doublereal rrr;
    static integer npertur;

/* USER DEFINED */
/*    IN STAND-ALONE-MODE THIS ROUTINE SIMPLY SETS: ACC(I)=0 */
/* ---  added common blocks in include file */
/*        common/perturbers/MP(100),XP(300),NPertur ! this MUST be changed by user */
/*        INCLUDE 'chaininterface.inc' */
/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/* ,dx(3)!,xppred(3,NPMX)   ! NMAX comes from inc-fil */
/*       HERE ONE MUST EVALUATE THE ACCELERATIONS DUE TO THE PERTURBERS. */
/*       Physical positions and velocities (in the inertial coordinate) */
/*       system are in vectors X and V */
/*       (X(1)=X_1,X(2)=Y_1,X(3)=Z_1, X(4)=X_2, X(5)=Y_2,...) */
/*       After a call to this routine the EXAccerations */
/*       are assumed to be in the vector ACC. */
    /* Parameter adjustments */
    --acc;

    /* Function Body */
    truetime = timecommon_1.taika + dataforchainroutinestwo_1.chtime;
/*                               ! note: chtime is measured from the beginning of this CHAIN call */
/*           these times are in common */
/* ---  init acc */
/* this is (?) the time to be used to obt */
    i__1 = dataforroutines1_1.n * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ki = i__ - (i__ - 1) / 3 * 3;
	acc[i__] = 0.;
/* -1.d-1*(x(i)+cmx(ki)) ! (test only) REMOVE this and R */
    }
    if (FALSE_) {
/*        This is an example only: */
/* THIS MUST BE REMOVED FOR REAL USE */
	i__1 = dataforroutines1_1.n;
	for (ic = 1; ic <= i__1; ++ic) {
/* ic= chainparticle index */
	    ic0 = ic * 3 - 3;
	    i__2 = npertur;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/* i=perturber index */
		s = truetime - t0p_(&i__);
/* this is the step size */
		s1 = s * .5;
/* and some multiples of it */
		s2 = s / 3.;
/* as used in the predictor */
		rr = 0.;
		for (k = 1; k <= 3; ++k) {
/* ---  here comes the predictor */
/*                 xppred(k,i) =  ((fpdot(k,i)*S2 + fp(k,i))*S1 */
/*     $                         +  vp(k,i))*S   + xp(k,i) */
/* ---  and predicted distance to chain particle */
/*                 dx(k)=X(ic0+k)-xppred(k,i) */
/*                 rr=rr+dx(k)**2 */
/* coordinate index */
		}
/* k */
		d__1 = rr + softening_1.ee;
		rrr = sqrt(pow_dd(&d__1, &c_b243));
		for (k = 1; k <= 3; ++k) {
/*                 ACC(ic0+k)=ACC(ic0+k)-MP(I)/rrr*dx(k) ! hope this is correct (not confirmed) */
		}
/* k */
	    }
/* i */
	}
/* ic */
    }
/* 1.eq.2 */
    return 0;
} /* coordinatedependentperturbations_ */

/* Subroutine */ int velocitydependentperturbations_(doublereal *dt, 
	doublereal *va, doublereal *spina, doublereal *acc, doublereal *dcmv, 
	doublereal *df, doublereal *dfgr, doublereal *dspin)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    extern /* Subroutine */ int reduce2cm_(doublereal *, doublereal *, 
	    integer *, doublereal *);
    static integer i__, k;
    extern /* Subroutine */ int relativisticaccelerations_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal dfr[600];

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*       häiriöt */
    /* Parameter adjustments */
    --dspin;
    --dfgr;
    --df;
    --dcmv;
    --acc;
    --spina;
    --va;

    /* Function Body */
    if (softening_1.clight != 0.f) {
/* include only if Clight set >0 */
	relativisticaccelerations_(dfr, &dfgr[1], &va[1], &spina[1], &dspin[1]
		);
    } else {
	i__1 = dataforroutines1_1.n * 3;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dfr[i__ - 1] = 0.;
	    dfgr[i__] = 0.;
	}
	for (k = 1; k <= 3; ++k) {
	    dspin[k] = 0.;
	}
    }
    i__1 = dataforroutines1_1.n * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	df[i__] = acc[i__] + dfr[i__ - 1];
    }
    reduce2cm_(&df[1], dataforroutines1_1.m, &dataforroutines1_1.n, &dcmv[1]);
    return 0;
} /* velocitydependentperturbations_ */

/* Subroutine */ int checkswitchingconditions_(logical *mustswitch)
{
    /* Initialized data */

    static integer ncall = 0;
    static integer nswitch = 200000000;

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, j, lri;
    static doublereal adisti, rinvmx;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    *mustswitch = FALSE_;
    ++ncall;
/*       Switch anyway after every NSWITCHth step. */
    if (ncall >= nswitch) {
	ncall = 0;
	*mustswitch = TRUE_;
	return 0;
    }
/*       Inspect the structure of the chain. */
/*       NOTE: Inverse values 1/r are used instead of r itself. */
    adisti = (dataforroutines1_1.n - 1) * .5f / dataforroutines1_1.rsum;
    lri = dataforroutines1_1.n - 1;
    i__1 = dataforroutines1_1.n - 2;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = dataforroutines1_1.n;
	for (j = i__ + 2; j <= i__2; ++j) {
	    ++lri;
/*       Do not inspect if 1/r is small. */
	    if (dataforroutines1_1.rinv[lri - 1] > adisti) {
		if (j - i__ > 2) {
/*        Check for a dangerous long loop. */
/*          RINVMX=MAX(RINV(I-1),RINV(I),RINV(J-1),RINV(J)) */
		    if (i__ > 1) {
/* Computing MAX */
			d__1 = dataforroutines1_1.rinv[i__ - 2], d__2 = 
				dataforroutines1_1.rinv[i__ - 1];
			rinvmx = max(d__1,d__2);
		    } else {
			rinvmx = dataforroutines1_1.rinv[0];
		    }
/* Computing MAX */
		    d__1 = rinvmx, d__2 = dataforroutines1_1.rinv[j - 2];
		    rinvmx = max(d__1,d__2);
		    if (j < dataforroutines1_1.n) {
/* Computing MAX */
			d__1 = rinvmx, d__2 = dataforroutines1_1.rinv[j - 1];
			rinvmx = max(d__1,d__2);
		    }
		    if (dataforroutines1_1.rinv[lri - 1] > rinvmx) {
/* 0.7*RINVMX may be more careful */
			*mustswitch = TRUE_;
			ncall = 0;
			return 0;
		    }
		} else {
/*        Is this a triangle with smallest size not regularised? */
/* Computing MAX */
		    d__1 = dataforroutines1_1.rinv[i__ - 1], d__2 = 
			    dataforroutines1_1.rinv[i__];
		    if (dataforroutines1_1.rinv[lri - 1] > max(d__1,d__2)) {
			*mustswitch = TRUE_;
			ncall = 0;
			return 0;
		    }
		}
	    }
	}
    }
    return 0;
} /* checkswitchingconditions_ */

/* Subroutine */ int findchainindices_(void)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i__, j, l, ic[400], ij[39800]	/* was [19900][2] */, 
	    li, ind[19900];
    static logical suc;
    static doublereal rij2[19900];
    static integer lmin;
    static logical used[19900];
    static integer lmax;
    static logical loop;
    extern doublereal square_(doublereal *, doublereal *);
    extern /* Subroutine */ int arrange_(integer *, doublereal *, integer *), 
	    checkconnection_(integer *, integer *, integer *, integer *, 
	    integer *, logical *, logical *);

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    l = 0;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = dataforroutines1_1.n;
	for (j = i__ + 1; j <= i__2; ++j) {
	    ++l;
	    rij2[l - 1] = square_(&dataforroutines1_1.x[i__ * 3 - 3], &
		    dataforroutines1_1.x[j * 3 - 3]);
	    ij[l - 1] = i__;
	    ij[l + 19899] = j;
	    used[l - 1] = FALSE_;
	}
    }
    arrange_(&l, rij2, ind);
    lmin = 201;
    lmax = 202;
    ic[lmin - 1] = ij[ind[0] - 1];
    ic[lmax - 1] = ij[ind[0] + 19899];
    used[ind[0] - 1] = TRUE_;
L1:
    i__1 = l;
    for (i__ = 2; i__ <= i__1; ++i__) {
	li = ind[i__ - 1];
	if (! used[li - 1]) {
	    checkconnection_(ic, &lmin, &lmax, ij, &li, &suc, &loop);
	    if (suc) {
		used[li - 1] = TRUE_;
		goto L2;
	    } else {
		used[li - 1] = loop;
	    }
	}
    }
L2:
    if (lmax - lmin + 1 < dataforroutines1_1.n) {
	goto L1;
    }
    l = 0;
    i__1 = lmax;
    for (i__ = lmin; i__ <= i__1; ++i__) {
	++l;
	dataforroutines1_1.iname[l - 1] = ic[i__ - 1];
    }
    return 0;
} /* findchainindices_ */

/* Subroutine */ int checkconnection_(integer *ic, integer *lmin, integer *
	lmax, integer *ij, integer *li, logical *suc, logical *loop)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, j, l, jc, icc[2];

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    ij -= 19901;
    --ic;

    /* Function Body */
    *suc = FALSE_;
    *loop = FALSE_;
    icc[0] = ic[*lmin];
    icc[1] = ic[*lmax];
    for (i__ = 1; i__ <= 2; ++i__) {
	for (j = 1; j <= 2; ++j) {
	    if (icc[i__ - 1] == ij[*li + j * 19900]) {
		jc = 3 - j;
		*loop = TRUE_;
		i__1 = *lmax;
		for (l = *lmin; l <= i__1; ++l) {
		    if (ic[l] == ij[*li + jc * 19900]) {
			return 0;
		    }
		}
		*suc = TRUE_;
		*loop = FALSE_;
		if (i__ == 1) {
		    --(*lmin);
		    ic[*lmin] = ij[*li + jc * 19900];
		    return 0;
		} else {
		    ++(*lmax);
		    ic[*lmax] = ij[*li + jc * 19900];
		    return 0;
		}
	    }
	}
    }
    return 0;
} /* checkconnection_ */

/* Subroutine */ int arrange_(integer *n, doublereal *array, integer *indx)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, j, l;
    static doublereal q;
    static integer ir, indxt;

    /* Parameter adjustments */
    --indx;
    --array;

    /* Function Body */
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	indx[j] = j;
/* L11: */
    }
    if (*n < 2) {
	return 0;
    }
    l = *n / 2 + 1;
    ir = *n;
L10:
    if (l > 1) {
	--l;
	indxt = indx[l];
	q = array[indxt];
    } else {
	indxt = indx[ir];
	q = array[indxt];
	indx[ir] = indx[1];
	--ir;
	if (ir == 1) {
	    indx[1] = indxt;
	    return 0;
	}
    }
    i__ = l;
    j = l + l;
L20:
    if (j <= ir) {
	if (j < ir) {
	    if (array[indx[j]] < array[indx[j + 1]]) {
		++j;
	    }
	}
	if (q < array[indx[j]]) {
	    indx[i__] = indx[j];
	    i__ = j;
	    j += j;
	} else {
	    j = ir + 1;
	}
	goto L20;
    }
    indx[i__] = indxt;
    goto L10;
} /* arrange_ */

/* Subroutine */ int initializexcandwc_(void)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l, lf;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*        Center of mass */
    for (k = 1; k <= 3; ++k) {
	dataforchainroutinestwo_1.cmx[k - 1] = 0.f;
	dataforchainroutinestwo_1.cmv[k - 1] = 0.f;
    }
    dataforroutines1_1.mass = 0.f;
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	dataforroutines1_1.mc[i__ - 1] = dataforroutines1_1.m[
		dataforroutines1_1.iname[i__ - 1] - 1];
/* masses along the chain */
	dataforroutines1_1.mass += dataforroutines1_1.mc[i__ - 1];
	for (k = 1; k <= 3; ++k) {
	    dataforchainroutinestwo_1.cmx[k - 1] += dataforroutines1_1.m[i__ 
		    - 1] * dataforroutines1_1.x[l + k - 1];
	    dataforchainroutinestwo_1.cmv[k - 1] += dataforroutines1_1.m[i__ 
		    - 1] * dataforroutines1_1.v[l + k - 1];
	}
    }
    for (k = 1; k <= 3; ++k) {
	dataforchainroutinestwo_1.cmx[k - 1] /= dataforroutines1_1.mass;
	dataforchainroutinestwo_1.cmv[k - 1] /= dataforroutines1_1.mass;
    }
/*       Rearange according to chain indices. */
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	lf = dataforroutines1_1.iname[i__ - 1] * 3 - 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.xi[l + k - 1] = dataforroutines1_1.x[lf + k - 
		    1];
	    dataforroutines1_1.vi[l + k - 1] = dataforroutines1_1.v[lf + k - 
		    1];
	}
    }
/*       Chain coordinates & vels ! AND INITIAL `WTTL' */
    dataforroutines1_1.wttl = 0.;
/*  initialize W */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.xc[l + k - 1] = dataforroutines1_1.xi[l + k + 
		    2] - dataforroutines1_1.xi[l + k - 1];
	    dataforroutines1_1.wc[l + k - 1] = dataforroutines1_1.vi[l + k + 
		    2] - dataforroutines1_1.vi[l + k - 1];
	}
    }
    return 0;
} /* initializexcandwc_ */

/* Subroutine */ int updatexandv_(void)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static doublereal v0[3], x0[3];
    static integer lf;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*        Obtain physical variables from chain quantities. */
    for (k = 1; k <= 3; ++k) {
	dataforroutines1_1.xi[k - 1] = 0.f;
	dataforroutines1_1.vi[k - 1] = 0.f;
	x0[k - 1] = 0.f;
	v0[k - 1] = 0.f;
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.vi[l + 3 + k - 1] = dataforroutines1_1.vi[l + 
		    k - 1] + dataforroutines1_1.wc[l + k - 1];
	    dataforroutines1_1.xi[l + 3 + k - 1] = dataforroutines1_1.xi[l + 
		    k - 1] + dataforroutines1_1.xc[l + k - 1];
	}
    }
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    v0[k - 1] += dataforroutines1_1.vi[l + k - 1] * 
		    dataforroutines1_1.mc[i__ - 1] / dataforroutines1_1.mass;
	    x0[k - 1] += dataforroutines1_1.xi[l + k - 1] * 
		    dataforroutines1_1.mc[i__ - 1] / dataforroutines1_1.mass;
	}
    }
/*        Rearrange according to INAME(i) and add CM. */
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	lf = (dataforroutines1_1.iname[i__ - 1] - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.x[lf + k - 1] = dataforroutines1_1.xi[l + k - 
		    1] - x0[k - 1];
/* +CMX(K) ! CM-coords */
	    dataforroutines1_1.v[lf + k - 1] = dataforroutines1_1.vi[l + k - 
		    1] - v0[k - 1];
/* +CMV(K) ! CM-vels */
	}
    }
    return 0;
} /* updatexandv_ */

/* Subroutine */ int chaintransformation_(void)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    extern /* Subroutine */ int findchainindices_(void);
    static integer i__, k, l, k0, k1, l1, l2, iold[200], lold, lnew, icold, 
	    icnew;
    static doublereal wcnew[600], xcnew[600];

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    l2 = (dataforroutines1_1.iname[0] - 1) * 3;
    for (k = 1; k <= 3; ++k) {
	dataforroutines1_1.x[l2 + k - 1] = 0.f;
    }
/*       Xs are needed when determining new chain indices. */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	l1 = l2;
	l2 = (dataforroutines1_1.iname[i__] - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.x[l2 + k - 1] = dataforroutines1_1.x[l1 + k - 
		    1] + dataforroutines1_1.xc[l + k - 1];
	}
    }
/*        Store the old chain indices. */
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	iold[i__ - 1] = dataforroutines1_1.iname[i__ - 1];
    }
/*       Find new ones. */
    findchainindices_();
/*       Construct new chain coordinates. Transformation matrix */
/*       (from old to new) has only coefficients -1, 0 or +1. */
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xcnew[i__ - 1] = 0.f;
	wcnew[i__ - 1] = 0.f;
    }
    i__1 = dataforroutines1_1.n - 1;
    for (icnew = 1; icnew <= i__1; ++icnew) {
/*       Obtain K0 &  K1 such that iold(k0)=iname(icnew) */
/*                                 iold(k1)=iname(icnew+1) */
	lnew = (icnew - 1) * 3;
	i__2 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    if (iold[i__ - 1] == dataforroutines1_1.iname[icnew - 1]) {
		k0 = i__;
	    }
	    if (iold[i__ - 1] == dataforroutines1_1.iname[icnew]) {
		k1 = i__;
	    }
	}
	i__2 = dataforroutines1_1.n - 1;
	for (icold = 1; icold <= i__2; ++icold) {
	    lold = (icold - 1) * 3;
	    if (k1 > icold && k0 <= icold) {
/*       ADD */
		for (k = 1; k <= 3; ++k) {
		    xcnew[lnew + k - 1] += dataforroutines1_1.xc[lold + k - 1]
			    ;
		    wcnew[lnew + k - 1] += dataforroutines1_1.wc[lold + k - 1]
			    ;
		}
	    } else if (k1 <= icold && k0 > icold) {
/*        SUBTRACT */
		for (k = 1; k <= 3; ++k) {
		    xcnew[lnew + k - 1] -= dataforroutines1_1.xc[lold + k - 1]
			    ;
		    wcnew[lnew + k - 1] -= dataforroutines1_1.wc[lold + k - 1]
			    ;
		}
	    }
	}
    }
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* !!!!!!!!!!!!!!!!! */
	dataforroutines1_1.xc[i__ - 1] = xcnew[i__ - 1];
/* !!!!!!!!!!!!!!!!!! */
	dataforroutines1_1.wc[i__ - 1] = wcnew[i__ - 1];
    }
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/*       Auxiliary quantities. */
/* !!!!!!!!!!!!!!!!!!!! */
    dataforroutines1_1.mass = 0.f;
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dataforroutines1_1.mc[i__ - 1] = dataforroutines1_1.m[
		dataforroutines1_1.iname[i__ - 1] - 1];
	dataforroutines1_1.mass += dataforroutines1_1.mc[i__ - 1];
    }
    return 0;
} /* chaintransformation_ */

doublereal square_(doublereal *x, doublereal *y)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2, d__3;

/* only ee needed her */
    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
/* Computing 2nd power */
    d__1 = x[1] - y[1];
/* Computing 2nd power */
    d__2 = x[2] - y[2];
/* Computing 2nd power */
    d__3 = x[3] - y[3];
    ret_val = d__1 * d__1 + d__2 * d__2 + d__3 * d__3 + softening_1.ee;
    return ret_val;
} /* square_ */

/* Subroutine */ int difsyab_(integer *n, doublereal *eps, doublereal *s, 
	doublereal *h__, doublereal *t, doublereal *y)
{
    /* Initialized data */

    static doublereal ep[4] = { .04,.0016,6.4e-5,2.56e-6 };
    static doublereal dt[21000]	/* was [3000][7] */ = { 0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0. };

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    extern /* Subroutine */ int substeps_(doublereal *, doublereal *, 
	    doublereal *, integer *);
    static doublereal b, c__, d__[7];
    static integer i__, j, k, l, m;
    static doublereal u, v, w, b1, y0[1500], fa;
    static logical bo;
    static doublereal ta;
    static logical kl, gr;
    static doublereal fs;
    static integer jr, js;
    static doublereal si, fy, fv, tn, yr[3000], ys[3000];
    static integer jti, jmax;
    static doublereal redu, subh;
    static logical konv;
    static doublereal odot7;

    /* Fortran I/O blocks */
    static cilist io___254 = { 0, 6, 0, 0, 0 };
    static cilist io___255 = { 0, 6, 0, 0, 0 };


/* ,Jmax) */
/*       N=coordin. määrä (=3*NB) */
/*       F=funktion nimi (FORCE) */
/* NMX=MAX(N),N=3*NB */
    /* Parameter adjustments */
    --y;
    --s;

    /* Function Body */
    jmax = 10;
/* JMAX set here */
    if (*eps < 1e-14) {
	*eps = 1e-14;
    }
    if (*n > 1500) {
	s_wsle(&io___254);
	do_lio(&c__9, &c__1, " too many variables!", (ftnlen)20);
	do_lio(&c__9, &c__1, "\a", (ftnlen)1);
	e_wsle();
    }
    if (jmax < 4) {
	s_wsle(&io___255);
	do_lio(&c__9, &c__1, " too small Jmax (=", (ftnlen)18);
	do_lio(&c__3, &c__1, (char *)&jmax, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, ")", (ftnlen)1);
	e_wsle();
    }
    jti = 0;
    fy = 1.;
    redu = .8;
    odot7 = .7f;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	y0[i__ - 1] = y[i__];
/* Computing MAX */
	d__2 = (d__1 = y0[i__ - 1], abs(d__1)), d__3 = s[i__];
	s[i__] = max(d__2,d__3);
    }
L10:
    tn = *t + *h__;
    bo = FALSE_;

    m = 1;
    jr = 2;
    js = 3;
    i__1 = jmax;
    for (j = 1; j <= i__1; ++j) {
/* 10 */
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ys[i__ - 1] = y[i__];
/* Computing MAX */
	    d__2 = (d__1 = ys[i__ - 1], abs(d__1)), d__3 = s[i__];
	    s[i__] = max(d__2,d__3);
	}

	if (bo) {
	    d__[1] = 1.777777777777778;
	    d__[3] = 7.111111111111111;
	    d__[5] = 28.44444444444444;
	} else {
	    d__[1] = 2.25;
	    d__[3] = 9.;
	    d__[5] = 36.;
	}
	if (j > 7) {
	    l = 7;
	    d__[6] = 64.;
	} else {
	    l = j;
	    d__[l - 1] = (doublereal) (m * m);
	}
	konv = l > 3;
	subh = *h__ / m;
	substeps_(y0, ys, &subh, &m);
/* M substeps of size H/M. */
	kl = l < 2;
	gr = l > 5;
	fs = 0.f;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    v = dt[i__ - 1];
	    c__ = ys[i__ - 1];
	    dt[i__ - 1] = c__;
	    ta = c__;
	    if (! kl) {
		i__3 = l;
		for (k = 2; k <= i__3; ++k) {
		    b1 = d__[k - 1] * v;
		    b = b1 - c__;
		    w = c__ - v;
		    u = v;
		    if (b != 0.f) {
			b = w / b;
			u = c__ * b;
			c__ = b1 * b;
		    }
		    v = dt[i__ + k * 3000 - 3001];
		    dt[i__ + k * 3000 - 3001] = u;
		    ta = u + ta;
		}
/* K=2,L */
/* Computing MAX */
		d__1 = s[i__], d__2 = abs(ta), d__1 = max(d__1,d__2);
		si = max(d__1,*eps);
		if ((d__1 = yr[i__ - 1] - ta, abs(d__1)) > si * *eps) {
		    konv = FALSE_;
		}
		if (! (gr || si == 0.)) {
		    fv = abs(w) / si;
		    if (fs < fv) {
			fs = fv;
		    }
		}
	    }
/* .NOT.KL. */
	    yr[i__ - 1] = ta;
	}
/*       end of I-loop */
/* I=1,N */
	if (fs != 0.) {
	    fa = fy;
	    k = l - 1;
	    d__1 = ep[k - 1] / fs;
	    d__2 = 1. / (real) (l + k);
	    fy = pow_dd(&d__1, &d__2);
	    fy = min(fy,1.4);
/* 1.4 ~ 1/0.7 ; where 0.7 = initial reduction fact */
	    if (! (l != 2 && fy < odot7 * fa || fy > odot7)) {
		*h__ *= fy;
		++jti;
		if (jti > 25) {
		    *h__ = 0.f;
		    return 0;
		}
		goto L10;
/* Try again with a smaller step. */
	    }
	}
	if (konv) {
	    *t = tn;
	    *h__ *= fy;
	    i__2 = *n;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		y[i__] = yr[i__ - 1] + y0[i__ - 1];
/* !!!!!! */
	    }
	    return 0;
	}
	d__[2] = 4.;
	d__[4] = 16.;
	bo = ! bo;
	m = jr;
	jr = js;
	js = m + m;
    }
/* J=1,Jmax */
    redu = redu * redu + .001;
/* square the reduction factor (but minimum */
    *h__ *= redu;
    goto L10;
/* Try again with smaller step. */
} /* difsyab_ */

/* Subroutine */ int substeps_(doublereal *y0, doublereal *y, doublereal *h__,
	 integer *leaps)
{
    extern /* Subroutine */ int leapfrog_(doublereal *, integer *, doublereal 
	    *), takeincrements2y_(doublereal *), initializeincrements2zero_(
	    void), putytoxcwc_(doublereal *, integer *);
    static integer nvar;
    static doublereal stime;

/* ,ytest(1000) */
    /* Parameter adjustments */
    --y;
    --y0;

    /* Function Body */
    collision_1.icollision = 0;
    putytoxcwc_(&y0[1], &nvar);
/* Y -> XC, WTTL, WC */
    initializeincrements2zero_();
    leapfrog_(h__, leaps, &stime);
/* advance */
    takeincrements2y_(&y[1]);
    return 0;
} /* substeps_ */

/* Subroutine */ int initializeincrements2zero_(void)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	incrementcommon_1.xcinc[i__ - 1] = 0.;
	incrementcommon_1.wcinc[i__ - 1] = 0.;
    }
    for (k = 1; k <= 3; ++k) {
	incrementcommon_1.cmxinc[k - 1] = 0.;
	incrementcommon_1.cmvinc[k - 1] = 0.;
	incrementcommon_1.spininc[k - 1] = 0.;
    }
    incrementcommon_1.wttlinc = 0.;
    incrementcommon_1.energyinc = 0.;
    incrementcommon_1.energrinc = 0.;
    incrementcommon_1.chtimeinc = 0.;
    return 0;
} /* initializeincrements2zero_ */

/* Subroutine */ int takeincrements2y_(doublereal *y)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --y;

    /* Function Body */
    l = 1;
    y[l] = incrementcommon_1.chtimeinc;
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++l;
	y[l] = incrementcommon_1.xcinc[i__ - 1];
    }
    ++l;
    y[l] = incrementcommon_1.wttlinc;
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++l;
	y[l] = incrementcommon_1.wcinc[i__ - 1];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	y[l] = incrementcommon_1.cmxinc[i__ - 1];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	y[l] = incrementcommon_1.cmvinc[i__ - 1];
    }
    ++l;
    y[l] = incrementcommon_1.energyinc;
    ++l;
    y[l] = incrementcommon_1.energrinc;
    for (k = 1; k <= 3; ++k) {
	++l;
	y[l] = incrementcommon_1.spininc[k - 1];
    }
/*        Nvar=L */
    return 0;
} /* takeincrements2y_ */

/* Subroutine */ int putytoxcwc_(doublereal *y, integer *lmx)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --y;

    /* Function Body */
    l = 1;
    dataforchainroutinestwo_1.chtime = y[l];
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++l;
	dataforroutines1_1.xc[i__ - 1] = y[l];
    }
    ++l;
    dataforroutines1_1.wttl = y[l];
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++l;
	dataforroutines1_1.wc[i__ - 1] = y[l];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	dataforchainroutinestwo_1.cmx[i__ - 1] = y[l];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	dataforchainroutinestwo_1.cmv[i__ - 1] = y[l];
    }
    ++l;
    dataforchainroutinestwo_1.energy = y[l];
    ++l;
    dataforchainroutinestwo_1.energr = y[l];
    for (k = 1; k <= 3; ++k) {
	++l;
	spincommon_1.spin[k - 1] = y[l];
    }
    *lmx = l;
    return 0;
} /* putytoxcwc_ */

/* Subroutine */ int takeyfromxcwc_(doublereal *y, integer *nvar)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --y;

    /* Function Body */
    l = 1;
    y[l] = dataforchainroutinestwo_1.chtime;
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++l;
	y[l] = dataforroutines1_1.xc[i__ - 1];
    }
    ++l;
    y[l] = dataforroutines1_1.wttl;
    i__1 = (dataforroutines1_1.n - 1) * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++l;
	y[l] = dataforroutines1_1.wc[i__ - 1];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	y[l] = dataforchainroutinestwo_1.cmx[i__ - 1];
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	y[l] = dataforchainroutinestwo_1.cmv[i__ - 1];
    }
    ++l;
    y[l] = dataforchainroutinestwo_1.energy;
    ++l;
    y[l] = dataforchainroutinestwo_1.energr;
    for (k = 1; k <= 3; ++k) {
	++l;
	y[l] = spincommon_1.spin[k - 1];
    }
    *nvar = l;
    return 0;
} /* takeyfromxcwc_ */

/* Subroutine */ int obtainorderofy_(doublereal *sy)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, k, l, i0;
    static doublereal sr, sw, sw0, wca, xca, upo, cmva, cmxa, w_old__, xcmin, 
	    w_new__;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --sy;

    /* Function Body */
    w_old__ = .01f;
    w_new__ = 1 - w_old__;
    l = 1;
    sy[l] = abs(dataforchainroutinestwo_1.chtime) * w_new__ + sy[l] * w_old__;
    sr = 0.;
    xcmin = 1e99;
    upo = 0.;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i0 = i__ * 3 - 3;
	xca = (d__1 = dataforroutines1_1.xc[i0], abs(d__1)) + (d__2 = 
		dataforroutines1_1.xc[i0 + 1], abs(d__2)) + (d__3 = 
		dataforroutines1_1.xc[i0 + 2], abs(d__3));
	sr += xca;
	upo += dataforchainroutinestwo_1.mmij / xca;
	xcmin = min(xca,xcmin);
	for (k = 1; k <= 3; ++k) {
	    ++l;
	    sy[l] = xca * w_new__ + sy[l] * w_old__;
	}
/* k */
    }
/* I */
    ++l;
/* Computing 2nd power */
    d__2 = dataforroutines1_1.mass;
    sy[l] = ((d__1 = dataforroutines1_1.wttl * 100.f, abs(d__1)) + d__2 * 
	    d__2 / xcmin) * w_new__ + sy[l] * w_old__;
    sw0 = sqrt((d__1 = dataforchainroutinestwo_1.energy / 
	    dataforroutines1_1.mass, abs(d__1)));
    sw = 0.;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i0 = i__ * 3 - 3;
	wca = (d__1 = dataforroutines1_1.wc[i0], abs(d__1)) + (d__2 = 
		dataforroutines1_1.wc[i0 + 1], abs(d__2)) + (d__3 = 
		dataforroutines1_1.wc[i0 + 2], abs(d__3));
	sw += wca;
	for (k = 1; k <= 3; ++k) {
	    ++l;
	    if (wca != 0.f) {
		sy[l] = wca * w_new__ + sy[l] * w_old__;
	    } else {
		sy[l] = sw0 * w_new__ + sy[l] * w_old__;
	    }
	}
/* k */
    }
/* i */
    l = 1;
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i0 = i__ * 3 - 3;
	for (k = 1; k <= 3; ++k) {
	    ++l;
	    if (sy[l] == 0.f) {
		sy[l] = sr / dataforroutines1_1.n * w_new__ + sy[l] * w_old__;
	    }
	}
/* k */
    }
/* I */
    ++l;
/* WTTL */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i0 = i__ * 3 - 3;
	for (k = 1; k <= 3; ++k) {
	    ++l;
	    if (sy[l] == 0.f) {
		sy[l] = (sw / dataforroutines1_1.n + sqrt(upo / 
			dataforroutines1_1.mass)) * w_new__ + sy[l] * w_old__;
	    }
/*        if(SY(L).eq.0.0)SY(L)=1 */
	}
/* k */
    }
/* i */
    cmxa = abs(dataforchainroutinestwo_1.cmx[0]) + abs(
	    dataforchainroutinestwo_1.cmx[1]) + abs(
	    dataforchainroutinestwo_1.cmx[2]) + sr / dataforroutines1_1.n;
    cmva = abs(dataforchainroutinestwo_1.cmv[0]) + abs(
	    dataforchainroutinestwo_1.cmv[1]) + abs(
	    dataforchainroutinestwo_1.cmv[2]) + sw / dataforroutines1_1.n;
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	sy[l] = cmxa * w_new__ + sy[l] * w_old__;
/* cmx */
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	++l;
	sy[l] = cmva * w_new__ + sy[l] * w_old__;
/* cmv */
    }
    ++l;
    sy[l] = (abs(dataforchainroutinestwo_1.energy) + upo * .1f) * w_new__ + 
	    sy[l] * w_old__;
/* E */
    ++l;
    sy[l] = sy[l - 1] * w_new__ + sy[l] * w_old__;
    if (sy[1] == 0.f) {
	sy[1] = sqrt(sr / dataforroutines1_1.mass) * sr * .01 * w_new__ + sy[
		1] * w_old__;
    }
    for (k = 1; k <= 3; ++k) {
	++l;
	sy[l] = 1.f;
/* spin components. */
    }
    i__1 = l;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*        if(sy(i).eq.0.0)sy(i)=eps */
    }
    return 0;
} /* obtainorderofy_ */

/* Subroutine */ int evaluatex_(void)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static doublereal x0[3];
    static integer lf;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*        Obtain physical variables from chain quantities. */
    for (k = 1; k <= 3; ++k) {
	dataforroutines1_1.xi[k - 1] = 0.f;
	x0[k - 1] = 0.f;
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.xi[l + 3 + k - 1] = dataforroutines1_1.xi[l + 
		    k - 1] + dataforroutines1_1.xc[l + k - 1];
	}
    }
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    x0[k - 1] += dataforroutines1_1.xi[l + k - 1] * 
		    dataforroutines1_1.mc[i__ - 1] / dataforroutines1_1.mass;
	}
    }
/*        Rearrange according to INAME(i) and add CM. */
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	lf = (dataforroutines1_1.iname[i__ - 1] - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.x[lf + k - 1] = dataforroutines1_1.xi[l + k - 
		    1] - x0[k - 1];
/* +CMX(K) ! CM-coords */
	}
    }
    return 0;
} /* evaluatex_ */

/* Subroutine */ int evaluatev_(doublereal *vn, doublereal *wi)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static doublereal v0[3];
    static integer lf;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*        Obtain physical V's from chain quantities. */
    /* Parameter adjustments */
    --wi;
    --vn;

    /* Function Body */
    for (k = 1; k <= 3; ++k) {
	v0[k - 1] = 0.f;
	dataforroutines1_1.vi[k - 1] = 0.f;
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.vi[l + 3 + k - 1] = dataforroutines1_1.vi[l + 
		    k - 1] + wi[l + k];
/* WC(L+K) */
	}
    }
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    v0[k - 1] += dataforroutines1_1.vi[l + k - 1] * 
		    dataforroutines1_1.mc[i__ - 1] / dataforroutines1_1.mass;
	}
    }
/*        Rearrange according to INAME(i) and add CM. */
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	lf = (dataforroutines1_1.iname[i__ - 1] - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    vn[lf + k] = dataforroutines1_1.vi[l + k - 1] - v0[k - 1];
/* +CMV(K) */
	    dataforroutines1_1.v[lf + k - 1] = vn[lf + k];

	}
    }
    return 0;
} /* evaluatev_ */

/* Subroutine */ int relativisticaccelerations_(doublereal *acc, doublereal *
	accgr, doublereal *va, doublereal *spina, doublereal *dspin)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, i1, i2, i3, j3, j2, j1, k1, k2, k3;
    static doublereal df[3], cl;
    static integer ii, ik, jk;
    static doublereal dx[3], dw[3];
    static integer jx;
    static doublereal rs;
    extern /* Subroutine */ int relativisticterms_(integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal dsp[3], rij, rij2, vij2, dfgr[3], test, rdotv;

    /* Fortran I/O blocks */
    static cilist io___354 = { 0, 6, 0, 0, 0 };


/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --dspin;
    --spina;
    --va;
    --accgr;
    --acc;

    /* Function Body */
    cl = softening_1.clight;
/*       INITIALIZE THE relativistic acceration(s) here. */
/* SPEED OF LIGHT */
    i__1 = dataforroutines1_1.n * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	acc[i__] = 0.f;
	accgr[i__] = 0.f;
    }
    for (k = 1; k <= 3; ++k) {
	dspin[k] = 0.;
    }
    i__1 = dataforroutines1_1.n;
    for (ik = 1; ik <= i__1; ++ik) {
	i__ = dataforroutines1_1.iname[ik - 1];
	i3 = i__ * 3;
	i2 = i3 - 1;
	i1 = i3 - 2;
	i__2 = dataforroutines1_1.n;
	for (jk = ik + 1; jk <= i__2; ++jk) {
	    j = dataforroutines1_1.iname[jk - 1];
	    if (min(i__,j) <= softening_1.nofbh) {
/* only BH - BH, max->min => BH* */
		j3 = j + j + j;
		j2 = j3 - 1;
		j1 = j3 - 2;
		if (jk != ik + 1) {
		    dx[0] = dataforroutines1_1.x[j1 - 1] - 
			    dataforroutines1_1.x[i1 - 1];
		    dx[1] = dataforroutines1_1.x[j2 - 1] - 
			    dataforroutines1_1.x[i2 - 1];
		    dx[2] = dataforroutines1_1.x[j3 - 1] - 
			    dataforroutines1_1.x[i3 - 1];
		    dw[0] = va[j1] - va[i1];
		    dw[1] = va[j2] - va[i2];
		    dw[2] = va[j3] - va[i3];
		} else {
		    k1 = ik * 3 - 2;
		    k2 = k1 + 1;
		    k3 = k2 + 1;
		    dx[0] = dataforroutines1_1.xc[k1 - 1];
		    dx[1] = dataforroutines1_1.xc[k2 - 1];
		    dx[2] = dataforroutines1_1.xc[k3 - 1];
		    dw[0] = va[j1] - va[i1];
		    dw[1] = va[j2] - va[i2];
		    dw[2] = va[j3] - va[i3];
		}
/* Computing 2nd power */
		d__1 = dw[0];
/* Computing 2nd power */
		d__2 = dw[1];
/* Computing 2nd power */
		d__3 = dw[2];
		vij2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
/*       This (cheating) avoids vij>cl and produces only O(1/c^6) 'errors'. */
		if (vij2 > cl * cl) {
		    for (k = 1; k <= 3; ++k) {
/*        dw(k)=dw(k)/(1+(vij2/cl**2)**8)**.0625d0 !  avoid V_ij > c !! */
/*        dw(k)=dw(k)/(1+(vij2/cl**2)**2)**.25d0 ! not so good */
		    }
		}
/* Computing 2nd power */
		d__1 = dw[0];
/* Computing 2nd power */
		d__2 = dw[1];
/* Computing 2nd power */
		d__3 = dw[2];
		vij2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
/* Computing 2nd power */
		d__1 = cl;
		rs = (dataforroutines1_1.m[i__ - 1] + dataforroutines1_1.m[j 
			- 1]) * 2. / (d__1 * d__1);
/* Computing 2nd power */
		d__1 = dx[0];
/* Computing 2nd power */
		d__2 = dx[1];
/* Computing 2nd power */
		d__3 = dx[2];
		rij2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
		rij = sqrt(rij2);
		rdotv = dx[0] * dw[0] + dx[1] * dw[1] + dx[2] * dw[2];
		ii = min(i__,j);
		jx = max(i__,j);
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*        nkir=nkir+1 */
/*        if(nkir.eq.nkir/1000*1000)then */
/*        write(8,108)rij/rs,(dx(k)/rs,k=1,3),sqrt(vij2)/cl */
/* 108     format(1x,1p,9g13.5) */
/*         end if */
/* ----------------------------------------------------- */
		relativisticterms_(&ii, dx, dw, &rij, &rdotv, &vij2, &
			dataforroutines1_1.m[ii - 1], &dataforroutines1_1.m[
			jx - 1], &cl, df, dfgr, &spina[1], dsp);
/* Computing 2nd power */
		d__1 = cl;
		rs = (dataforroutines1_1.m[i__ - 1] + dataforroutines1_1.m[j 
			- 1]) * 2. / (d__1 * d__1);
		test = rs * 4;
/*          write(6,*)rij/RS,sqrt(vij2)/cl,' R  V ' */
/*                         test=.99*Rs */
		if (rij < test && collision_1.iwarning < 2) {
		    s_wsle(&io___354);
		    do_lio(&c__9, &c__1, " Near collision: r/RS", (ftnlen)21);
		    d__1 = rij / rs;
		    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(
			    doublereal));
		    do_lio(&c__3, &c__1, (char *)&i__, (ftnlen)sizeof(integer)
			    );
		    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
		    d__2 = sqrt(vij2) / cl;
		    do_lio(&c__5, &c__1, (char *)&d__2, (ftnlen)sizeof(
			    doublereal));
		    e_wsle();
		}
/* diagno */
		if (rij < test) {

		    ++collision_1.iwarning;
		    collision_1.icollision = 1;
/* collision indicator */
		    collision_1.ione = min(i__,j);
		    collision_1.itwo = max(i__,j);
		    return 0;
		}
		for (k = 1; k <= 3; ++k) {
		    dspin[k] += dsp[k - 1];
		}
		acc[i1] += dataforroutines1_1.m[j - 1] * df[0];
/* here I assume action = reaction */
		acc[i2] += dataforroutines1_1.m[j - 1] * df[1];
/* which is not really true for */
		acc[i3] += dataforroutines1_1.m[j - 1] * df[2];
/* relativistic terms (but who cares) */
		acc[j1] -= dataforroutines1_1.m[i__ - 1] * df[0];
		acc[j2] -= dataforroutines1_1.m[i__ - 1] * df[1];
		acc[j3] -= dataforroutines1_1.m[i__ - 1] * df[2];
/*        Grav.Rad.-terms */
		accgr[i1] += dataforroutines1_1.m[j - 1] * dfgr[0];
/* here I assume action = reacti */
		accgr[i2] += dataforroutines1_1.m[j - 1] * dfgr[1];
/* which is not really true for */
		accgr[i3] += dataforroutines1_1.m[j - 1] * dfgr[2];
/* relativistic terms (but who c */
		accgr[j1] -= dataforroutines1_1.m[i__ - 1] * dfgr[0];
		accgr[j2] -= dataforroutines1_1.m[i__ - 1] * dfgr[1];
		accgr[j3] -= dataforroutines1_1.m[i__ - 1] * dfgr[2];
	    }
	}
/* J */
    }
/* I */
    for (k = 1; k <= 3; ++k) {
	turhia_1.akiih[k - 1] = acc[k + 3];
    }
/* REMOVE THIS LOOP(diagno only) */
    return 0;
} /* relativisticaccelerations_ */

/* Subroutine */ int relativisticterms_notinuse__(integer *i1, doublereal *x, 
	doublereal *v, doublereal *r__, doublereal *rdotv, doublereal *v2, 
	doublereal *m1, doublereal *m2, doublereal *c__, doublereal *dv, 
	doublereal *dvgr, doublereal *spina, doublereal *dspin)
{
    /* Initialized data */

    static doublereal beta = 1.;
    static doublereal gamma = 1.;

    /* System generated locals */
    doublereal d__1, d__2, d__3, d__4, d__5, d__6, d__7, d__8, d__9, d__10, 
	    d__11, d__12;

    /* Local variables */
    static integer i__, k;
    static doublereal m, n[3], r2, v4, nv, my, ny, dv2[3], dv3[3], dv4[3], 
	    dv5[3];
    extern /* Subroutine */ int gopu_spinterms__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Parameter adjustments */
    --dspin;
    --spina;
    --dvgr;
    --dv;
    --v;
    --x;

    /* Function Body */
    m = *m1 + *m2;
    my = *m1 * *m2 / m;
    ny = my / m;
    n[0] = x[1] / *r__;
    n[1] = x[2] / *r__;
    n[2] = x[3] / *r__;
    nv = *rdotv / *r__;
    v4 = *v2 * *v2;
    r2 = *r__ * *r__;
    if (TRUE_) {
	for (i__ = 1; i__ <= 3; ++i__) {
/* Computing 2nd power */
	    d__1 = *c__;
/* Computing 2nd power */
	    d__2 = nv;
/* Computing 2nd power */
	    d__3 = *c__;
/* Computing 2nd power */
	    d__4 = *r__;
	    dv2[i__ - 1] = m / (d__1 * d__1) * n[i__ - 1] / r2 * (m / *r__ * (
		    (beta + gamma) * 2 + ny * 2) - *v2 * (gamma + ny * 3) + 
		    ny * 3 / 2 * (d__2 * d__2)) + m * v[i__] * nv / (d__3 * 
		    d__3) / (d__4 * d__4) * (gamma * 2 + 2 - ny * 2);
/* 1/c**2 term */
	}
	for (i__ = 1; i__ <= 3; ++i__) {
/* Computing 4th power */
	    d__1 = *c__, d__1 *= d__1;
/* Computing 2nd power */
	    d__2 = nv;
/* Computing 4th power */
	    d__3 = nv, d__3 *= d__3;
/* Computing 2nd power */
	    d__4 = m;
/* Computing 3rd power */
	    d__5 = *r__;
/* Computing 2nd power */
	    d__6 = nv;
/* Computing 2nd power */
	    d__7 = *r__;
/* Computing 3rd power */
	    d__8 = nv;
/* Computing 2nd power */
	    d__9 = m;
/* Computing 3rd power */
	    d__10 = *r__;
/* Computing 3rd power */
	    d__11 = m;
/* Computing 4th power */
	    d__12 = *r__, d__12 *= d__12;
	    dv4[i__ - 1] = 1 / (d__1 * d__1) * (ny * m * n[i__ - 1] / r2 * (
		    v4 * -2 + *v2 * 1.5 * (d__2 * d__2) * (3 - ny * 4) - d__3 
		    * d__3 * 15 / 8 * (1 - ny * 3)) + d__4 * d__4 * n[i__ - 1]
		     / (d__5 * (d__5 * d__5)) * (*v2 / 2 * ny * (ny * 4 + 11) 
		    + d__6 * d__6 * 2 * (ny * (ny * 3 + 12) + 1)) + ny * m * 
		    v[i__] / (d__7 * d__7) * (*v2 * 8 * nv - d__8 * (d__8 * 
		    d__8) * 3 / 2 * (ny * 2 + 3)) - d__9 * d__9 / 2 / (d__10 *
		     (d__10 * d__10)) * v[i__] * nv * (ny * 43 + 4) - d__11 * 
		    (d__11 * d__11) * n[i__ - 1] / (d__12 * d__12) * (ny * 87 
		    / 4 + 9));
/* 1/c**4 terms */
	}
    } else {
	for (k = 1; k <= 3; ++k) {
	    dv2[k - 1] = 0.;
	    dv4[k - 1] = 0.;
	}
    }
    for (i__ = 1; i__ <= 3; ++i__) {
/* Computing 5th power */
	d__1 = *c__, d__2 = d__1, d__1 *= d__1;
/* Computing 2nd power */
	d__3 = m;
/* Computing 3rd power */
	d__4 = *r__;
	dv5[i__ - 1] = ny / (d__2 * (d__1 * d__1)) * (d__3 * d__3 * -8 / (
		d__4 * (d__4 * d__4)) / 5 * (v[i__] * (*v2 + m * 3 / *r__) - 
		n[i__ - 1] * nv * (*v2 * 3 + m * 17 / 3 / *r__)));
/* gravitational radiation terms */
    }
    if (*i1 == 1) {
	gopu_spinterms__(&x[1], &v[1], r__, m1, m2, c__, &spina[1], dv3, &
		dspin[1]);
/* spinterms */
    } else {
	for (k = 1; k <= 3; ++k) {
	    dv3[k - 1] = 0.;
	    dspin[k] = 0.;
	}
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	dv[i__] = -1 / m * (dv2[i__ - 1] + dv3[i__ - 1] + dv4[i__ - 1] + dv5[
		i__ - 1]);
	dvgr[i__] = -1 / m * dv5[i__ - 1];
    }
    return 0;
} /* relativisticterms_notinuse__ */

/* Subroutine */ int relativisticterms_(integer *i1, doublereal *x, 
	doublereal *v, doublereal *r__, doublereal *rdotv, doublereal *vv, 
	doublereal *m1, doublereal *m2, doublereal *c__, doublereal *dv, 
	doublereal *dvgr, doublereal *spina, doublereal *dspin)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3, d__4, d__5, d__6, d__7, d__8, d__9, d__10, 
	    d__11, d__12, d__13, d__14, d__15, d__16, d__17, d__18, d__19, 
	    d__20, d__21, d__22;

    /* Local variables */
    static integer k;
    static doublereal m, n[3], vr, pi2, eta, dvq[3], atot, btot, afric, bfric;
    extern /* Subroutine */ int gopu_spinterms__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* _not in use */
/*           pi= 3.14159265358979324d0 */
    /* Parameter adjustments */
    --dspin;
    --spina;
    --dvgr;
    --dv;
    --v;
    --x;

    /* Function Body */
    pi2 = 9.8696044010893586;
    vr = *rdotv / *r__;
    for (k = 1; k <= 3; ++k) {
	n[k - 1] = x[k] / *r__;
    }
    m = *m1 + *m2;
/* Computing 2nd power */
    d__1 = m;
    eta = *m1 * *m2 / (d__1 * d__1);
/* Computing 2nd power */
    d__1 = vr;
    outpa1a2ctc_1.a1 = (eta + 2) * 2 * (m / *r__) - (eta * 3 + 1) * *vv + eta 
	    * 1.5 * (d__1 * d__1);
/* Computing 2nd power */
    d__1 = m / *r__;
/* Computing 2nd power */
    d__2 = *vv;
/* Computing 4th power */
    d__3 = vr, d__3 *= d__3;
/* Computing 2nd power */
    d__4 = eta;
/* Computing 2nd power */
    d__5 = vr;
/* Computing 2nd power */
    d__6 = vr;
    outpa1a2ctc_1.a2 = (eta * 29 + 12) * -.75 * (d__1 * d__1) - eta * (3 - 
	    eta * 4) * (d__2 * d__2) - eta * 1.875 * (1 - eta * 3) * (d__3 * 
	    d__3) + eta * .5 * (13 - eta * 4) * (m / *r__) * *vv + (eta * 25 
	    + 2 + d__4 * d__4 * 2) * (m / *r__) * (d__5 * d__5) + eta * 1.5 * 
	    (3 - eta * 4) * *vv * (d__6 * d__6);
    outpa1a2ctc_1.a2p5 = eta * 1.6000000000000001 * (m / *r__) * vr * (m / *
	    r__ * 5.666666666666667 + *vv * 3);
/* Computing 3rd power */
    d__1 = m / *r__;
/* Computing 2nd power */
    d__2 = eta;
/* Computing 2nd power */
    d__3 = m / *r__;
/* Computing 2nd power */
    d__4 = eta;
/* Computing 3rd power */
    d__5 = eta;
/* Computing 2nd power */
    d__6 = m / *r__;
/* Computing 2nd power */
    d__7 = vr;
/* Computing 2nd power */
    d__8 = eta;
/* Computing 3rd power */
    d__9 = *vv;
/* Computing 2nd power */
    d__10 = eta;
/* Computing 6th power */
    d__11 = vr, d__11 *= d__11;
/* Computing 2nd power */
    d__12 = eta;
/* Computing 2nd power */
    d__13 = *vv;
/* Computing 2nd power */
    d__14 = eta;
/* Computing 4th power */
    d__15 = vr, d__15 *= d__15;
/* Computing 2nd power */
    d__16 = eta;
/* Computing 2nd power */
    d__17 = vr;
/* Computing 2nd power */
    d__18 = eta;
/* Computing 2nd power */
    d__19 = *vv;
/* Computing 2nd power */
    d__20 = vr;
/* Computing 2nd power */
    d__21 = eta;
/* Computing 4th power */
    d__22 = vr, d__22 *= d__22;
    outpa1a2ctc_1.a3 = ((116.58333333333333f - pi2 * 2.5625f) * eta + 16 + 
	    eta * 35.5f * eta) * (d__1 * (d__1 * d__1)) + eta * (pi2 * 
	    1.921875f + 24.794047619047618f - d__2 * d__2) * (d__3 * d__3) * *
	    vv - ((pi2 * 9.609375f + 135.2202380952381f) * eta + 1 + d__4 * 
	    d__4 * 1.375f - d__5 * (d__5 * d__5) * 7) * (d__6 * d__6) * (d__7 
	    * d__7) - eta * .25 * (11 - eta * 49 + d__8 * d__8 * 52) * (d__9 *
	     (d__9 * d__9)) + eta * 2.1875f * (1 - eta * 5 + d__10 * d__10 * 
	    5) * (d__11 * (d__11 * d__11)) - eta * .25 * (eta * 32 + 75 - 
	    d__12 * d__12 * 40) * (m / *r__) * (d__13 * d__13) - eta * .5 * (
	    158 - eta * 69 - d__14 * d__14 * 60) * (m / *r__) * (d__15 * 
	    d__15) + eta * (121 - eta * 16 - d__16 * d__16 * 20) * (m / *r__) 
	    * *vv * (d__17 * d__17) + eta * .375f * (20 - eta * 79 + d__18 * 
	    d__18 * 60) * (d__19 * d__19) * (d__20 * d__20) - eta * 1.875f * (
	    4 - eta * 18 + d__21 * d__21 * 17) * *vv * (d__22 * d__22);
/* Computing 2nd power */
    d__1 = m / *r__;
/* Computing 2nd power */
    d__2 = *vv;
/* Computing 4th power */
    d__3 = vr, d__3 *= d__3;
/* Computing 2nd power */
    d__4 = vr;
/* Computing 2nd power */
    d__5 = vr;
    outpa1a2ctc_1.a3p5 = eta * -1.6000000000000001f * (m / *r__) * vr * ((eta 
	    * 14 + 43) * 1.6428571428571428f * (d__1 * d__1) + (eta * 70 + 61)
	     * .10714285714285714f * (d__2 * d__2) + d__3 * d__3 * 70 + (519 
	    - eta * 1267) * .023809523809523808f * (m / *r__) * *vv + (eta * 
	    188 + 147) * .25 * (m / *r__) * (d__4 * d__4) - (eta * 2 + 19) * 
	    3.75f * *vv * (d__5 * d__5));
    outpa1a2ctc_1.b1 = (2 - eta) * 2 * vr;
/* Computing 2nd power */
    d__1 = eta;
/* Computing 2nd power */
    d__2 = vr;
    outpa1a2ctc_1.b2 = vr * -.5 * ((eta * 41 + 4 + d__1 * d__1 * 8) * (m / *
	    r__) - eta * (eta * 4 + 15) * *vv + eta * 3 * (eta * 2 + 3) * (
	    d__2 * d__2));
    outpa1a2ctc_1.b2p5 = eta * -1.6000000000000001f * (m / *r__) * (m / *r__ *
	     3 + *vv);
/* Computing 2nd power */
    d__1 = eta;
/* Computing 3rd power */
    d__2 = eta;
/* Computing 2nd power */
    d__3 = m / *r__;
/* Computing 2nd power */
    d__4 = eta;
/* Computing 2nd power */
    d__5 = *vv;
/* Computing 2nd power */
    d__6 = eta;
/* Computing 4th power */
    d__7 = vr, d__7 *= d__7;
/* Computing 2nd power */
    d__8 = eta;
/* Computing 2nd power */
    d__9 = eta;
/* Computing 2nd power */
    d__10 = vr;
/* Computing 2nd power */
    d__11 = eta;
/* Computing 2nd power */
    d__12 = vr;
    outpa1a2ctc_1.b3 = vr * (((pi2 * 3.84375f + 6.9630952380952378f) * eta + 
	    4 - d__1 * d__1 * 25 - d__2 * (d__2 * d__2) * 8) * (d__3 * d__3) 
	    + eta * .125f * (65 - eta * 152 - d__4 * d__4 * 48) * (d__5 * 
	    d__5) + eta * 1.875f * (3 - eta * 8 - d__6 * d__6 * 2) * (d__7 * 
	    d__7) + eta * (eta * 27 + 15 + d__8 * d__8 * 10) * (m / *r__) * *
	    vv - eta * .16666666666666666f * (eta * 177 + 329 + d__9 * d__9 * 
	    108) * (m / *r__) * (d__10 * d__10) - eta * .75f * (16 - eta * 37 
	    - d__11 * d__11 * 16) * *vv * (d__12 * d__12));
/* Computing 2nd power */
    d__1 = m / *r__;
/* Computing 2nd power */
    d__2 = *vv;
/* Computing 4th power */
    d__3 = vr, d__3 *= d__3;
/* Computing 2nd power */
    d__4 = vr;
/* Computing 2nd power */
    d__5 = vr;
    outpa1a2ctc_1.b3p5 = eta * 1.6000000000000001f * (m / *r__) * ((eta * 546 
	    + 1325) * .023809523809523808f * (d__1 * d__1) + (eta * 42 + 313) 
	    * .035714285714285712f * (d__2 * d__2) + d__3 * d__3 * 75 - (eta *
	     777 + 205) * .023809523809523808f * (m / *r__) * *vv + (eta * 
	    424 + 205) * .083333333333333329f * (m / *r__) * (d__4 * d__4) - (
	    eta * 2 + 113) * .75f * *vv * (d__5 * d__5));
/*                A3p5=0 */
/*                B3p5=0 */
/*                A2p5=0 */
/*                B2p5=0 */
/*                A3=0 */
/*                B3=0 */
/* Computing 2nd power */
    d__1 = *c__;
/* Computing 4th power */
    d__2 = *c__, d__2 *= d__2;
/* Computing 5th power */
    d__3 = *c__, d__4 = d__3, d__3 *= d__3;
    atot = outpa1a2ctc_1.a1 / (d__1 * d__1) + outpa1a2ctc_1.a2 / (d__2 * d__2)
	     + outpa1a2ctc_1.a2p5 / (d__4 * (d__3 * d__3));
/* +A3/c**6+A3p5/c**7 */
/* Computing 2nd power */
    d__1 = *c__;
/* Computing 4th power */
    d__2 = *c__, d__2 *= d__2;
/* Computing 5th power */
    d__3 = *c__, d__4 = d__3, d__3 *= d__3;
    btot = outpa1a2ctc_1.b1 / (d__1 * d__1) + outpa1a2ctc_1.b2 / (d__2 * d__2)
	     + outpa1a2ctc_1.b2p5 / (d__4 * (d__3 * d__3));
/* +B3/c**6+B3p5/c**7 */
/* Computing 5th power */
    d__1 = *c__, d__2 = d__1, d__1 *= d__1;
    afric = outpa1a2ctc_1.a2p5 / (d__2 * (d__1 * d__1));
/* +A3p5/c**7 ! *0 if you want to */
/* Computing 5th power */
    d__1 = *c__, d__2 = d__1, d__1 *= d__1;
    bfric = outpa1a2ctc_1.b2p5 / (d__2 * (d__1 * d__1));
/* +B3p5/c**7 ! *0    -"- */
    if (*i1 == 1) {
	gopu_spinterms__(&x[1], &v[1], r__, m1, m2, c__, &spina[1], dvq, &
		dspin[1]);
/* spinterms */
    } else {
	for (k = 1; k <= 3; ++k) {
	    dvq[k - 1] = 0.;
	    dspin[k] = 0.;
	}
    }
    for (k = 1; k <= 3; ++k) {
/* Computing 2nd power */
	d__1 = *r__;
	dv[k] = -m / (d__1 * d__1) * (n[k - 1] * atot + v[k] * btot) / m - 
		dvq[k - 1] / m;
/* in the code */
/* Computing 2nd power */
	d__1 = *r__;
	dvgr[k] = -m / (d__1 * d__1) * (n[k - 1] * afric + v[k] * bfric) / m;
    }
/*          turhia */
/*           rw=r/(2*m/c**2) */
/*           fr=cdot(x,dV)/r */
/*           frm=fr-m/r**2 */
    return 0;
} /* relativisticterms_ */

/* Subroutine */ int reduce2cm_(doublereal *x, doublereal *m, integer *nb, 
	doublereal *cm)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;
    static doublereal sm;

    /* Parameter adjustments */
    --cm;
    --m;
    --x;

    /* Function Body */
    cm[1] = 0.;
    cm[2] = 0.;
    cm[3] = 0.;
    sm = 0.;
    i__1 = *nb;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sm += m[i__];
	for (k = 1; k <= 3; ++k) {
	    cm[k] += m[i__] * x[k + (i__ - 1) * 3];
	}
    }
    for (k = 1; k <= 3; ++k) {
	cm[k] /= sm;
    }
    i__1 = *nb;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (k = 1; k <= 3; ++k) {
	    x[k + (i__ - 1) * 3] -= cm[k];
	}
    }
    return 0;
} /* reduce2cm_ */

/* Subroutine */ int cross_(doublereal *a, doublereal *b, doublereal *c__)
{
    /* Parameter adjustments */
    --c__;
    --b;
    --a;

    /* Function Body */
    c__[1] = a[2] * b[3] - a[3] * b[2];
    c__[2] = a[3] * b[1] - a[1] * b[3];
    c__[3] = a[1] * b[2] - a[2] * b[1];
    return 0;
} /* cross_ */

/* Subroutine */ int gopu_spinterms__(doublereal *x, doublereal *v, 
	doublereal *r__, doublereal *m1, doublereal *m2, doublereal *c__, 
	doublereal *alpha, doublereal *dv3, doublereal *dalpha)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal j[3];
    static integer k;
    static doublereal m, n[3], w[3], q2, aq, bq, cq, sj, sq, eta, nxa[3], sjj,
	     vxa[3], dv_q__[3];
    extern doublereal cdot_(doublereal *, doublereal *);
    static doublereal rdot, anxv, coeff;
    extern /* Subroutine */ int cross_(doublereal *, doublereal *, doublereal 
	    *), q2term_(doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *);

/* ,trh(3) ! TEST */
/* This routine assumes: The BH mass M1>>m2. Spin of */
/* m2 is neglected. */
    /* Parameter adjustments */
    --dalpha;
    --dv3;
    --alpha;
    --v;
    --x;

    /* Function Body */
    for (k = 1; k <= 3; ++k) {
	n[k - 1] = x[k] / *r__;
    }
    m = *m1 + *m2;
/* Computing 2nd power */
    d__1 = m;
    eta = *m1 * *m2 / (d__1 * d__1);
    sq = sqrt(1 - eta * 4);
    aq = -12 / (sq + 1);
    bq = -6 / (sq + 1) - 3;
    cq = 6 / (sq + 1) + 1;
    rdot = cdot_(n, &v[1]);
    cross_(n, &v[1], w);
    anxv = cdot_(&alpha[1], w);
    cross_(n, &alpha[1], nxa);
    cross_(&v[1], &alpha[1], vxa);
    for (k = 1; k <= 3; ++k) {
/* Computing 2nd power */
	d__1 = *m1;
/* Computing 3rd power */
	d__2 = *c__ * *r__;
	dv3[k] = -(d__1 * d__1) / (d__2 * (d__2 * d__2)) * (aq * anxv * n[k - 
		1] + rdot * bq * nxa[k - 1] + cq * vxa[k - 1]);
    }
/* Computing 2nd power */
    d__1 = *c__ * *r__;
    coeff = eta * m / (d__1 * d__1) * (3 / (sq + 1) + .5);
    cross_(w, &alpha[1], &dalpha[1]);
    for (k = 1; k <= 3; ++k) {
	dalpha[k] = coeff * dalpha[k];
    }
/*  C.Will Q2-terms */
    sjj = 0.;
    for (k = 1; k <= 3; ++k) {
/* Computing 2nd power */
	d__1 = *m1;
	j[k - 1] = d__1 * d__1 / *c__ * alpha[k];
/* Computing 2nd power */
	d__1 = j[k - 1];
	sjj += d__1 * d__1;
    }
    sj = sqrt(sjj);
    if (sj != 0.f) {
/* if sj=0, then J(k)=0 and Q-term =0 anyway */
	for (k = 1; k <= 3; ++k) {
	    j[k - 1] /= sj;
	}
    }
/* Computing 2nd power */
    d__1 = *c__;
    q2 = -sjj / *m1 / (d__1 * d__1);
/*        do k=1,3 */
/*       trh(k)=dv3(k)  ! add Quadrupole terms */
/*     &  +1.5*Q2/r**4*(n(k)*(5*cdot(n,j)**2-1)-2*cdot(n,j)*j(k)) */
/*        end do */
/*  X=X_j-X_i in this code */
    q2 = -q2;
/* earlier we had Q2 grad Q-Potential, now grad Q-ForceFun */
    q2term_(m1, r__, &x[1], &v[1], c__, &q2, j, dv_q__);
    for (k = 1; k <= 3; ++k) {
	dv3[k] += dv_q__[k - 1];
/* add quadrupole terms (these are more cor */
    }
    return 0;
} /* gopu_spinterms__ */

/* Subroutine */ int q2term_(doublereal *m, doublereal *r__, doublereal *x, 
	doublereal *v, doublereal *c__, doublereal *q2, doublereal *e, 
	doublereal *dvq)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3, d__4, d__5, d__6, d__7;

    /* Local variables */
    static integer k;
    static doublereal oc, er, rx[3], vv, ux[3], u2b, rq2, vrx;
    extern doublereal cdot_(doublereal *, doublereal *);

/* m=m1+m2 (?),vv=v**2 */
/* e=spin direction;  Q2=m**3/c**4*xi**2, xi=|spin|=Kerr parameter */
    /* Parameter adjustments */
    --dvq;
    --e;
    --v;
    --x;

    /* Function Body */
    vv = cdot_(&v[1], &v[1]);
    er = cdot_(&e[1], &x[1]);
/* Computing 2nd power */
    d__1 = er / *r__;
/* Computing 3rd power */
    d__2 = *r__;
    rq2 = (d__1 * d__1 * 3 - 1) / (d__2 * (d__2 * d__2) * 2);
/* the quadrupole pot (exept 4 facto */
    u2b = *m / *r__;
    oc = 1 / *c__;
    for (k = 1; k <= 3; ++k) {
/* Computing 3rd power */
	d__1 = *r__;
	ux[k - 1] = -x[k] * *m / (d__1 * (d__1 * d__1));
/* two-body acceleration */
/* Computing 5th power */
	d__1 = *r__, d__2 = d__1, d__1 *= d__1;
/* Computing 2nd power */
	d__3 = er;
/* Computing 6th power */
	d__4 = *r__, d__4 *= d__4;
/* Computing 2nd power */
	d__5 = er;
/* Computing 2nd power */
	d__6 = *r__;
/* Computing 4th power */
	d__7 = *r__, d__7 *= d__7;
	rx[k - 1] = e[k] * 3 * er / (d__2 * (d__1 * d__1)) + x[k] * (d__3 * 
		d__3 * -3 / (d__4 * (d__4 * d__4)) - (d__5 * d__5 * 3 / (d__6 
		* d__6) - 1) * 3 / (d__7 * d__7 * 2)) / *r__;
/* qua */
    }
    vrx = cdot_(&v[1], rx);
    for (k = 1; k <= 3; ++k) {
/* complete quadrupole term in \dot v */
/* Computing 2nd power */
	d__1 = oc;
/* Computing 2nd power */
	d__2 = oc;
	dvq[k] = *q2 * (rx[k - 1] * (d__1 * d__1 * ((*q2 * rq2 + u2b) * -4 + 
		vv) + 1) - d__2 * d__2 * 4 * (rq2 * ux[k - 1] + vrx * v[k]));
    }
    return 0;
} /* q2term_ */

/* Subroutine */ int initialstepsize_(doublereal *x, doublereal *v, 
	doublereal *m, integer *nb, doublereal *ee, doublereal *step)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal t, u, r1, r2;
    static integer ki, kj;
    static doublereal time_step2__, vv, vx, vy, xx, vz, yy, zz, mij, alag, 
	    mass, rmin, energy;

    /* Parameter adjustments */
    --m;
    --v;
    --x;

    /* Function Body */
    t = 0.f;
    u = 0.f;
    rmin = 1e30;
    mass = m[*nb];
    time_step2__ = 1e30f;
    i__1 = *nb - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	mass += m[i__];
	i__2 = *nb;
	for (j = i__ + 1; j <= i__2; ++j) {
	    mij = m[i__] * m[j];
	    ki = (i__ - 1) * 3;
	    kj = (j - 1) * 3;
	    xx = x[ki + 1] - x[kj + 1];
	    yy = x[ki + 2] - x[kj + 2];
	    zz = x[ki + 3] - x[kj + 3];
	    r2 = xx * xx + yy * yy + zz * zz + *ee;
	    vx = v[ki + 1] - v[kj + 1];
	    vy = v[ki + 2] - v[kj + 2];
	    vz = v[ki + 3] - v[kj + 3];
	    vv = vx * vx + vy * vy + vz * vz;
	    r1 = sqrt(r2);
/* Computing MIN */
	    d__1 = time_step2__, d__2 = r2 / (vv + (m[i__] + m[j]) / r1);
	    time_step2__ = min(d__1,d__2);
/* ~2B radius o */
	    u += mij / r1;
	    t += mij * (vx * vx + vy * vy + vz * vz);
	}
    }
    t /= mass * 2;
    energy = t - u;
    alag = t + u;
    *step = u * .1f * sqrt(time_step2__);
    return 0;
} /* initialstepsize_ */

/* Subroutine */ int elmnts_(doublereal *x, doublereal *v, doublereal *m, 
	doublereal *a, doublereal *e, doublereal *mo, doublereal *inc, 
	doublereal *om, doublereal *oo, doublereal *alfa, doublereal *q, 
	doublereal *tq)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal b, d__;
    static integer k;
    static doublereal r__, w[3], w2, ex, ey, ez, jx, jy, jz, mu, eta, too;
    extern doublereal oot_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), atn2_(doublereal *, 
	    doublereal *);
    static doublereal sqaf, zeta;

/*       NOTE: wrong results can be produced in exeptional situations */
/*       where some angles are undefined in terms of the expressions used. */
/*       This may happen in exactly planar, rectilinear .. orbits */
/*       Troubles can often be avoided by a very small 'perturbation' of x and/or v. */
    /* Parameter adjustments */
    --v;
    --x;

    /* Function Body */
    mu = sqrt(*m);
    for (k = 1; k <= 3; ++k) {
	w[k - 1] = v[k] / mu;
    }
/* Computing 2nd power */
    d__1 = x[1];
/* Computing 2nd power */
    d__2 = x[2];
/* Computing 2nd power */
    d__3 = x[3];
    r__ = sqrt(d__1 * d__1 + d__2 * d__2 + d__3 * d__3);
/* Computing 2nd power */
    d__1 = w[0];
/* Computing 2nd power */
    d__2 = w[1];
/* Computing 2nd power */
    d__3 = w[2];
    w2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
    eta = x[1] * w[0] + x[2] * w[1] + x[3] * w[2];
    *alfa = 2 / r__ - w2;
    zeta = 1 - *alfa * r__;
/*       areal velocity vector (jx,jy,jz) */
    jx = x[2] * w[2] - x[3] * w[1];
    jy = x[3] * w[0] - x[1] * w[2];
    jz = x[1] * w[1] - x[2] * w[0];
    d__ = sqrt(jx * jx + jy * jy + jz * jz);
/*       eccentricity vector (ex,ey,ez) */
    ex = w[1] * jz - w[2] * jy - x[1] / r__;
    ey = w[2] * jx - w[0] * jz - x[2] / r__;
    ez = w[0] * jy - w[1] * jx - x[3] / r__;
    *e = sqrt(ex * ex + ey * ey + ez * ez);
    b = sqrt(jx * jx + jy * jy);
    *inc = atn2_(&b, &jz) * 57.295779513082323;
    d__1 = -jy;
    *om = atn2_(&jx, &d__1) * 57.295779513082323;
    d__1 = ez * d__;
    d__2 = ey * jx - ex * jy;
    *oo = atn2_(&d__1, &d__2) * 57.295779513082323;
    *a = 1 / *alfa;
    sqaf = sqrt((abs(*alfa)));
    *q = d__ * d__ / (*e + 1);
    too = oot_(alfa, &eta, &zeta, q, e, &sqaf);
    *tq = too / mu;
/* Computing 3rd power */
    d__1 = sqaf;
    *mo = too * (d__1 * (d__1 * d__1)) * 57.295779513082323;
    return 0;
} /* elmnts_ */

doublereal atn2_(doublereal *s, doublereal *c__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double atan2(doublereal, doublereal);

    ret_val = atan2(*s, *c__);
    if (ret_val < 0.f) {
	ret_val += 6.2831853071795862;
    }
    return ret_val;
} /* atn2_ */

doublereal oot_(doublereal *alfa, doublereal *eta, doublereal *zeta, 
	doublereal *q, doublereal *e, doublereal *sqaf)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double atan2(doublereal, doublereal);

    /* Local variables */
    static doublereal x, z__;
    extern doublereal g3_(doublereal *);
    static doublereal ecc;

/*       alfa=1/a; eta=sqrt(a) e sin(E); zeta=e Cos(E), */
/*       q=a(1-e), e=ecc, sqaf=sqrt(|a|) */
/* oot=pericentre time */
    if (*zeta > 0.f) {
/*        ellipse (near peri), parabola or hyperbola. */
	ecc = max(*e,1e-18);
	x = *eta / ecc;
	z__ = *alfa * x * x;
	ret_val = x * (*q + x * x * g3_(&z__));
    } else {
/*       upper half of an elliptic orbit. */
	ret_val = (atan2(*eta * *sqaf, *zeta) / *sqaf - *eta) / *alfa;
    }
    return ret_val;
} /* oot_ */

doublereal g3_(doublereal *z__)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double sqrt(doublereal), asin(doublereal), log(doublereal);

    /* Local variables */
    static doublereal x;

    if (*z__ > .025) {
/* elliptic */
	x = sqrt(*z__);
/* Computing 3rd power */
	d__1 = x;
	ret_val = (asin(x) - x) / (d__1 * (d__1 * d__1));
    } else if (*z__ < -.025) {
/* hyperbolic */
	x = sqrt(-(*z__));
	ret_val = (log(x + sqrt(x * x + 1)) - x) / x / *z__;
    } else {
/*       g3 = (1/6.d0-19177*z/170280 + 939109*z*z/214552800)/ */
/*     &  (1-7987*z/7095 + 54145*z*z/204336) */
/* Pade approximant for small  |z| */
	ret_val = ((*z__ * -19177 / 170280 + *z__ * 939109 * *z__ / 214552800)
		 * 6 + 1) / ((1 - *z__ * 7987 / 7095 + *z__ * 54145 * *z__ / 
		204336) * 6);
	mita_1.zero = 0.;
    }
    return ret_val;
} /* g3_ */

/* Subroutine */ int constantsofmotion_(doublereal *ene_nb__, doublereal *g, 
	doublereal *alag)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal t, u;
    static integer k1, k2, k3;
    static doublereal r2;
    extern doublereal wfunction_(void);
    static integer ik, jk, ki, kj;
    static doublereal vx, vy, xx, vz, yy, zz, mij, rmin, omegab;

/*        IMPLICIT real*8 (A-H,m,O-Z) */
/*        DIMENSION G(3) */
/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*       Contants of motion in the centre-of-mass system. */
    /* Parameter adjustments */
    --g;

    /* Function Body */
    t = 0.f;
    u = 0.f;
    g[1] = 0.f;
    g[2] = 0.f;
    g[3] = 0.f;
    rmin = 1e30;
/*        mass=M(N) */
    i__1 = dataforroutines1_1.n - 1;
    for (ik = 1; ik <= i__1; ++ik) {
	i__ = dataforroutines1_1.iname[ik - 1];
/*        mass=mass+M(I) */
/* along the chain */
	i__2 = dataforroutines1_1.n;
	for (jk = ik + 1; jk <= i__2; ++jk) {
	    j = dataforroutines1_1.iname[jk - 1];
/*  -"- */
	    mij = dataforroutines1_1.m[i__ - 1] * dataforroutines1_1.m[j - 1];
	    ki = (i__ - 1) * 3;
	    kj = (j - 1) * 3;
	    if (jk != ik + 1) {
		xx = dataforroutines1_1.x[ki] - dataforroutines1_1.x[kj];
		yy = dataforroutines1_1.x[ki + 1] - dataforroutines1_1.x[kj + 
			1];
		zz = dataforroutines1_1.x[ki + 2] - dataforroutines1_1.x[kj + 
			2];
		vx = dataforroutines1_1.v[ki] - dataforroutines1_1.v[kj];
		vy = dataforroutines1_1.v[ki + 1] - dataforroutines1_1.v[kj + 
			1];
		vz = dataforroutines1_1.v[ki + 2] - dataforroutines1_1.v[kj + 
			2];
	    } else {
		k1 = ik * 3 - 2;
		k2 = k1 + 1;
		k3 = k2 + 1;
		xx = dataforroutines1_1.xc[k1 - 1];
/* use chain vectors when possible */
		yy = dataforroutines1_1.xc[k2 - 1];
/* (this often reduces roundoff) */
		zz = dataforroutines1_1.xc[k3 - 1];
		vx = dataforroutines1_1.wc[k1 - 1];
		vy = dataforroutines1_1.wc[k2 - 1];
		vz = dataforroutines1_1.wc[k3 - 1];
	    }
	    r2 = xx * xx + yy * yy + zz * zz + softening_1.ee;
	    u += mij / sqrt(r2);
	    t += mij * (vx * vx + vy * vy + vz * vz);
	    g[1] += mij * (yy * vz - zz * vy);
	    g[2] += mij * (zz * vx - xx * vz);
	    g[3] += mij * (xx * vy - yy * vx);
	}
    }
    t /= dataforroutines1_1.mass * 2;
    g[1] /= dataforroutines1_1.mass;
    g[2] /= dataforroutines1_1.mass;
    g[3] /= dataforroutines1_1.mass;
    *ene_nb__ = t - u;
    *alag = t + u;
    justforfun_1.tkin = t;
/* to justforfun */
    justforfun_1.upot = u;
/* to justforfun */
    omegab = wfunction_();
    justforfun_1.dskin = softening_1.cmethod[0] * (t - 
	    dataforchainroutinestwo_1.energy - 
	    dataforchainroutinestwo_1.energr) + softening_1.cmethod[1] * 
	    dataforroutines1_1.wttl + softening_1.cmethod[2];
    justforfun_1.dspot = softening_1.cmethod[0] * u + softening_1.cmethod[1] *
	     omegab + softening_1.cmethod[2];
    return 0;
} /* constantsofmotion_ */

/* Subroutine */ int findbinaries_(doublereal *time)
{
    /* Format strings */
    static char fmt_123[] = "(1x,f12.1,\002 BINARY:(\002,i3,\002,\002,i3,"
	    "\002)\002,\002 A=\002,1p,g12.2,\002 e=\002,0p,f10.4)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, k;
    static doublereal r__, w[3], r2, w2, oa;
    static integer li, lj;
    static doublereal om, xx[3], oa0, ecc, eta, ecc2, zeta;
    extern /* Subroutine */ int flush_(integer *);

    /* Fortran I/O blocks */
    static cilist io___492 = { 0, 88, 0, fmt_123, 0 };


/* this is a toy analysis routine */
/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/*     SEARCH FOR BINARIES [diagnostics only] */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = dataforroutines1_1.n;
	for (j = i__ + 1; j <= i__2; ++j) {
	    li = (i__ - 1) * 3;
	    lj = (j - 1) * 3;
	    om = 1.f / sqrt(dataforroutines1_1.m[i__ - 1] + 
		    dataforroutines1_1.m[j - 1]);
	    for (k = 1; k <= 3; ++k) {
		xx[k - 1] = dataforroutines1_1.x[li + k - 1] - 
			dataforroutines1_1.x[lj + k - 1];
		w[k - 1] = (dataforroutines1_1.v[li + k - 1] - 
			dataforroutines1_1.v[lj + k - 1]) * om;
	    }
/* Computing 2nd power */
	    d__1 = xx[0];
/* Computing 2nd power */
	    d__2 = xx[1];
/* Computing 2nd power */
	    d__3 = xx[2];
	    r2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
	    eta = xx[0] * w[0] + xx[1] * w[1] + xx[2] * w[2];
/* Computing 2nd power */
	    d__1 = w[0];
/* Computing 2nd power */
	    d__2 = w[1];
/* Computing 2nd power */
	    d__3 = w[2];
	    w2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
	    r__ = sqrt(r2);
	    oa = 2.f / r__ - w2;
	    zeta = 1.f - oa * r__;
/* Computing 2nd power */
	    d__1 = zeta;
/* Computing 2nd power */
	    d__2 = eta;
	    ecc2 = d__1 * d__1 + oa * (d__2 * d__2);
	    ecc = sqrt(ecc2);
	    oa0 = (dataforroutines1_1.n - 2) * 2.f / (dataforroutines1_1.rsum 
		    + 1e-20f);
	    if (oa > oa0) {
		s_wsfe(&io___492);
		do_fio(&c__1, (char *)&(*time), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		d__1 = 1.f / oa;
		do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ecc, (ftnlen)sizeof(doublereal));
		e_wsfe();
		flush_(&c__88);
	    }
	}
    }
    return 0;
} /* findbinaries_ */

/* Subroutine */ int wcmotion_(doublereal *hs)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal a, f[600];
    static integer i__, j, k, l;
    static doublereal u;
    static integer i0, j0;
    extern /* Subroutine */ int evaluatex_(void);
    static doublereal af, fc[600];
    static integer li, lj;
    static doublereal dt;
    extern /* Subroutine */ int coordinatedependentperturbations_(doublereal *
	    ), v_jacconly__(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal acc[600], gom[600];
    static integer lri;
    static doublereal rij2, rijl, xaux[3], rijl2, omega, omeker;
    extern /* Subroutine */ int v_jump__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static doublereal rij2inv, energrj, energyj;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/* df(nmx3),dfGR(nmx3), */
/* ,dcmv(3),Va(nmx3),afc(nmx3),dfE(3),dspin(3) */
    evaluatex_();
    dataforroutines1_1.rsum = 0.f;
    omega = 0.;
    u = 0.;
    i__1 = dataforroutines1_1.n * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	f[i__ - 1] = 0.;
	gom[i__ - 1] = 0.;
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
/* Computing 2nd power */
	d__1 = dataforroutines1_1.xc[l];
/* Computing 2nd power */
	d__2 = dataforroutines1_1.xc[l + 1];
/* Computing 2nd power */
	d__3 = dataforroutines1_1.xc[l + 2];
	rijl2 = d__1 * d__1 + d__2 * d__2 + d__3 * d__3 + softening_1.ee;
	rijl = sqrt(rijl2);
/*        Evaluate RSUM for decisionmaking. */
	dataforroutines1_1.rsum += rijl;
	dataforroutines1_1.rinv[i__ - 1] = 1. / rijl;
	u += dataforroutines1_1.mc[i__ - 1] * dataforroutines1_1.mc[i__] * 
		dataforroutines1_1.rinv[i__ - 1];
/* Computing 3rd power */
	d__1 = dataforroutines1_1.rinv[i__ - 1];
	a = d__1 * (d__1 * d__1);
	i0 = i__ * 3 - 3;
	j = i__ + 1;
	j0 = j * 3 - 3;
	omeker = omegacoefficients_1.omec[dataforroutines1_1.iname[i__ - 1] + 
		dataforroutines1_1.iname[j - 1] * 200 - 201];
	for (k = 1; k <= 3; ++k) {
	    af = a * dataforroutines1_1.xc[i0 + k - 1];
	    f[i0 + k - 1] += dataforroutines1_1.mc[j - 1] * af;
	    f[j0 + k - 1] -= dataforroutines1_1.mc[i__ - 1] * af;
	    if (softening_1.cmethod[1] != 0. && omeker != 0.f) {
		gom[i0 + k - 1] += af * omeker;
		gom[j0 + k - 1] -= af * omeker;
	    }
	}
	if (softening_1.cmethod[1] != 0.f && omeker != 0.f) {
	    omega += omeker * dataforroutines1_1.rinv[i__ - 1];
	}
    }
    lri = dataforroutines1_1.n - 1;
/*       Physical coordinates */
    for (k = 1; k <= 3; ++k) {
	dataforroutines1_1.xi[k - 1] = 0.f;
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    dataforroutines1_1.xi[l + 3 + k - 1] = dataforroutines1_1.xi[l + 
		    k - 1] + dataforroutines1_1.xc[l + k - 1];
	}
    }
/*        Non-chained contribution */
    i__1 = dataforroutines1_1.n - 2;
    for (i__ = 1; i__ <= i__1; ++i__) {
	li = (i__ - 1) * 3;
	i__2 = dataforroutines1_1.n;
	for (j = i__ + 2; j <= i__2; ++j) {
	    lj = (j - 1) * 3;
	    rij2 = softening_1.ee + 0.f;
	    if (j > i__ + 2) {
		for (k = 1; k <= 3; ++k) {
		    xaux[k - 1] = dataforroutines1_1.xi[lj + k - 1] - 
			    dataforroutines1_1.xi[li + k - 1];
/* Computing 2nd power */
		    d__1 = xaux[k - 1];
		    rij2 += d__1 * d__1;
		}
	    } else {
		for (k = 1; k <= 3; ++k) {
		    xaux[k - 1] = dataforroutines1_1.xc[li + k - 1] + 
			    dataforroutines1_1.xc[li + k + 2];
/* Computing 2nd power */
		    d__1 = xaux[k - 1];
		    rij2 += d__1 * d__1;
		}
	    }
	    rij2inv = 1 / rij2;
	    ++lri;
	    dataforroutines1_1.rinv[lri - 1] = sqrt(rij2inv);
	    u += dataforroutines1_1.mc[i__ - 1] * dataforroutines1_1.mc[j - 1]
		     * dataforroutines1_1.rinv[lri - 1];
	    omeker = omegacoefficients_1.omec[dataforroutines1_1.iname[i__ - 
		    1] + dataforroutines1_1.iname[j - 1] * 200 - 201];
	    if (omeker != 0.f && softening_1.cmethod[1] != 0.f) {
		omega += omeker * dataforroutines1_1.rinv[lri - 1];
	    }
	    for (k = 1; k <= 3; ++k) {
/* Computing 3rd power */
		d__1 = dataforroutines1_1.rinv[lri - 1];
		a = d__1 * (d__1 * d__1) * xaux[k - 1];
		f[li + k - 1] += dataforroutines1_1.mc[j - 1] * a;
		f[lj + k - 1] -= dataforroutines1_1.mc[i__ - 1] * a;
		if (softening_1.cmethod[1] != 0. && omeker != 0.f) {
		    gom[li + k - 1] += a * omeker;
		    gom[lj + k - 1] -= a * omeker;
		}
	    }
	}
/* J=I+2,N */
    }
/* I=1,N-2 */
    dt = *hs / (u * softening_1.cmethod[0] + omega * softening_1.cmethod[1] + 
	    softening_1.cmethod[2]);
/* time interva */
    coordinatedependentperturbations_(acc);
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (k = 1; k <= 3; ++k) {
	    l = (i__ - 1) * 3;
	    fc[l + k - 1] = f[i__ * 3 + k - 1] - f[i__ * 3 + k - 4];
	}
    }
    if (softening_1.clight > 0.f) {
/* V-dependent ACC */
	d__1 = dt / 2;
	v_jump__(vwcommon_1.ww, vwcommon_1.spinw, vwcommon_1.cmvw, &
		vwcommon_1.wttlw, dataforroutines1_1.wc, spincommon_1.spin, 
		fc, acc, &d__1, gom, &energyj, &energrj, &c__1);
/* Auxiliary W (=Ww) etc */
	v_jump__(dataforroutines1_1.wc, spincommon_1.spin, 
		dataforchainroutinestwo_1.cmv, &dataforroutines1_1.wttl, 
		vwcommon_1.ww, vwcommon_1.spinw, fc, acc, &dt, gom, &
		dataforchainroutinestwo_1.energy, &
		dataforchainroutinestwo_1.energr, &c__2);
/* 'true' W  etc */
	d__1 = dt / 2;
	v_jump__(vwcommon_1.ww, vwcommon_1.spinw, vwcommon_1.cmvw, &
		vwcommon_1.wttlw, dataforroutines1_1.wc, spincommon_1.spin, 
		fc, acc, &d__1, gom, &energyj, &energrj, &c__3);
/* Auxiliary W (=Ww) ets */
    } else {
/* c>0 */
	v_jacconly__(dataforroutines1_1.wc, dataforchainroutinestwo_1.cmv, &
		dataforroutines1_1.wttl, fc, acc, &dt, gom, &
		dataforchainroutinestwo_1.energy, &energrj);
/* here ACC depends ONLY on COORDINATES */
    }
    return 0;
} /* wcmotion_ */

/* Subroutine */ int v_jump__(doublereal *wcj, doublereal *spinj, doublereal *
	cmvj, doublereal *wttlj, doublereal *wci, doublereal *spini, 
	doublereal *fcj, doublereal *acc, doublereal *dt, doublereal *gom, 
	doublereal *energyj, doublereal *energrj, integer *ind)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    extern /* Subroutine */ int velocitydependentperturbations_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer i__, k, l, i0, i1, i2, k0;
    extern /* Subroutine */ int evaluatev_(doublereal *, doublereal *);
    static doublereal df[600], afc[600], dfe[600], dfgr[600], dcmv[3], dote, 
	    dotw, dspin[3], dotegr;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --gom;
    --acc;
    --fcj;
    --spini;
    --wci;
    --cmvj;
    --spinj;
    --wcj;

    /* Function Body */
    evaluatev_(dataforroutines1_1.v, &wci[1]);
/* adding V-dependent perts. */
    if (softening_1.clight > 0.f) {
	velocitydependentperturbations_(dt, dataforroutines1_1.v, &spini[1], &
		acc[1], dcmv, df, dfgr, dspin);
    } else {
	i__1 = dataforroutines1_1.n * 3;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    df[i__ - 1] = acc[i__];
	}
    }
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = i__ * 3 - 3;
	i1 = dataforroutines1_1.iname[i__ - 1] * 3 - 3;
	i2 = dataforroutines1_1.iname[i__] * 3 - 3;
	for (k = 1; k <= 3; ++k) {
	    afc[l + k - 1] = df[i2 + k - 1] - df[i1 + k - 1];
	}
    }
    if (*ind == 2) {
	dote = 0.;
	dotegr = 0.;
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i0 = i__ * 3 - 3;
	    for (k = 1; k <= 3; ++k) {
		dfe[k - 1] = df[i0 + k - 1] - dfgr[i0 + k - 1];

	    }
	    dote += dataforroutines1_1.m[i__ - 1] * (dataforroutines1_1.v[i0] 
		    * dfe[0] + dataforroutines1_1.v[i0 + 1] * dfe[1] + 
		    dataforroutines1_1.v[i0 + 2] * dfe[2]);
/* NB-Energy change (without Grav.Rad.) */
/* % */
	    for (k = 1; k <= 3; ++k) {
		dfe[k - 1] = dfgr[i0 + k - 1];
	    }
	    dotegr += dataforroutines1_1.m[i__ - 1] * (dataforroutines1_1.v[
		    i0] * dfe[0] + dataforroutines1_1.v[i0 + 1] * dfe[1] + 
		    dataforroutines1_1.v[i0 + 2] * dfe[2]);
/* radiated energy */
	}
	*energyj += dote * *dt;
	*energrj += dotegr * *dt;
	if (*ind == 2) {
	    incrementcommon_1.energyinc += dote * *dt;
	    incrementcommon_1.energrinc += dotegr * *dt;
	}
/* ind.eq.2 */
    }
/* IND=2 */
    if (softening_1.cmethod[1] != 0.) {
	dotw = 0.;
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    k0 = i__ * 3 - 3;
	    i0 = dataforroutines1_1.iname[i__ - 1] * 3 - 3;
	    dotw += dataforroutines1_1.v[i0] * gom[k0 + 1] + 
		    dataforroutines1_1.v[i0 + 1] * gom[k0 + 2] + 
		    dataforroutines1_1.v[i0 + 2] * gom[k0 + 3];
	}
	*wttlj += dotw * *dt;
	if (*ind == 2) {
	    incrementcommon_1.wttlinc += dotw * *dt;
	}
    }
/* cmethod(2).ne.0.0 */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    if (*ind == 2) {
		incrementcommon_1.wcinc[l + k - 1] += (fcj[l + k] + afc[l + k 
			- 1]) * *dt;
	    }
	    wcj[l + k] += (fcj[l + k] + afc[l + k - 1]) * *dt;
	}
    }
    for (k = 1; k <= 3; ++k) {
	spinj[k] += *dt * dspin[k - 1];
	cmvj[k] += *dt * dcmv[k - 1];
    }
    if (*ind == 2) {
	for (k = 1; k <= 3; ++k) {
	    incrementcommon_1.spininc[k - 1] += *dt * dspin[k - 1];
	    incrementcommon_1.cmvinc[k - 1] += *dt * dcmv[k - 1];
	}
    }
/* ind.eq.2 */
    return 0;
} /* v_jump__ */

/* Subroutine */ int v_jacconly__(doublereal *wcj, doublereal *cmvj, 
	doublereal *wttlj, doublereal *fc, doublereal *acc, doublereal *dt, 
	doublereal *gom, doublereal *energyj, doublereal *energrj)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    extern /* Subroutine */ int reduce2cm_(doublereal *, doublereal *, 
	    integer *, doublereal *);
    static integer i__, k, l, i0, i1, i2, k1;
    extern /* Subroutine */ int evaluatev_(doublereal *, doublereal *);
    static doublereal afc[600], dfe[600], wci[600], dcmv[3];
    extern doublereal cdot_(doublereal *, doublereal *);
    static doublereal dote, dotw, dotegr;

/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
    /* Parameter adjustments */
    --gom;
    --acc;
    --fc;
    --cmvj;
    --wcj;

    /* Function Body */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    wci[l + k - 1] = dataforroutines1_1.wc[l + k - 1] + fc[l + k] * *
		    dt / 2;
/* ( no inc here!) */
	}
    }
    evaluatev_(dataforroutines1_1.v, wci);
    reduce2cm_(&acc[1], dataforroutines1_1.m, &dataforroutines1_1.n, dcmv);
    i__1 = dataforroutines1_1.n * 3;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dataforroutines1_1.v[i__ - 1] += acc[i__] * *dt / 2;
/* average Velocity */
    }
/* adding V-dependent perts. */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = i__ * 3 - 3;
	i1 = dataforroutines1_1.iname[i__ - 1] * 3 - 3;
	i2 = dataforroutines1_1.iname[i__] * 3 - 3;
	for (k = 1; k <= 3; ++k) {
	    afc[l + k - 1] = acc[i2 + k] - acc[i1 + k];
/* CHAIN vector acceleratio */
	}
    }
    dote = 0.;
    dotegr = 0.;
    i__1 = dataforroutines1_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i1 = i__ * 3 - 2;
	for (k = 1; k <= 3; ++k) {
	    dfe[k - 1] = acc[i0 + k];
	}
	dote += dataforroutines1_1.m[i__ - 1] * cdot_(&dataforroutines1_1.v[
		i1 - 1], &acc[i1]);
    }
    *energyj += dote * *dt;
    *energrj += dotegr * *dt;
    incrementcommon_1.energyinc += dote * *dt;
    incrementcommon_1.energrinc += dotegr * *dt;
    if (softening_1.cmethod[1] != 0.) {
	dotw = 0.;
	i__1 = dataforroutines1_1.n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    k1 = i__ * 3 - 2;
	    i1 = dataforroutines1_1.iname[i__ - 1] * 3 - 2;
	    dotw += cdot_(&dataforroutines1_1.v[i1 - 1], &gom[k1]);
	}
	incrementcommon_1.wttlinc += dotw * *dt;
	*wttlj += dotw * *dt;
    }
/* cmethod(2).ne.0.0 */
    i__1 = dataforroutines1_1.n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (i__ - 1) * 3;
	for (k = 1; k <= 3; ++k) {
	    incrementcommon_1.wcinc[l + k - 1] += (fc[l + k] + afc[l + k - 1])
		     * *dt;
	    wcj[l + k] += (fc[l + k] + afc[l + k - 1]) * *dt;
	}
    }
    for (k = 1; k <= 3; ++k) {
	incrementcommon_1.cmvinc[k - 1] += *dt * dcmv[k - 1];
	cmvj[k] += *dt * dcmv[k - 1];
    }
    return 0;
} /* v_jacconly__ */

/* --------------------------------------- */
/* Subroutine */ int estimatestepsize_(doublereal *dtime, doublereal *step)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k;
    static doublereal r__;
    static integer i0, j0, k1, k2, k3;
    static doublereal oa;
    static integer ik, jk, ki, kj;
    static doublereal xa;
    static integer kp;
    static doublereal gx[5];
    static integer nr;
    static doublereal rr;
    static integer nx;
    static doublereal rx, vv, eta;
    static integer ind;
    static doublereal vij[3], xij[3];
    static integer iwr;
    extern /* Subroutine */ int updatexandv_(void);
    static doublereal alfa;
    extern doublereal cdot_(doublereal *, doublereal *);
    static doublereal mipj, vijk, xijk, zeta;
    extern /* Subroutine */ int xanom_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal dltrr, period, delta_t__;

    /* Fortran I/O blocks */
    static cilist io___584 = { 0, 91, 0, 0, 0 };


/*       ARCCOM.CH =filename */

/* the relative spin of M(1) !Spin=spin*G* */
/* not part of ARCCOM2e2.C */
    nr = 0;
    nx = 0;
/*     evaluate lenght of chain */
    updatexandv_();
/* we need x and v */
    *step = softening_1.cmethod[2] * *dtime;
/* contribution from cmethod(3) */
    i__1 = dataforroutines1_1.n - 1;
    for (ik = 1; ik <= i__1; ++ik) {
	i__2 = dataforroutines1_1.n;
	for (jk = ik + 1; jk <= i__2; ++jk) {
	    i__ = dataforroutines1_1.iname[ik - 1];
	    j = dataforroutines1_1.iname[jk - 1];
	    toolarge_1.iw = i__;
	    toolarge_1.jw = j;
	    ki = (i__ - 1) * 3;
	    kj = (j - 1) * 3;
	    if (jk != ik + 1) {
		xij[0] = dataforroutines1_1.x[ki] - dataforroutines1_1.x[kj];
		xij[1] = dataforroutines1_1.x[ki + 1] - dataforroutines1_1.x[
			kj + 1];
		xij[2] = dataforroutines1_1.x[ki + 2] - dataforroutines1_1.x[
			kj + 2];
		vij[0] = dataforroutines1_1.v[ki] - dataforroutines1_1.v[kj];
		vij[1] = dataforroutines1_1.v[ki + 1] - dataforroutines1_1.v[
			kj + 1];
		vij[2] = dataforroutines1_1.v[ki + 2] - dataforroutines1_1.v[
			kj + 2];
		ind = 0;
	    } else {
		ind = 123;
		k1 = ik * 3 - 2;
		k2 = k1 + 1;
		k3 = k2 + 1;
		xij[0] = -dataforroutines1_1.xc[k1 - 1];
/* use chain vectors when possible */
		xij[1] = -dataforroutines1_1.xc[k2 - 1];
/* (this often reduces roundoff) */
		xij[2] = -dataforroutines1_1.xc[k3 - 1];
		vij[0] = -dataforroutines1_1.wc[k1 - 1];
		vij[1] = -dataforroutines1_1.wc[k2 - 1];
		vij[2] = -dataforroutines1_1.wc[k3 - 1];
	    }
	    i0 = i__ * 3 - 3;
	    j0 = j * 3 - 3;
	    for (k = 1; k <= 3; ++k) {
		xijk = dataforroutines1_1.x[i0 + k - 1] - 
			dataforroutines1_1.x[j0 + k - 1];
		vijk = dataforroutines1_1.v[i0 + k - 1] - 
			dataforroutines1_1.v[j0 + k - 1];
	    }
	    rr = cdot_(xij, xij);
	    r__ = sqrt(rr);
	    alfa = softening_1.cmethod[0] * dataforroutines1_1.m[i__ - 1] * 
		    dataforroutines1_1.m[j - 1] + softening_1.cmethod[1] * 
		    omegacoefficients_1.omec[i__ + j * 200 - 201];
/* terms from potent */
	    mipj = dataforroutines1_1.m[i__ - 1] + dataforroutines1_1.m[j - 1]
		    ;
	    vv = cdot_(vij, vij);
	    oa = 2 / r__ - vv / mipj;
/* Computing 2nd power */
	    d__1 = *dtime;
	    dltrr = d__1 * d__1 * vv;
	    if (dltrr < rr * .001f) {
		++nr;
		*step += *dtime * alfa / r__;
/* add contributions from large distances */
	    } else {
/* in this case use Stumpff-Weiss method */
		++nx;
		eta = cdot_(xij, vij);
		toolarge_1.beta = mipj * oa;
		zeta = mipj - toolarge_1.beta * r__;
		period = 0.;
		if (oa > 0.f) {
		    period = 6.283185307179586 / (oa * sqrt(oa * mipj));
		    kp = (integer) (*dtime / period);
		    delta_t__ = *dtime - kp * period;
/* periods into account differently */
		} else {
		    kp = 0;
		    delta_t__ = *dtime;
/* !! */
		}
		toolarge_1.ma = dataforroutines1_1.m[i__ - 1];
		toolarge_1.mb = dataforroutines1_1.m[j - 1];
		xa = 0.;
		xanom_(&mipj, &r__, &eta, &zeta, &toolarge_1.beta, &delta_t__,
			 &xa, &rx, gx);
/* Solve KPLR- */
		*step += alfa * (xa + oa * kp * period);
/* Here the Stumpff-Weiss princ */
	    }
	}
    }
    if (iwr > 0) {
	s_wsle(&io___584);
	do_lio(&c__3, &c__1, (char *)&nr, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&nx, (ftnlen)sizeof(integer));
	e_wsle();
    }
    return 0;
} /* estimatestepsize_ */

/* ---------------------------------------- */
/* Subroutine */ int gfunc_(doublereal *xb, doublereal *al, doublereal *g)
{
    static doublereal c__[5];
    static integer i__;
    static doublereal s, z__;
    extern /* Subroutine */ int cfun_(doublereal *, doublereal *);

    /* Parameter adjustments */
    --g;

    /* Function Body */
    z__ = *al * *xb * *xb;
    cfun_(&z__, c__);
    s = *xb;
    for (i__ = 1; i__ <= 5; ++i__) {
	g[i__] = c__[i__ - 1] * s;
	s *= *xb;
/* L1: */
    }
    return 0;
} /* gfunc_ */

/* Subroutine */ int cfun_(doublereal *z__, doublereal *c__)
{
    /* Format strings */
    static char fmt_106[] = "(\002 too large Z=\002,1p,g12.4,\0024 c-functio"
	    "ns\002,0p,2i5,1p,4g12.4,i5,\002 ijmab_beta ax n_a\002)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal h__;
    static integer i__, k;
    static doublereal c2, c3, akseli;

    /* Fortran I/O blocks */
    static cilist io___592 = { 0, 6, 0, fmt_106, 0 };


/* Stumpff(Z,C) */
    /* Parameter adjustments */
    --c__;

    /* Function Body */
    ++diagno_1.ncfunc;
    toolarge_1.itoo = 0;
    h__ = *z__;
    for (k = 0; k <= 7; ++k) {
	if (abs(h__) < .9) {
	    goto L2;
	}
	h__ /= 4;
/* divide by 4 untill h<.9 */
    }
    akseli = (toolarge_1.ma + toolarge_1.mb) / toolarge_1.beta;
    s_wsfe(&io___592);
    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&toolarge_1.iw, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&toolarge_1.jw, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&toolarge_1.ma, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&toolarge_1.mb, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&toolarge_1.beta, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&akseli, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&toolarge_1.n_alku__, (ftnlen)sizeof(integer));
    e_wsfe();
    c__[1] = 0.;
/* 1. */
    for (k = 2; k <= 5; ++k) {
	c__[k] = 0.;
/* c(k-1)/k ! something */
    }
    toolarge_1.itoo = 1;
    return 0;
L2:
    c__[4] = (h__ * ((40025040. - h__ * 147173.) * h__ - 3741257520.) + 
	    201859257600.) / ((h__ * (h__ * (h__ * 5801. + 1945020.) + 
	    298738440.) + 20185925760.) * 240.);
/* use Pade -approximants for c_4 & c_5 */
    c__[5] = (h__ * ((358614256. - h__ * 1029037.) * h__ - 40967886960.) + 
	    3750361655040.) / ((h__ * (h__ * (h__ * 1451. + 582348.) + 
	    104602680.) + 8117665920.) * 55440.);
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* 4-fold argument K times */
	c3 = .16666666666666666 - h__ * c__[5];
	c2 = .5 - h__ * c__[4];
	c__[5] = (c__[5] + c__[4] + c2 * c3) * .0625;
	c__[4] = c3 * (2. - h__ * c3) * .125;
	h__ *= 4.;
    }
    c__[3] = .16666666666666666 - *z__ * c__[5];
    c__[2] = .5 - *z__ * c__[4];
    c__[1] = 1 - *z__ * c__[3];
    return 0;
} /* cfun_ */

/* -------KPLR solver------------------------------ */
/* Subroutine */ int xanom_(doublereal *m, doublereal *r__, doublereal *eta, 
	doublereal *zet, doublereal *beta, doublereal *t, doublereal *x, 
	doublereal *rx, doublereal *g)
{
    /* Format strings */
    static char fmt_166[] = "(1x,\002NO CONV\002,1p,7g12.4,\002 a r0 r1 t pr"
	    "d x dx\002)";

    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal f;
    static integer i__, k;
    static doublereal g0, r0, r1, r2, x0, x1, x00, dx, xg, ddr, aks, tau, rpp,
	     rpr, hhc2, eta0, eta1, eta2, tau0, tau1, tau2, zet0, zet1, zet2, 
	    xens;
    static integer icase;
    static doublereal ddtau;
    extern /* Subroutine */ int gfunc_(doublereal *, doublereal *, doublereal 
	    *);
    static integer itera;
    static doublereal dzeit, rlast, periodi;

    /* Fortran I/O blocks */
    static cilist io___630 = { 0, 6, 0, fmt_166, 0 };


/*      Solution of the `universal' form of Kepler's equation. */
/*      input: m=mass, r =r(0)=dist, eta=r.v, zet=m-r*beta, beta=m/a, t=time-incr */
/*      { note:  eta=sqrt[m a]*e Sin[E],  zeta=m e Cos[E] } */
/*      output: x=\int dt/r, rx=r(t), g(k)=x^k*c_k(beta*x^2); c_k=Stumpff-funcs */
/*      recommend: if a fairly good initial estimate is not available, use X=0. */
    /* Parameter adjustments */
    --g;

    /* Function Body */
    toolarge_2.betaa = *beta;
    eitoimi_1.iei = 0;
    if (*t == 0.f) {
/* if called with t=0 */
	*x = 0.;
	for (k = 1; k <= 5; ++k) {
	    g[k] = 0.;
	}
	*rx = *r__;
	return 0;
    }
/*        initial estimate (if not given as input i.e. if not x*t>0 ) */
    if (*x * *t <= 0.f) {
/* no initial estimate */
	if (*zet > 0.f) {
/*         x=t/(r**3+m*t**2/6)**.333333333d0 */
/* near pericentre */
/* Computing 2nd power */
	    d__2 = *t;
	    d__1 = *m * (d__2 * d__2) / 6;
	    *x = *t / sqrt(*r__ * *r__ + pow_dd(&d__1, &c_b341));
	    xens = *x;
	} else {
/* far from peric */
	    *x = *t / *r__;
	}
    }
/*        first bracket the root by stepping forwards */
/*        using the difference equations */
    toolarge_2.n_alku__ = 0;
L66:
    r0 = *r__;
    ++toolarge_2.n_alku__;
    eta0 = *eta;
    zet0 = *zet;
    tau0 = -(*t);
    gfunc_(x, beta, &g[1]);
/* 1. */
    xg = *x;
    g0 = 1 - *beta * g[2];
    tau1 = r0 * *x + eta0 * g[2] + zet0 * g[3] - *t;
    r1 = r0 + eta0 * g[1] + zet0 * g[2];
    eta1 = eta0 * g0 + zet0 * g[1];
    zet1 = zet0 * g0 - *beta * eta0 * g[1];
    x0 = 0.;
    x1 = *x;
    hhc2 = g[2] * 2;
    for (k = 1; k <= 8; ++k) {
/* !!!!!!!!!!!! */
	if (tau0 * tau1 > 0.f) {
	    ddtau = hhc2 * eta1;
	    ddr = hhc2 * zet1;
	    r2 = r1 * 2 - r0 + ddr;
	    zet2 = zet1 * 2 - zet0 - *beta * ddr;
	    tau2 = tau1 * 2 - tau0 + ddtau;
	    eta2 = eta1 * 2 - eta0 - *beta * ddtau;
	    eta0 = eta1;
	    eta1 = eta2;
	    zet0 = zet1;
	    zet1 = zet2;
	    r0 = r1;
	    r1 = r2;
	    tau0 = tau1;
	    tau1 = tau2;
	    x0 = x1;
	    x1 += *x;
	} else {
	    goto L77;
	}
    }
    *x = x1 * 1.5;
    goto L66;
/* initial estimate was much too small! */
L77:
/*       iterate to final solution */
    dx = *x;
    for (i__ = 1; i__ <= 300; ++i__) {
/* usually i_max =2 or 3 only */
	itera = i__;
	if ((d__1 = tau0 * r1, abs(d__1)) < (d__2 = tau1 * r0, abs(d__2))) {
	    dx = -tau0 / r0;
/*        dx=-tau0/(r0+eta0*dx/2) */
/*        dx=-tau0/(r0+eta0*dx/2+zet0*dx*dx/6) */
	    *x = x0 + dx;
	    dzeit = dx * (r0 + eta0 * dx / 2 + zet0 * dx * dx / 6) + tau0;
	    x00 = x0;
	    icase = 0;
	    tau = tau0;
	} else {
	    dx = -tau1 / r1;
/*        dx=-tau1/(r1+eta1*dx/2) */
/*        dx=-tau1/(r1+eta1*dx/2+zet1*dx*dx/6) */
	    *x = x1 + dx;
	    dzeit = dx * (r1 + eta1 * dx / 2 + zet1 * dx * dx / 6) + tau1;
	    x00 = x1;
	    icase = 1;
	    tau = tau1;
	}
	if ((x1 - *x) * (*x - x0) < 0.f || i__ == i__ / 5 * 5) {
/* if out_of_brackets o */
	    *x = (x0 + x1) / 2;
/* use bisection */
	    icase = -1;
	    goto L11;
	}
	if (abs(dzeit) < abs(*t) * .001 && abs(dx) < abs(*x) * .001f) {
	    goto L99;
	}
L11:
	gfunc_(x, beta, &g[1]);
/* 2.,... */
	xg = *x;
	g0 = 1 - *beta * g[2];
	rpr = *eta * g0 + *zet * g[1];
	rpp = *zet * g0 - *beta * *eta * g[1];
	rlast = *r__ + *eta * g[1] + *zet * g[2];
	f = *r__ * *x + *eta * g[2] + *zet * g[3] - *t;
	if (f * tau0 > 0.f) {
/* keep it bracketed */
	    x0 = *x;
	    tau0 = f;
	    eta0 = rpr;
	    zet0 = rpp;
	    r0 = rlast;
	} else {
	    x1 = *x;
	    tau1 = f;
	    eta1 = rpr;
	    zet1 = rpp;
	    r1 = rlast;
	}
    }
/* i */
    aks = *m / *beta;
    periodi = aks * 6.28f * sqrt(abs(aks) / *m);
    s_wsfe(&io___630);
    do_fio(&c__1, (char *)&aks, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&r0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&r1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&periodi, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*x), (ftnlen)sizeof(doublereal));
    d__1 = f / (r0 + r1) * 2;
    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    e_wsfe();
    eitoimi_1.iei = 1;
L99:
/*      final correction of g's  & r-evaluation */
    if (x00 != xg) {
	gfunc_(x, beta, &g[1]);
	xg = *x;
    } else {
	g[5] += dx * (g[4] + dx * g[3] / 2.);
	g[4] += dx * (g[3] + dx * g[2] / 2.);
/* Computing 3rd power */
	d__1 = *x;
	g[3] = d__1 * (d__1 * d__1) / 6. - *beta * g[5];
/* Computing 2nd power */
	d__1 = *x;
	g[2] = d__1 * d__1 / 2. - *beta * g[4];
	g[1] = *x - *beta * g[3];
    }
    *rx = *r__ + *eta * g[1] + *zet * g[2];
    return 0;
} /* xanom_ */

