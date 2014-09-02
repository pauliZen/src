CFLAGS = -O
FFLAGS = -O3
#FFLAGS = -O3 -ffortran-bounds-check
FC = gfortran

#SL=/star/lib
#LIBP = -L$(SL) `pgplot_link`
LIBP = -L/usr/lib -L/usr/X11R6/lib -L$(shell echo ~)/Downloads/pgplot -L$(shell echo ~)/lib -lpgplot -lX11 -lgcc
#LIBP = -lpgplot -L/usr/X11/lib -lX11

LIBX = -L/usr/X11R6/lib -lX11

SOURCE = kozai2.f binary.f block.f data.f derqp.f difsy1.f grbin.f inc.f \
         inclin.f impact.f peri.f plpert.f transf.f xtpert.f wait.f \
         ran2.f lenz.f gopu_SpinTerms.f cdot2.f

OBJECTS = $(SOURCE:.f=.o)

XOBJS = moviex.o 
POBJS = moviep.o 

help:
	@echo kozai: Three-body regularization program.
	@echo Within NEMO probably use:
	@echo '    make LIBP="$$YAPP_PGPLOT" ...'
	@echo to set the PGPLOT library, the LIBX may need a new value too:
	@echo "Current value:  LIBX=$(LIBX)"

all:	xtriple ptriple

xtriple: $(OBJECTS) $(XOBJS)
	$(FC) $(FFLAGS) $(OBJECTS) $(XOBJS) $(LIBX) -o xtriple

ptriple: $(OBJECTS) $(POBJS)
	$(FC) $(FFLAGS) $(OBJECTS) $(POBJS) $(LIBP) -o ptriple

clean:
	rm -f core *.o xtriple ptriple 

# don't remove the next few lines, they are essential for Sverre

print:
	@- \rm -f KOZAI.TEXT
	@cat $(SOURCE) > KOZAI.TEXT


#	these are benchmarks with the (X) windows display
bench:
	time xtriple < inx0
	time ptriple < inpyth0

